#include<stdlib.h>
#include<stdio.h> 
#include"struct_list.h" 
//���ò���
int MaxCustSingleLine=0, //�������ȴ��˿���
    MaxLines=0,          //���λ����������MaxLines��ֱ�����
    MaxSeqLen=0,         //�������ȴ�����
    MinTimeLen=0,        //һ�ΰ������ʱ��
   	MaxTimeLen=0,        //һ�ΰ����ʱ��
   	MinRestTimeLen=0,    //�����һ����Ϣ���ʱ��
	MaxRestTimeLen=0;    //�����һ����Ϣ�ʱ��

int current_time=0;      //��ǰʱ��

WIN windows[8]={{0}};        //�������Ϣ

//��������Ϣ
int list_lines=0,        //�Ŷӻ�����������
	list_cust_count=0,   //�Ŷӻ������ܳ˿���
	accept_new_cust=0,   //�ɹ����뻺�����ĳ˿���
	reject_new_cust=0;   //���ܾ����뻺�����ĳ˿���

EVENT event={0};           //�����¼���Ϣ 
 
int offduty=0;           //�Ƿ����°ࣨ0-��1-��) 
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

