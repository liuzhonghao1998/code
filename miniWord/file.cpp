#include"struct.h"
#include<stdio.h>
#include<iostream>
using namespace std;

Row_node* pData_stack;	
char file_name[20];
int next[100];
HANDLE hout;
COORD coord;
CONSOLE_SCREEN_BUFFER_INFO csbi; //����̨��Ļ��������Ϣ

int Newfile()
{
	FILE *fPtr;
	cout<<"�������ļ�����"; 
	gets(file_name);
	strcat(file_name, ".txt");
	if(NULL==(fPtr=fopen(file_name, "w")))
	    printf("�½��ļ�ʧ�ܣ�");
	else
	    printf("�½��ļ��ɹ����ļ�����Ϊ��%s", file_name);
	fclose(fPtr);
	return 0;
}

void delete_stack()
{
	Row_node* current_row=pData_stack;
	Row_node* temp_row=NULL;
	Data_node* current_data=NULL;
	Data_node* temp_data=NULL;
	while(current_row!=NULL) //�ж��Ƿ�������һ�� 
	{
		current_data=current_row->right;
		while(current_data!=NULL) //�ж��Ƿ�Ϊ���е����һ���������� 
		{
			temp_data=current_data;
			current_data=current_data->right;
			free(temp_data); //�ͷ��������� 
		}
		temp_row=current_row;
		current_row=current_row->down;
		free(temp_row); //�ͷ������� 
	}
	pData_stack=NULL;
}

int Openfile()
{ 
	FILE *fPtr;
	memset(file_name,'\0',20);
	printf("��������Ҫ�򿪵��ļ�����"); 
	gets(file_name);
	strcat(file_name, ".txt");
	if(NULL==(fPtr=fopen(file_name, "r+")))
	{
	    printf("�ļ�%s�����ڣ��Ƿ���Ҫ�������ļ���(0-NO, 1-YES)\n", file_name);
	    fclose(fPtr);
	    int choice;
	    scanf("%d", &choice);
	    while(1)
	    {
	    	if(choice==1)
	    	{
	    		if(NULL==(fPtr=fopen(file_name, "w+")))
	            {
	            	printf("����%��s��ʧ�ܣ�\n", file_name);
	            	break;
				}    
		        else
		        {
		        	printf("����%��s���ɹ���\n", file_name);
		        	break;
				}   
			}
			else
			    if(choice==0) break;
			    else
			    {
			    	printf("�����������������룺(1-yes, 2-no)");
			    	scanf("%d", &choice);
				}
		}
    }
	else
	{
		printf("���ļ��ɹ���\n");
		
		int data_node_num=MAX/100+1; //һ�е��������������� 
		int remain_chars=MAX%100; //һ�����һ������������ַ��� 
		int count=0;
		
		//�����������ͷ��㲢��ʼ�� 
		pData_stack=(Row_node*)malloc(sizeof(Row_node));
		pData_stack->down=NULL;
		pData_stack->right=NULL;
		
		Row_node* current_row=pData_stack;
		Row_node* last_row=NULL; 
		Data_node* current_data=NULL;
		Data_node* last_data=NULL;
		
		if(data_node_num==1){ //һ���ַ���С��100 
			while(!feof(fPtr)){
				//������������������remain_chars���ַ�������������ַ���
				current_data=(Data_node*)malloc(sizeof(Data_node));  
				memset(current_data->data, '\0', 100);
				current_data->right=NULL; 				
				fgets(current_data->data, remain_chars+1, fPtr);
				
				current_row->right=current_data;
				
				if(!feof(fPtr)){ //û�ж����ļ�β��������һ�е������� 
					last_row=(Row_node*)malloc(sizeof(Row_node));
					last_row->right=NULL;
					last_row->down=NULL;
					current_row->down=last_row;
					current_row=last_row;
				}
			}
		} 
		else{ //һ���ַ�������100 
			while(!feof(fPtr)){
				if(NULL==current_row->right){ //�ж��Ƿ�Ϊÿ�еĵ�һ����������
					//������������������100���ַ�������������ַ��� 
					current_data=(Data_node*)malloc(sizeof(Data_node));  
					memset(current_data->data,'\0',100);
					current_data->right=NULL; 				
					fgets(current_data->data, 101, fPtr);
				
					current_row->right=current_data;
					last_data=current_data;
					count++;
				
					if(strlen(current_data->data)<100){
						if(!feof(fPtr)){ //û�ж����ļ�β��������һ�е������� 
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
		 				//������������������100���ַ�������������ַ��� 
		 				current_data=(Data_node*)malloc(sizeof(Data_node));  
						memset(current_data->data,'\0',100);
						current_data->right=NULL; 
						fgets(current_data->data, 101, fPtr);
				
						last_data->right=current_data;
						last_data=current_data;
						count++;
					
						if(strlen(current_data->data)<100){
							if(!feof(fPtr)){ //û�ж����ļ�β��������һ�е�������
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
						//������������������remain_chars���ַ�������������ַ���
						current_data=(Data_node*)malloc(sizeof(Data_node));  
						memset(current_data->data,'\0',100);
						current_data->right=NULL; 
						fgets(current_data->data, remain_chars+1, fPtr);
				
						last_data->right=current_data;
						last_data=current_data;
						count++;
					
						if(!feof(fPtr)){ //û�ж����ļ�β��������һ�е������� 
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
		
	printf("�ļ�����%s���Ƿ������ļ�����(1-yes, 2-no)\n", file_name);
	//�����ļ��� 
	int choice;
    scanf("%d", &choice);
    while(1)
    {
    	if(choice==1)
        {
    	    char new_file_name[20];
    	    printf("���������ļ�����");
    	    getchar();
		    gets(new_file_name);
		    strcat(new_file_name, ".txt");
		    if(rename(file_name, new_file_name)==0)
		    {
		        printf("�����ļ����ɹ������ļ���Ϊ%s\n", new_file_name);
		        fptr=fopen(new_file_name,"w");
		    }
		    else
		        printf("�����ļ���ʧ�ܣ�\n");
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
				printf("�����������������룺(1-yes, 2-no)");
				scanf("%d", &choice);
			}     
		} 
	}
	
	while(current_row!=NULL) //�ж��Ƿ�������һ�� 
	{
		current_data=current_row->right;
		while(current_data!=NULL) //�ж��Ƿ�Ϊ���е����һ���������� 
		{
			temp_data=current_data;
			current_data=current_data->right;
			temp_data->right=NULL;
			fputs(temp_data->data, fptr); //������������ַ��򱣴浽�ļ��� 
			temp_data->right=current_data;			
		}
		current_row=current_row->down;
	}
	fclose(fptr); //�ر��ļ� 
}

