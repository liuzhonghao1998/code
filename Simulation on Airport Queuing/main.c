#include<stdio.h>
#include<stdlib.h>
#include<windows.h> 
#include"control.h" 
#include"struct_list.h"
#include"init.h"   
#include"input.h"    
#include"time_count.h"  
int timecount=0; 
HANDLE hThread1,hMutex;
int main()
{
	init();
	FILE* fptr; 
	int choose;
	printf("请选择输入方式(1或2)：\n1.键盘输入	2.文件输入\n");
	while(1){
		scanf("%d",&choose);
		getchar();
		if(choose==1||choose==2)  
		break;
		else{
			printf("输入错误，请重新选择(1或2)\n1.键盘输入	2.文件输入\n"); 
		}  
	}
	if(choose==2){
		fptr=fopen("input.txt","r");
		fptr=get_fileinput(fptr);
	} 
	else if(choose==1){
		hMutex=CreateMutex(NULL,FALSE,NULL); 
		hThread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)kb_input,NULL ,0,NULL);
		CloseHandle(hThread1);
	}
	while(offduty==0){
		control(); 
		if(choose==2){
			if(event.event_time==current_time){
			fptr=get_fileinput(fptr);
			}
		}
		output();
		time_count(); 
	}
	fclose(fptr);
	return 0;
 } 
