#ifndef _struct_list_H  //避免该头文件被重复包含
#define _struct_list_H
struct customer
{
	int id;                     //乘客编号
	struct customer* nextptr;   //链表指针域
};
typedef struct customer CUST;
typedef struct customer* CUSTPTR;

struct check_window
{
	CUSTPTR headptr,            //指向安检口队首乘客
            Lastptr;            //指向安检口队尾乘客
int state,             			//安检口状态（-1 -休息中，0-空闲中，1-服务中）
	cust_no,					//正在安检中乘客的编号
	total_serve_len,			//正在安检中乘客总服务时长
    already_serve_len,			//正在安检中乘客已服务时长
	total_rest_len,				//计划休息时长
	already_rest_len,   		//已休息时长
	win_list_cust_count, 		//安检口队列总人数
	cust_in,	         		//新乘客加入（0-否，1-是）
    cust_leave;       			//乘客离开队列进入安检口（0-否，1-是）
};
typedef struct check_window WIN;

struct input_event
{
	int event_time;				//事件发生的时刻
	int new_cust;				//申请进入缓冲区的乘客数
	int rest_request[8];		//安检口休息申请（0-未提出，1-提出）
	int end_request;			//下班指令（0-未下达，1-下达）
};
typedef struct input_event EVENT;
#define MaxWinLen 6
#endif
