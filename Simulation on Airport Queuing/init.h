#ifndef _init_H  //避免该头文件被重复包含
#define _init_H
#include"struct_list.h"
//配置参数
extern int MaxCustSingleLine, //队列最大等待乘客数
    MaxLines,          //蛇形缓冲区最多由MaxLines个直队组成
    MaxSeqLen,         //最大允许等待长度
    MinTimeLen,        //一次安检最短时长
   	MaxTimeLen,        //一次安检最长时长
   	MinRestTimeLen,    //安检口一次休息最短时长
	MaxRestTimeLen;    //安检口一次休息最长时长
 
extern int current_time;      //当前时间

extern WIN windows[8];        //安检口信息

//缓冲区信息 
extern int list_lines,        //排队缓冲区队列数
	list_cust_count,   //排队缓冲区总乘客数
	accept_new_cust,   //成功进入缓冲区的乘客数
	reject_new_cust;   //被拒绝进入缓冲区的乘客数

extern EVENT event;            //输入事件信息 
 
extern int offduty;           //是否已下班（0-否，1-是) 
void init();				  //读取并保存配置参数 
#endif
