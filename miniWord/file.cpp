#include"struct.h"
#include<stdio.h>
#include<iostream>
using namespace std;

Row_node* pData_stack;	
char file_name[20];
int next[100];
HANDLE hout;
COORD coord;
CONSOLE_SCREEN_BUFFER_INFO csbi; //控制台屏幕缓冲区信息

int Newfile()
{
	FILE *fPtr;
	cout<<"请输入文件名："; 
	gets(file_name);
	strcat(file_name, ".txt");
	if(NULL==(fPtr=fopen(file_name, "w")))
	    printf("新建文件失败！");
	else
	    printf("新建文件成功，文件名称为：%s", file_name);
	fclose(fPtr);
	return 0;
}

void delete_stack()
{
	Row_node* current_row=pData_stack;
	Row_node* temp_row=NULL;
	Data_node* current_data=NULL;
	Data_node* temp_data=NULL;
	while(current_row!=NULL) //判断是否读到最后一行 
	{
		current_data=current_row->right;
		while(current_data!=NULL) //判断是否为该行的最后一个数据链表 
		{
			temp_data=current_data;
			current_data=current_data->right;
			free(temp_data); //释放数据链表 
		}
		temp_row=current_row;
		current_row=current_row->down;
		free(temp_row); //释放行链表 
	}
	pData_stack=NULL;
}

int Openfile()
{ 
	FILE *fPtr;
	memset(file_name,'\0',20);
	printf("请输入需要打开的文件名："); 
	gets(file_name);
	strcat(file_name, ".txt");
	if(NULL==(fPtr=fopen(file_name, "r+")))
	{
	    printf("文件%s不存在！是否需要创建该文件？(0-NO, 1-YES)\n", file_name);
	    fclose(fPtr);
	    int choice;
	    scanf("%d", &choice);
	    while(1)
	    {
	    	if(choice==1)
	    	{
	    		if(NULL==(fPtr=fopen(file_name, "w+")))
	            {
	            	printf("创建%文s件失败！\n", file_name);
	            	break;
				}    
		        else
		        {
		        	printf("创建%文s件成功！\n", file_name);
		        	break;
				}   
			}
			else
			    if(choice==0) break;
			    else
			    {
			    	printf("输入有误！请重新输入：(1-yes, 2-no)");
			    	scanf("%d", &choice);
				}
		}
    }
	else
	{
		printf("打开文件成功！\n");
		
		int data_node_num=MAX/100+1; //一行的最大数据链表个数 
		int remain_chars=MAX%100; //一行最后一个数据链表的字符数 
		int count=0;
		
		//创建行链表的头结点并初始化 
		pData_stack=(Row_node*)malloc(sizeof(Row_node));
		pData_stack->down=NULL;
		pData_stack->right=NULL;
		
		Row_node* current_row=pData_stack;
		Row_node* last_row=NULL; 
		Data_node* current_data=NULL;
		Data_node* last_data=NULL;
		
		if(data_node_num==1){ //一行字符数小于100 
			while(!feof(fPtr)){
				//创建数据链表，并存入remain_chars个字符于数据链表的字符域
				current_data=(Data_node*)malloc(sizeof(Data_node));  
				memset(current_data->data, '\0', 100);
				current_data->right=NULL; 				
				fgets(current_data->data, remain_chars+1, fPtr);
				
				current_row->right=current_data;
				
				if(!feof(fPtr)){ //没有读到文件尾，创建下一行的行链表 
					last_row=(Row_node*)malloc(sizeof(Row_node));
					last_row->right=NULL;
					last_row->down=NULL;
					current_row->down=last_row;
					current_row=last_row;
				}
			}
		} 
		else{ //一行字符数大于100 
			while(!feof(fPtr)){
				if(NULL==current_row->right){ //判断是否为每行的第一个数据链表
					//创建数据链表，并存入100个字符于数据链表的字符域 
					current_data=(Data_node*)malloc(sizeof(Data_node));  
					memset(current_data->data,'\0',100);
					current_data->right=NULL; 				
					fgets(current_data->data, 101, fPtr);
				
					current_row->right=current_data;
					last_data=current_data;
					count++;
				
					if(strlen(current_data->data)<100){
						if(!feof(fPtr)){ //没有读到文件尾，创建下一行的行链表 
							last_row=(Row_node*)malloc(sizeof(Row_node));
							last_row->right=NULL;
							last_row->down=NULL;
							current_row->down=last_row;
							current_row=last_row;
							count=0;
						}
					}
				}
		 		else{
		 			if(count<data_node_num-1){
		 				//创建数据链表，并存入100个字符于数据链表的字符域 
		 				current_data=(Data_node*)malloc(sizeof(Data_node));  
						memset(current_data->data,'\0',100);
						current_data->right=NULL; 
						fgets(current_data->data, 101, fPtr);
				
						last_data->right=current_data;
						last_data=current_data;
						count++;
					
						if(strlen(current_data->data)<100){
							if(!feof(fPtr)){ //没有读到文件尾，创建下一行的行链表
								last_row=(Row_node*)malloc(sizeof(Row_node));
								last_row->right=NULL;
								last_row->down=NULL;
								current_row->down=last_row;
								current_row=last_row;
								count=0;
							}
						}
					}
					else{
						//创建数据链表，并存入remain_chars个字符于数据链表的字符域
						current_data=(Data_node*)malloc(sizeof(Data_node));  
						memset(current_data->data,'\0',100);
						current_data->right=NULL; 
						fgets(current_data->data, remain_chars+1, fPtr);
				
						last_data->right=current_data;
						last_data=current_data;
						count++;
					
						if(!feof(fPtr)){ //没有读到文件尾，创建下一行的行链表 
							last_row=(Row_node*)malloc(sizeof(Row_node));
							last_row->right=NULL;
							last_row->down=NULL;
							current_row->down=last_row;
							current_row=last_row;
							count=0;
						}
					}
				}
			}
		}
	}
	fclose(fPtr);
	return 0;
}

void save_file()
{
	FILE* fptr;
	Row_node* current_row=pData_stack;
	Data_node* current_data=NULL;
	Data_node* temp_data=NULL;
		
	printf("文件名是%s，是否重置文件名？(1-yes, 2-no)\n", file_name);
	//重置文件名 
	int choice;
    scanf("%d", &choice);
    while(1)
    {
    	if(choice==1)
        {
    	    char new_file_name[20];
    	    printf("请输入新文件名：");
    	    getchar();
		    gets(new_file_name);
		    strcat(new_file_name, ".txt");
		    if(rename(file_name, new_file_name)==0)
		    {
		        printf("重置文件名成功！新文件名为%s\n", new_file_name);
		        fptr=fopen(new_file_name,"w");
		    }
		    else
		        printf("重置文件名失败！\n");
		    break;
	    }
	    else
		{
			if(choice==2) 
			{
				fptr=fopen(file_name,"w");
				break;
			}
			else
			{
				printf("输入有误，请重新输入：(1-yes, 2-no)");
				scanf("%d", &choice);
			}     
		} 
	}
	
	while(current_row!=NULL) //判断是否读到最后一行 
	{
		current_data=current_row->right;
		while(current_data!=NULL) //判断是否为该行的最后一个数据链表 
		{
			temp_data=current_data;
			current_data=current_data->right;
			temp_data->right=NULL;
			fputs(temp_data->data, fptr); //将数据链表的字符域保存到文件中 
			temp_data->right=current_data;			
		}
		current_row=current_row->down;
	}
	fclose(fptr); //关闭文件 
}

