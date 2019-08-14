#include<stdlib.h>
#include<stdio.h> 
#include"struct_list.h" 
//配置参数
int MaxCustSingleLine=0, //队列最大等待乘客数
    MaxLines=0,          //蛇形缓冲区最多由MaxLines个直队组成
    MaxSeqLen=0,         //最大允许等待长度
    MinTimeLen=0,        //一次安检最短时长
   	MaxTimeLen=0,        //一次安检最长时长
   	MinRestTimeLen=0,    //安检口一次休息最短时长
	MaxRestTimeLen=0;    //安检口一次休息最长时长

int current_time=0;      //当前时间

WIN windows[8]={{0}};        //安检口信息

//缓冲区信息
int list_lines=0,        //排队缓冲区队列数
	list_cust_count=0,   //排队缓冲区总乘客数
	accept_new_cust=0,   //成功进入缓冲区的乘客数
	reject_new_cust=0;   //被拒绝进入缓冲区的乘客数

EVENT event={0};           //输入事件信息 
 
int offduty=0;           //是否已下班（0-否，1-是) 
void init()
{
	int init[7]={0},i=0,flag=1;
	FILE*sptr; 
	sptr=fopen("init.txt","r");
	char ch=fgetc(sptr);
	while(!feof(sptr)){ 
		if(ch>='0'&&ch<='9'){
			if(flag){
				init[i]=ch-'0';
				flag=!flag;
			}
			else{
				init[i]=init[i]*10+ch-'0';
			}
		} 
		else if(ch=='\n'){
			flag=1;
			i++;
		}
		ch=fgetc(sptr);
	}
	MaxCustSingleLine=init[0];
	MaxLines=init[1];
	MaxSeqLen=init[2];
	MinTimeLen=init[3];
	MaxTimeLen=init[4];
	MinRestTimeLen=init[5];
	MaxRestTimeLen=init[6]; 
}

