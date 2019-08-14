#include<stdio.h> 
#include<stdlib.h> 
#include<time.h>
#include"control.h"
#include"init.h" 
#include"struct_list.h"
#include"control.h" 
#define outputcycle 10  
extern int current_time;
extern int state_change;
extern WIN windows[8];
extern int offduty;
void kb_output()
{
	char ch;int i;
	ch=offduty>0?'Y':'N';
	CUSTPTR currentptr=NULL;
	switch(ch){
		case'Y':{
			printf("OFFDUTY=Y\n");
			break;
		}
		case'N':{
			printf("OFFDUTY=N\n");
			break;
		}
		printf("\tState\tCustNo\tServLen\tRestLen\tWinlistState\tWinListCustCount\tWinListCust\n");
		for(i=0;i<8;i++){
			switch(windows[i].state){
				case 0:{
					printf("空闲中\t");
					break;
				}
				case -1:{
					printf("休息中\t");
					break;
				} 
				case 1:{
					printf("g工作中\n");
					break;
				}
			}
			printf("%d\t%d/%d\t%d/%d\t",windows[i].cust_no,windows[i].already_serve_len,windows[i].total_serve_len,windows[i].already_rest_len,windows[i].total_rest_len);
			if(windows[i].cust_in==0&&windows[i].cust_leave==1){
				printf("CUSTADDIN and CUSTLEAVE\t");
			}
			else if(windows[i].cust_in==1&&windows[i].cust_leave==1) printf("CUSTLEAVE\t");
			else if(windows[i].cust_in==1&&windows[i].cust_leave==0) printf("CUSTADDIN\t");
			else if(windows[i].cust_in==0&&windows[i].cust_leave==0) printf("NOTCHANGE\t");
			printf("%d\t\t\t",windows[i].win_list_cust_count);
		  	currentptr=windows[i].headptr;
		  	 int T=1;
		  	 while(currentptr!=NULL){
		  	 	if(T){
		  	 		printf("%d",currentptr->id);
		  	 		T=0;
				   }
				else printf("->%d",currentptr->id);
				currentptr=currentptr->nextptr;
			   }
			   printf("\n");
		}
		printf("Listlines:%d\n",list_lines);
		printf("ListCustCount:%d\n",list_cust_count);
		if(accept_new_cust>0){
			printf("乘客进入缓冲区\n");
		}
		if(reject_new_cust>0){
			printf("拒绝进入缓冲区\n");
		}
		if(event.end_request){
			printf("接收到下班指令\n");
		} 
}	
 } 
void foutput(FILE*fptr){
	fprintf(fptr,"T=<%d>\n",current_time);
	char ch;int i;
	ch=offduty>0?'Y':'N';
	CUSTPTR currentptr=NULL;
	switch(ch){
		case'Y':{
			fprintf(fptr,"OFFDUTY=Y\n");
			break;
		}
		case'N':{
			fprintf(fptr,"OFFDUTY=N\n");
			break;
		}
	}
	fprintf(fptr,"\tState\tCustNo\tServLen\tRestLen\tWinlistState\tWinListCustCount\tWinListCust\n");
	for(i=0;i<8;i++){
		 fprintf(fptr,"WIN%d\t",i+1);
		 switch(windows[i].state){
		 	case 0:{
		 		fprintf(fptr,"空闲中\t");
				break;
			 }
			case -1:{
				fprintf(fptr,"休息中\t");
				break;
			}
			case 1:{
				fprintf(fptr,"工作中\t");
				break;
			}  
		 }
		 fprintf(fptr,"%d\t",windows[i].cust_no);
		 fprintf(fptr,"%d/%d\t",windows[i].already_serve_len,windows[i].total_serve_len);
		 fprintf(fptr,"%d/%d\t",windows[i].already_rest_len,windows[i].total_rest_len);
		 if(windows[i].cust_in==1&&windows[i].cust_leave==1){
			fprintf(fptr,"CUSTADDIN and CUSTLEAVE\t");
		 }
		 else if(windows[i].cust_in==0&&windows[i].cust_leave==1){
		 	fprintf(fptr,"CUSTLEAVE\t");
		 }
		 else if(windows[i].cust_in==1&&windows[i].cust_leave==0){
		 	fprintf(fptr,"CUSTADDIN\t");
		 }
		 else if(windows[i].cust_in==0&&windows[i].cust_leave==0){
		 	fprintf(fptr,"NOTCHANGE\t");
		 } 
		 fprintf(fptr,"%d\t\t\t",windows[i].win_list_cust_count);
		 currentptr=windows[i].headptr;
		 int T=1;
		 while(currentptr!=NULL){
		 	if(T){
			 fprintf(fptr,"%d",currentptr->id);
			 T=0;
	 		}
			else fprintf(fptr,"->%d",currentptr->id);
		 	currentptr=currentptr->nextptr;
		 	} 
		 	fprintf(fptr,"\n");
	}
	fprintf(fptr,"ListLines:%d\n",list_lines);
	fprintf(fptr,"ListCustCount:%d\n",list_cust_count);
	if(accept_new_cust>0){
		fprintf(fptr,"乘客进入缓冲区\n");
	}
	if(reject_new_cust>0){
		fprintf(fptr,"拒绝进入缓冲区\n"); 
	}
	if(event.end_request){
		fprintf(fptr,"接收到下班指令\n");
	}
}
void output()
{
	FILE*fptr;
	FILE*sptr;
	switch(current_time){
		case 0:{
			fptr=fopen("outputDetail.txt","w");
			sptr=fopen("output.txt","w");
			break;
		}
		default:{
			fptr=fopen("outputDetail.txt","a");
			sptr=fopen("output.txt","a");
			break;
		} 
	} 
	
	if(current_time%outputcycle==0){
		foutput(fptr);
	}
	if(state_change){
		foutput(sptr);
	}
}
