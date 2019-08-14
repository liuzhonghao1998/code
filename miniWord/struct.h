#ifndef _STRUCT_H
#define _STRUCT_H

#define MAX 168
#include<windows.h>
struct data_node
{
	char data[100];
	struct data_node* right;
}typedef Data_node;

struct row_node
{
	struct data_node* right;
	struct row_node* down;
}typedef Row_node;

extern Row_node* pData_stack;	
extern char file_name[20];
extern int next[100];
extern HANDLE hout;
extern COORD coord;
extern CONSOLE_SCREEN_BUFFER_INFO csbi; //控制台屏幕缓冲区信息

#endif
