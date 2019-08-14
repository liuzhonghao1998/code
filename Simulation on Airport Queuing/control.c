#include<stdio.h> 
#include<stdlib.h>
#include"struct_list.h"
#include"init.h"
#define q1 -1  //休息// 
#define q2 0   //空闲// 
#define q3 1   //安检//
#define q4 2   //安检提出//
#define q5 3   //安检准备休息// 
#define q6 4   //空闲提出// 

void new_cust_control();                            //处理新乘客到来 
void assign_cust_control();                         //分配乘客到安检口 
void Check(); 
void SecWmachine();
int restallow();
int randomREST();
int randomLEN();
void lowprint(); 

	int state_change=0;                             //标志当前时刻大厅状态是否发生变化 
	static int ready_offduty=0;						//标志是否准备下班 
	static CUSTPTR seq_headptr=NULL;                //指向排队缓冲区队首的指针
	static CUSTPTR turnptr[99]={0};	               //指向各行末尾（拐弯处）的指针（角标为行序数）
	static int restfl[8]={0};                      //用于储存和排序安检口申请// 
	static int restall[8]={0};                    //用于给安检申请休息排队// 
	static int statein[8]={0};               //第i+1个安检口的状态，用于内部计算//
	
void control()
{
	int i=0,j=0,k=0;
	state_change=0;
	accept_new_cust=0;
	reject_new_cust=0;
	for(j=0;j<=7;j++)
	{
		windows[j].cust_in=0; 
		windows[j].cust_leave=0;
	}
	
	if(event.event_time==current_time&&event.end_request==1)                        //判断当前时刻是否发出下班指令 
		ready_offduty=1;
		
	new_cust_control();                             //处理新乘客到来 
	assign_cust_control();                          //分配乘客到安检口 
	Check();
	
	if(ready_offduty==1&&seq_headptr==NULL)         //判断缓冲区是否为空 
		while(windows[i].cust_no==0&&windows[i].headptr==NULL&&i<=7)                  //判断各安检口是否为空 
			i++;	
	if(i==8)
	{
		state_change=1;
		offduty=1;                                  //正式下班 
	}
	
	if(state_change==0)                             //判断大厅状态是否发生变化 
	{
		for(j=0;j<=7;j++)
		{
			if(windows[j].cust_leave==1)
			{
				state_change=1;
				break;
			}
		}
	}
		
	lowprint();
} 

void new_cust_control()                             //处理新乘客到来 
{	
	int i;			                                //用于依次处理申请
	static int last_number=0;                       //已分配的编号数
	static CUSTPTR seq_lastptr=NULL;                //指向排队缓冲区队尾的指针
          		   
	if(current_time==event.event_time&&event.new_cust>0)
	{//如果当前时刻有乘客申请进入缓冲区
		if(ready_offduty==0)
		{//如果下班指令未下达
			for(i=1;i<=event.new_cust;i++)
			{//依次处理申请
				if(list_cust_count==MaxCustSingleLine* MaxLines)
	            //缓冲区已满
					reject_new_cust++;
				else
				{//缓冲区未满
				accept_new_cust++;
					if(seq_headptr==NULL)
		 			{//缓冲区为空
						seq_headptr=malloc(sizeof(CUST));
						seq_lastptr=seq_headptr;
					}
					else
					{//缓冲区不为空
						seq_lastptr->nextptr= malloc(sizeof(CUST));
						seq_lastptr= seq_lastptr->nextptr;
					}
					seq_lastptr->id=last_number+1;
					seq_lastptr->nextptr=NULL;
					last_number++;
					list_cust_count++;
					if(list_cust_count%MaxCustSingleLine==1)
					//增加一条直队
						list_lines++;
					if(list_cust_count%MaxCustSingleLine==0)
	        		//标记拐弯处
						turnptr[list_lines]=seq_lastptr;
				}//end of else
			}//end of for
		}//end of if
	}//end of if
}

void assign_cust_control()            //分配乘客到安检口 
{
	int i=0,j=1;
	for(i=0;i<=7;i++)
	{//查看各安检口及其队列的状态 
		while(seq_headptr!=NULL&&windows[i].win_list_cust_count<MaxWinLen&&windows[i].state!=q1&&statein[i]!=q5)
		{//判断当前时刻是否能分配乘客到安检口 
			if(windows[i].headptr!=NULL)
			//如果该安检口队列不为空 
				windows[i].Lastptr->nextptr=seq_headptr;
			else//如果该安检口队列为空 
				windows[i].headptr=seq_headptr;
			windows[i].Lastptr=seq_headptr;
			seq_headptr=seq_headptr->nextptr;
			windows[i].Lastptr->nextptr=NULL;
			windows[i].win_list_cust_count++; 
			list_cust_count--;
			windows[i].cust_in=1;
			state_change=1;
			j=1;
			if(seq_headptr==NULL)
				list_lines--;
			while(turnptr[j]!=NULL&&j<MaxCustSingleLine)
			{//缓冲区队伍依次前移 
				turnptr[j]=turnptr[j]->nextptr;
				if(turnptr[j]==NULL)
					list_lines--;
				j++;	
			}
		}//end of while
	}//end of for
}
 void Check(void){              //安检函数// 
 	CUSTPTR freeptr=NULL; 
 	static int number=1; 
	int i,no,j;                
		number++;
		if(event.event_time==current_time)
		{
			for(j=0;j<=7;j++)
			{
				if(event.rest_request[j]==1)
					restfl[j]=number;
			}
		}
		for(i=0;i<=7;i++){
			switch(windows[i].state){
				case 0:
					if(event.rest_request[i]==1&&event.event_time==current_time){      //第i+1个安检口申请休息/ 
						restfl[i]=number;
						SecWmachine(i);
					}else{
					    if(windows[i].headptr!=NULL){
					    	SecWmachine(i);
					 } 
					}
					if(restfl[i]!=0){
						SecWmachine(i);
					}
				break;
				case 1:
					if(event.rest_request[i]==1&&event.event_time==current_time){     //第i+1个安检口申请休息，调用自动机//
						restfl[i]=number;
						SecWmachine(i);
					}
					if(restfl[i]!=0){                   //第i+1个安检口休息申请未过// 
						SecWmachine(i);
					}
					if(windows[i].cust_no==0&&windows[i].headptr!=NULL){
						windows[i].cust_leave=1;         //乘客进入安检口// 
						windows[i].win_list_cust_count--;
						no=windows[i].headptr->id;
						windows[i].cust_no=no;
						windows[i].total_serve_len=randomLEN();
						freeptr=windows[i].headptr;
						windows[i].headptr=windows[i].headptr->nextptr;
						SecWmachine(i);
						free(freeptr);
					}else{
						if(windows[i].total_serve_len==windows[i].already_serve_len){   //该乘客安检结束// 
							windows[i].total_serve_len=0;
							windows[i].already_serve_len=0;
							windows[i].cust_leave=0;            //重置// 
							windows[i].cust_no=0;							
							SecWmachine(i);
						}else{
							windows[i].already_serve_len++;   //系统时间加一(未改版)//
						}
					}
				break;
				case -1:
					if(windows[i].total_rest_len!=windows[i].already_rest_len){
						windows[i].already_rest_len++;              //已休息时间增加（未改版）//
					}else{
						SecWmachine(i);                          //休息时间已到//
					}
				break;
		}
    }
} 
void SecWmachine(int i)    //安检口自动机函数，i:第i+1个安检口// 
{	int j; 
    static  win_open_num=8;
	switch(statein[i]){
		case q2:       //空闲// 
			if(restfl[i]==0&&windows[i].headptr==NULL){
				statein[i]=q2;
				windows[i].state=q2;
			}else{
				if(windows[i].headptr!=NULL&&restfl[i]==0){
					statein[i]=q3;
					windows[i].state=q3;
					state_change=1;             //安检口状态改变（告诉输出）//
				}else{
					if(restfl[i]!=0&&windows[i].headptr==NULL){
						statein[i]=q6;
					}else{
						if(restfl[i]!=0&&windows[i].headptr!=NULL){
							statein[i]=q4;
							windows[i].state=q3;
							state_change=1;
						}
					}
				}
			}
		break;
		case q3:   //安检//
		if(restfl[i]==0&&windows[i].headptr!=NULL){
			statein[i]=q3;
		}else{
			if(restfl[i]==0&&windows[i].headptr==NULL&&windows[i].cust_no==0){
				statein[i]=q2;
				windows[i].state=q2;
			}else{
				if(restfl[i]!=0&&event.event_time==current_time){
					statein[i]=q4;
				}
			}
		}
		break;
		case q4:   //安检提出//
			if( restallow(list_cust_count,i,win_open_num)==0){
				statein[i]=q4;
				windows[i].state=q3;
			}else{
				if( restallow(list_cust_count,i,win_open_num)){
					restfl[i]=0;               //申请通过，该申请清零// 
					statein[i]=q5;
					windows[i].state=q3;
					win_open_num--;
				}
			}
		break;
		case q5:   //安检准备休息//
			if(windows[i].headptr!=NULL||windows[i].cust_no!=0){
				statein[i]=q5;
				windows[i].state=q3;
			}else if(windows[i].cust_no==0&&windows[i].headptr==NULL){
				statein[i]=q1;
				windows[i].state=q1;
				state_change=1;                            //安检口状态改变（告诉输出）//
				windows[i].total_rest_len=randomREST();       //分配休息时间//
			}
		break;
		case q6:    //空闲提出//
		   if( restallow(list_cust_count,i,win_open_num)==0){
		   	statein[i]=q6;
			windows[i].state=q2;
		   }else{
		   	restfl[i]=0;                          //申请通过，该申请清零//
		   	statein[i]=q1;
			windows[i].state=q1;
			windows[i].total_rest_len=randomREST();      //分配休息时间//
			state_change=1; 
			win_open_num--; 
		   }
		break; 
		case q1:    //休息//
			if(windows[i].total_rest_len-windows[i].already_rest_len!=0){
			statein[i]=q1;
			windows[i].state=q1;
			}else{
			statein[i]=q2;
			windows[i].state=q2;
			windows[i].already_rest_len=0;
			windows[i].total_rest_len=0;
			state_change=1;
			win_open_num++;
			}
		break;	 
	}
 } 
 int restallow(int sum,int i,int winnum)                 //管理休息申请，返回值是先休息的安检口//
 {
 	int j=0,MIN=i,Min;
 	int point=0;
 	if(sum/winnum<MaxSeqLen&&winnum>1){
 		for( ; j<=7;j++){                      //判断最先申请的安检口// 
 			if(restfl[MIN]>restfl[j]&&restfl[j]!=0)
 				MIN=j;
		 }
		 if(restfl[i]==restfl[MIN])
		 	MIN=i;
		 j=0;
		 for( ; j<=7;j++){                   //查看最先申请的安检口个数// 
		 	if(restfl[MIN]==restfl[j]){
		 		point++;
			 }
		 }
		 j=0;
	    if(point>1){                         //最先申请安检口个数不止一个//          
	       if(MIN==i){                     //其中i+1包含在最先组中// 
	       	  	Min=i;
				for( ;j<=7;j++){               //找休息时间最短的安检口// 
	    		if(restfl[j]==restfl[MIN]&&restall[j]<restall[Min])
	    			Min=j;
				}
				}
			else
				return 0;
			if(Min==i)
		   		return 1;                           //包含在最先队列且总休息时间最短// 
		   else
		   		return 0;                             //包含在最先队列但总休息时间不是最短// 
		}
		if(point<=1){                  //最先申请的安检口就一个// 
			if(MIN==i)                 //最先申请安检口是i+1// 
				return 1;                        
			else
				return 0;               //最先申请的安检口不是i+1// 
		}
	 }else
	 	return 0; 
}
 int randomREST(){                //分配休息时间//
 	int i=MaxRestTimeLen-MinRestTimeLen+1;
 	int j;
 	srand(time(NULL));
 	j=MinRestTimeLen+(rand())%i;
 	return j;
 }
 int randomLEN(){         //分配安检时间// 
 	int i=MaxTimeLen-MinTimeLen+1;
 	int j;
 	srand(time(NULL));
 	j=MinTimeLen+(rand())%i;
 	return j;
 }

void lowprint()
{
	CUSTPTR outptr;
	int i=1;
	outptr=seq_headptr;
	while(outptr!=NULL)
	{
		printf("%d\t",outptr->id);
		if(outptr==turnptr[i])
		{
			printf("\n");
			i++;
		}
		outptr=outptr->nextptr;
	}
	printf("\n\n");
	for(i=0;i<=7;i++)
	{
		outptr=windows[i].headptr;
		while(outptr)
		{
			printf("%d\t",outptr->id);
			outptr=outptr->nextptr;
		}
		printf("\n");
	}
	printf("\n");
}
