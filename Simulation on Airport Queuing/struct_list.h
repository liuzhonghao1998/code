#ifndef _struct_list_H  //�����ͷ�ļ����ظ�����
#define _struct_list_H
struct customer
{
	int id;                     //�˿ͱ��
	struct customer* nextptr;   //����ָ����
};
typedef struct customer CUST;
typedef struct customer* CUSTPTR;

struct check_window
{
	CUSTPTR headptr,            //ָ�򰲼�ڶ��׳˿�
            Lastptr;            //ָ�򰲼�ڶ�β�˿�
int state,             			//�����״̬��-1 -��Ϣ�У�0-�����У�1-�����У�
	cust_no,					//���ڰ����г˿͵ı��
	total_serve_len,			//���ڰ����г˿��ܷ���ʱ��
    already_serve_len,			//���ڰ����г˿��ѷ���ʱ��
	total_rest_len,				//�ƻ���Ϣʱ��
	already_rest_len,   		//����Ϣʱ��
	win_list_cust_count, 		//����ڶ���������
	cust_in,	         		//�³˿ͼ��루0-��1-�ǣ�
    cust_leave;       			//�˿��뿪���н��밲��ڣ�0-��1-�ǣ�
};
typedef struct check_window WIN;

struct input_event
{
	int event_time;				//�¼�������ʱ��
	int new_cust;				//������뻺�����ĳ˿���
	int rest_request[8];		//�������Ϣ���루0-δ�����1-�����
	int end_request;			//�°�ָ�0-δ�´1-�´
};
typedef struct input_event EVENT;
#define MaxWinLen 6
#endif
