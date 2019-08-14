#include"struct.h"
#include<stdio.h>
void get_next(char const *T) 
{
	int i=0;
	int j=-1;
	next[i]=j;
	while(i<strlen(T)){
		if(j==-1 || T[i]==T[j]){
			++i;
			++j;
			next[i]=j;
		}
		else
		    j=next[j];
	}
}

void search(char const str[],int x,int y)
{
	get_next(str);
	int data_node_num=MAX/100+1;
	int remain_chars=MAX%100;
	Row_node* current_row=pData_stack; //当前行链表 
	Data_node* current_data=NULL; //当前数据链表 
	//根据光标位置定位到相应的行链表和数据链表 
	for(int i=0; i<y; i++)  
		current_row=current_row->down;
	current_data=current_row->right;
	for(int j=1; j<=x/100; j++)  
	    current_data=current_data->right;

	int str_len=strlen(str);
	int i=x%100;
	int j=0;
	int current_x=x/100+1; //当前行的第current_x个数据链表 
	int current_y=y; //当前第current_y行
	
	//查找的KMP算法 
	while(j<=(str_len-1) && current_row!=NULL){
		if(j==-1 || current_data->data[i]==str[j]){
			i++;
			j++;			
			if(current_x<data_node_num){
				if(i>99){ //当前数据链表查找完毕之后查找下一个数据链表 
					current_data=current_data->right;
					current_x++;
					i=0;
				}
			}
			else{
				if(i>remain_chars-1){ //当前行查找完毕查找下一行 
					current_row=current_row->down;
					current_data=current_row->right;
					current_x=1;
					current_y++;
					i=0;
				}
			}
			//遇到换行符查找下一段或到文件尾
			if(current_data->data[i]=='\n' || current_data->data[i]=='\0'){ 
				current_row=current_row->down;
				if(current_row!=NULL)
					current_data=current_row->right;
				current_x=1;
				current_y++;
				i=0;
				j=0;
			}
		}
		else
			j=next[j];
	}
	if(j>=str_len) //查找成功，定位光标到查找的字符串前 
	{
		printf("查找成功！"); 
		if(current_x==1){
			if((i+1)>str_len){
				x=i-str_len;
				y=current_y;
			}
			else{
				x=MAX-str_len+i;
				y=current_y-1;
			}
		}
		else{
			x=100*(current_x-1)+i-str_len;
			y=current_y;
		}
		coord.X=x;
		coord.Y=y+3;
	}
	else
	{
	    printf("查找失败，不存在该字符串！"); 
	    system("pause");
	}
}

