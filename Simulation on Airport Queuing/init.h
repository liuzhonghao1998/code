#ifndef _init_H  //�����ͷ�ļ����ظ�����
#define _init_H
#include"struct_list.h"
//���ò���
extern int MaxCustSingleLine, //�������ȴ��˿���
    MaxLines,          //���λ����������MaxLines��ֱ�����
    MaxSeqLen,         //�������ȴ�����
    MinTimeLen,        //һ�ΰ������ʱ��
   	MaxTimeLen,        //һ�ΰ����ʱ��
   	MinRestTimeLen,    //�����һ����Ϣ���ʱ��
	MaxRestTimeLen;    //�����һ����Ϣ�ʱ��
 
extern int current_time;      //��ǰʱ��

extern WIN windows[8];        //�������Ϣ

//��������Ϣ 
extern int list_lines,        //�Ŷӻ�����������
	list_cust_count,   //�Ŷӻ������ܳ˿���
	accept_new_cust,   //�ɹ����뻺�����ĳ˿���
	reject_new_cust;   //���ܾ����뻺�����ĳ˿���

extern EVENT event;            //�����¼���Ϣ 
 
extern int offduty;           //�Ƿ����°ࣨ0-��1-��) 
void init();				  //��ȡ���������ò��� 
#endif
