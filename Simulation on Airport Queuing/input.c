#include"struct_list.h"
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h> 
#define q0 0
#define q1 1
#define q2 2
#define q3 3
#define q4 4
#define q5 5
#define q6 6
#define end -1 
EVENT event;
extern HANDLE hMutex;
void kb_input()
{
	char *ch;
	gets(ch);
	int i,flag=0;
	for(i=0;i<strlen(ch);i++){
		if(ch[i]=='R'){
			flag=1;
			continue;
		}
		else if(ch[i]=='G'){
			event.new_cust++;
		}
		else if(ch[i]=='|'){
			continue;
		}
		else if(ch[i]=='Q'){
			event.end_request=1;
		}
		else if(ch[i]>='1'&&ch[i]<='8'){
			if(flag){
				event.rest_request[ch[i]-'0'-1]=1;				
			}	
		} 
	}
	 
}
FILE* get_fileinput(FILE*fptr){
	
	int state=q0;
	event.event_time=0;
	event.new_cust=0;
	event.end_request=0;
	int i=0,flag=1;
	char ch;
	while(i<9){
		event.rest_request[i]=0;
		i++;
	}
	while((ch=fgetc(fptr))!=EOF&&ch!='\n')
		switch(state){
			case q0:{
				if(ch=='T')
				state=q1;
				else state=end;
				break;
			}
			case q1:{
				if(ch=='=') state=q2;
				else state=end;
				break;
			}
			case q2:{
				if(ch>='0'&&ch<='9'&&flag==1){
				event.event_time=ch-'0';
				flag=!flag;
				state=q2;
				}
				else if(ch>='0'&&ch<='9'&&flag==0){
				event.event_time=event.event_time*10+ch-'0';
				} 
				else state=q3;
				break;
			}
			case q3:{
				switch(ch){
					case'=':{
						state=q4;
						break;
					}
					default:{
						state=q3;
						break;
					} 
				} 
				break;
			}
			case q4:{
				switch(ch){
					case 'G':{
						event.new_cust++;	
						state=q6;
						break;
					} 
					case'R':{
						state=q5;
						break;
					}
					case'Q':{
						event.end_request=1;
						break;
					}
					case'\n' :{
						state=end;
						break;
					}
				}
			}
			case q5:{
				if(ch>='1'&&ch<='8'){
					event.rest_request[ch-'0'-1]=1;
					state=q6;
				}
				break;
			}
			case q6:{
				if(ch=='|') state=q4;
				break;
			}
			case end:{
				break;
			}			 
		}
	return fptr;
}

