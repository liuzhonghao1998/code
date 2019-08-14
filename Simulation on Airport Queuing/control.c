#include<stdio.h> 
#include<stdlib.h>
#include"struct_list.h"
#include"init.h"
#define q1 -1  //��Ϣ// 
#define q2 0   //����// 
#define q3 1   //����//
#define q4 2   //�������//
#define q5 3   //����׼����Ϣ// 
#define q6 4   //�������// 

void new_cust_control();                            //�����³˿͵��� 
void assign_cust_control();                         //����˿͵������ 
void Check(); 
void SecWmachine();
int restallow();
int randomREST();
int randomLEN();
void lowprint(); 

	int state_change=0;                             //��־��ǰʱ�̴���״̬�Ƿ����仯 
	static int ready_offduty=0;						//��־�Ƿ�׼���°� 
	static CUSTPTR seq_headptr=NULL;                //ָ���Ŷӻ��������׵�ָ��
	static CUSTPTR turnptr[99]={0};	               //ָ�����ĩβ�����䴦����ָ�루�Ǳ�Ϊ��������
	static int restfl[8]={0};                      //���ڴ�������򰲼������// 
	static int restall[8]={0};                    //���ڸ�����������Ϣ�Ŷ�// 
	static int statein[8]={0};               //��i+1������ڵ�״̬�������ڲ�����//
	
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
	
	if(event.event_time==current_time&&event.end_request==1)                        //�жϵ�ǰʱ���Ƿ񷢳��°�ָ�� 
		ready_offduty=1;
		
	new_cust_control();                             //�����³˿͵��� 
	assign_cust_control();                          //����˿͵������ 
	Check();
	
	if(ready_offduty==1&&seq_headptr==NULL)         //�жϻ������Ƿ�Ϊ�� 
		while(windows[i].cust_no==0&&windows[i].headptr==NULL&&i<=7)                  //�жϸ�������Ƿ�Ϊ�� 
			i++;	
	if(i==8)
	{
		state_change=1;
		offduty=1;                                  //��ʽ�°� 
	}
	
	if(state_change==0)                             //�жϴ���״̬�Ƿ����仯 
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

void new_cust_control()                             //�����³˿͵��� 
{	
	int i;			                                //�������δ�������
	static int last_number=0;                       //�ѷ���ı����
	static CUSTPTR seq_lastptr=NULL;                //ָ���Ŷӻ�������β��ָ��
          		   
	if(current_time==event.event_time&&event.new_cust>0)
	{//�����ǰʱ���г˿�������뻺����
		if(ready_offduty==0)
		{//����°�ָ��δ�´�
			for(i=1;i<=event.new_cust;i++)
			{//���δ�������
				if(list_cust_count==MaxCustSingleLine* MaxLines)
	            //����������
					reject_new_cust++;
				else
				{//������δ��
				accept_new_cust++;
					if(seq_headptr==NULL)
		 			{//������Ϊ��
						seq_headptr=malloc(sizeof(CUST));
						seq_lastptr=seq_headptr;
					}
					else
					{//��������Ϊ��
						seq_lastptr->nextptr= malloc(sizeof(CUST));
						seq_lastptr= seq_lastptr->nextptr;
					}
					seq_lastptr->id=last_number+1;
					seq_lastptr->nextptr=NULL;
					last_number++;
					list_cust_count++;
					if(list_cust_count%MaxCustSingleLine==1)
					//����һ��ֱ��
						list_lines++;
					if(list_cust_count%MaxCustSingleLine==0)
	        		//��ǹ��䴦
						turnptr[list_lines]=seq_lastptr;
				}//end of else
			}//end of for
		}//end of if
	}//end of if
}

void assign_cust_control()            //����˿͵������ 
{
	int i=0,j=1;
	for(i=0;i<=7;i++)
	{//�鿴������ڼ�����е�״̬ 
		while(seq_headptr!=NULL&&windows[i].win_list_cust_count<MaxWinLen&&windows[i].state!=q1&&statein[i]!=q5)
		{//�жϵ�ǰʱ���Ƿ��ܷ���˿͵������ 
			if(windows[i].headptr!=NULL)
			//����ð���ڶ��в�Ϊ�� 
				windows[i].Lastptr->nextptr=seq_headptr;
			else//����ð���ڶ���Ϊ�� 
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
			{//��������������ǰ�� 
				turnptr[j]=turnptr[j]->nextptr;
				if(turnptr[j]==NULL)
					list_lines--;
				j++;	
			}
		}//end of while
	}//end of for
}
 void Check(void){              //���캯��// 
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
					if(event.rest_request[i]==1&&event.event_time==current_time){      //��i+1�������������Ϣ/ 
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
					if(event.rest_request[i]==1&&event.event_time==current_time){     //��i+1�������������Ϣ�������Զ���//
						restfl[i]=number;
						SecWmachine(i);
					}
					if(restfl[i]!=0){                   //��i+1���������Ϣ����δ��// 
						SecWmachine(i);
					}
					if(windows[i].cust_no==0&&windows[i].headptr!=NULL){
						windows[i].cust_leave=1;         //�˿ͽ��밲���// 
						windows[i].win_list_cust_count--;
						no=windows[i].headptr->id;
						windows[i].cust_no=no;
						windows[i].total_serve_len=randomLEN();
						freeptr=windows[i].headptr;
						windows[i].headptr=windows[i].headptr->nextptr;
						SecWmachine(i);
						free(freeptr);
					}else{
						if(windows[i].total_serve_len==windows[i].already_serve_len){   //�ó˿Ͱ������// 
							windows[i].total_serve_len=0;
							windows[i].already_serve_len=0;
							windows[i].cust_leave=0;            //����// 
							windows[i].cust_no=0;							
							SecWmachine(i);
						}else{
							windows[i].already_serve_len++;   //ϵͳʱ���һ(δ�İ�)//
						}
					}
				break;
				case -1:
					if(windows[i].total_rest_len!=windows[i].already_rest_len){
						windows[i].already_rest_len++;              //����Ϣʱ�����ӣ�δ�İ棩//
					}else{
						SecWmachine(i);                          //��Ϣʱ���ѵ�//
					}
				break;
		}
    }
} 
void SecWmachine(int i)    //������Զ���������i:��i+1�������// 
{	int j; 
    static  win_open_num=8;
	switch(statein[i]){
		case q2:       //����// 
			if(restfl[i]==0&&windows[i].headptr==NULL){
				statein[i]=q2;
				windows[i].state=q2;
			}else{
				if(windows[i].headptr!=NULL&&restfl[i]==0){
					statein[i]=q3;
					windows[i].state=q3;
					state_change=1;             //�����״̬�ı䣨���������//
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
		case q3:   //����//
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
		case q4:   //�������//
			if( restallow(list_cust_count,i,win_open_num)==0){
				statein[i]=q4;
				windows[i].state=q3;
			}else{
				if( restallow(list_cust_count,i,win_open_num)){
					restfl[i]=0;               //����ͨ��������������// 
					statein[i]=q5;
					windows[i].state=q3;
					win_open_num--;
				}
			}
		break;
		case q5:   //����׼����Ϣ//
			if(windows[i].headptr!=NULL||windows[i].cust_no!=0){
				statein[i]=q5;
				windows[i].state=q3;
			}else if(windows[i].cust_no==0&&windows[i].headptr==NULL){
				statein[i]=q1;
				windows[i].state=q1;
				state_change=1;                            //�����״̬�ı䣨���������//
				windows[i].total_rest_len=randomREST();       //������Ϣʱ��//
			}
		break;
		case q6:    //�������//
		   if( restallow(list_cust_count,i,win_open_num)==0){
		   	statein[i]=q6;
			windows[i].state=q2;
		   }else{
		   	restfl[i]=0;                          //����ͨ��������������//
		   	statein[i]=q1;
			windows[i].state=q1;
			windows[i].total_rest_len=randomREST();      //������Ϣʱ��//
			state_change=1; 
			win_open_num--; 
		   }
		break; 
		case q1:    //��Ϣ//
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
 int restallow(int sum,int i,int winnum)                 //������Ϣ���룬����ֵ������Ϣ�İ����//
 {
 	int j=0,MIN=i,Min;
 	int point=0;
 	if(sum/winnum<MaxSeqLen&&winnum>1){
 		for( ; j<=7;j++){                      //�ж���������İ����// 
 			if(restfl[MIN]>restfl[j]&&restfl[j]!=0)
 				MIN=j;
		 }
		 if(restfl[i]==restfl[MIN])
		 	MIN=i;
		 j=0;
		 for( ; j<=7;j++){                   //�鿴��������İ���ڸ���// 
		 	if(restfl[MIN]==restfl[j]){
		 		point++;
			 }
		 }
		 j=0;
	    if(point>1){                         //�������밲��ڸ�����ֹһ��//          
	       if(MIN==i){                     //����i+1��������������// 
	       	  	Min=i;
				for( ;j<=7;j++){               //����Ϣʱ����̵İ����// 
	    		if(restfl[j]==restfl[MIN]&&restall[j]<restall[Min])
	    			Min=j;
				}
				}
			else
				return 0;
			if(Min==i)
		   		return 1;                           //���������ȶ���������Ϣʱ�����// 
		   else
		   		return 0;                             //���������ȶ��е�����Ϣʱ�䲻�����// 
		}
		if(point<=1){                  //��������İ���ھ�һ��// 
			if(MIN==i)                 //�������밲�����i+1// 
				return 1;                        
			else
				return 0;               //��������İ���ڲ���i+1// 
		}
	 }else
	 	return 0; 
}
 int randomREST(){                //������Ϣʱ��//
 	int i=MaxRestTimeLen-MinRestTimeLen+1;
 	int j;
 	srand(time(NULL));
 	j=MinRestTimeLen+(rand())%i;
 	return j;
 }
 int randomLEN(){         //���䰲��ʱ��// 
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
