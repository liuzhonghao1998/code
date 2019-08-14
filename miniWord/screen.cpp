#include"struct.h"
#include<iostream>
#include<conio.h>
#include"file.h"
#include"add.h"
#include"delete.h"
#include"search.h"
#include"replace.h"
using namespace std;
void Outputscreen()
{
	Row_node* pRow=NULL;
	Data_node* pData=NULL;
	int i=0;
	
	system("CLS");
	cout<<"------"<<endl;
	cout<<"|菜单|"<<endl;
	cout<<"------"<<endl;
	pRow=pData_stack;
	while(pRow!=NULL)
	{
		pData=pRow->right;
		while(pData!=NULL)
		{
			if(pData->data[i]!='\0'&&pData->data[i]!='\n')
			{
				cout<<pData->data[i];
			}
			else
			{
				pData=pData->right;
				i=0;
				continue;
			}
			if(i<99)
			{
				i++;
			}
			else
			{
				i=0;
				pData=pData->right;
			}
		}
		if(pRow->down!=NULL)
		{
			cout<<endl;
		}
		pRow=pRow->down;
	}
}

int Select()
{
	int choice=0,choice1=0,x=0,y=0;
	char str[101],str1[101];
	while(1)
	{
		cout<<"1.新建文件"<<endl;
		cout<<"2.打开文件"<<endl;
		cout<<"3.保存文件" <<endl;
		cout<<"4.查找"<<endl;
		cout<<"5.替换"<<endl;
		cout<<"6.退出程序"<<endl;
		cout<<"7.返回"<<endl; 
		cout<<"请输入功能：";
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				cout<<"是否保存当前文件？(1-是，2-否)";
				cin>>choice1;
				if(choice1==1)
				{
					save_file();
				}
				getchar();
				delete_stack();
				Newfile();
				break;
			case 2:
				cout<<"是否保存当前文件？(1-是，2-否)";
				cin>>choice1;
				if(choice1==1)
				{
					save_file();
				}
				getchar();
				delete_stack();
				Openfile();
				break;
			case 3:
				save_file();
				break;
			case 4:
				getchar();
				cout<<"输入要查找的字符串："; 
				memset(str,'\0',101);
				gets(str);
				cout<<"输入查找起始位置坐标：";
				cin>>y>>x;
				search(str,x-1,y-1);
				break;
			case 5: 
				cout<<"输入原字符串：";
				memset(str,'\0',101);
				getchar();
				gets(str);
				cout<<"输入新字符串：";
				memset(str1,'\0',101);
				gets(str1);
				cout<<"输入查找起始位置坐标：";
				cin>>y>>x;
				replace(str,str1,x-1,y-1);
				break;
			case 6:
				cout<<"是否保存当前文件？(1-是，2-否)";
				cin>>choice1;
				if(choice1==1)
				{
					save_file();
				}
				break;
			case 7:
				break;
			default:
				cout<<"输入选项有误"<<endl;
				break; 
		}
		if(choice>=1&&choice<=7)
			return choice;
	} 
}

int Boardinput()
{
	char ch;
	int choice=0,x=0,y=0,X=0,Y=0,c=0;
	char* match=NULL;
	Data_node* D;
	Row_node* R ,*R1;       	
	while(!kbhit()){}
	c=getch();
	ch=(char)c;
    GetConsoleScreenBufferInfo(hout,&csbi);
    coord.X=csbi.dwCursorPosition.X; //得到坐标X的值
    coord.Y=csbi.dwCursorPosition.Y; //得到坐标Y的值
        
    if(coord.X>=0&&coord.X<=5&&coord.Y>=0&&coord.Y<=2)
    {
        if (ch == 0x0D)
        {
        	system("CLS");
        	choice=Select();
        	system("CLS");
        	if((choice>=1&&choice<=3)||choice==7)
        	{
        		coord.X=0;
    			coord.Y=0;
    			SetConsoleCursorPosition(hout,coord);
    			Outputscreen();
   				coord.X=0;
   				coord.Y=3;
    			SetConsoleCursorPosition(hout,coord);
			}
			if(choice==4||choice==5)
			{
				x=coord.X;
				y=coord.Y;
				coord.X=0;
    			coord.Y=0;
    			SetConsoleCursorPosition(hout,coord);
    			Outputscreen();
    			coord.X=x;
    			coord.Y=y;
				SetConsoleCursorPosition(hout,coord);
			}
			if(choice==6)
			{
				system("pause");
				return 1;
			}
		}
	}
        
    else if(coord.Y>=3)
    {
        coord.Y-=3;
        X=0;Y=0;x=0;
        	
    	if((pData_stack!=NULL)&&(c == 0xE0 || c == 0x08 || c == 0x7F))  
    	{  
    		R = pData_stack;
			R1 = pData_stack;
        	X = coord.X;
        	while(Y<coord.Y){
        		if(R->down!=NULL)R = R->down;
        		else
				{
					R=(Row_node*)malloc(sizeof(Row_node));
					R->down=NULL;
					R->right=NULL;
					R1->down=R;
					D=(Data_node*)malloc(sizeof(Data_node));
					D->right=NULL;
					memset(D->data,'\0',100);
					R->right=D;
				}
        		Y++;
				if (Y == coord.Y - 1) R1 = R;
			}
			D = R->right;
			while(x<(coord.X/100)){
				if(D->right!=NULL)D = D->right;
				else
				{
					D->right=(Data_node*)malloc(sizeof(Data_node));
					D=D->right;
					D->right=NULL;
					memset(D->data,'\0',100);
				}
					x++;
			}
			match = D->data;
			x=0;
			while(x<(coord.X%100)){  //match定位到光标的位置 
				match++;
				x++; 
			} 
				
			if(c==0xE0)
			{
				while(!kbhit()){}
        		c=getch();
			}  
			      		
        	if (c == 0x48)//上  
        	{  
        		if(R1==R&&coord.X<=5)  //第一行
        		{
					coord.Y-=2;
				}
				else
				{
				if (coord.Y != 0) {
					coord.Y--;
					x = 0;
					D = R1->right;
					match = D->data;
					while (*match != '\0') {
						if (x % 100 == 0 && x > 0 && D->right != NULL) {
							D = D->right;
							match = D->data;
						}
						else match++, x++;
					}
					if(coord.X>=x)coord.X = x - 1;
				}
				else
				{
					coord.Y=-2;
					coord.X=1; 
				}
				}	
        	}  
        	else if (c == 0x50)//下  
        	{  
        		if(R->down!=NULL) 
        		{
					coord.Y++; 
					R = R->down;
					x = 0;
					D = R->right;
					match = D->data;
					while (*match != '\0') {
						if (x % 100 == 0 && x > 0 && D->right != NULL) {
							D = D->right;
							match = D->data;
						}	
						else match++, x++;
					}
					if(coord.X>=x&&x!=0)coord.X = x - 1;
					else if(x==0)coord.X=0;  
				}
				else
				{
					x=coord.X;
					while(x<MAX-1&&*match!='\0'){
						if (x % 100 == 0 && x > 0 && D->right != NULL) 
						{
								D = D->right;
								match = D->data;
						}
						else match++ , x++;	
					}
					if(x==MAX-1&&*match!='\0') 
					{
						coord.Y++;
						coord.X=0;
					}
				} 
        	}  
        	else if (c == 0x4B)//左  
        	{  
            	if (coord.X != 0)  
                	coord.X--;
				else if (coord.X == 0 && R1 != R) {
					D = R1->right;
					x = 0;
					match = D->data;
					while (*match != '\0') {
						if (x % 100 == 0 && x > 0 && D->right != NULL) {
							D = D->right;
							match = D->data;
						}
						else match++, x++;
					}
					coord.X = x - 1;
					coord.Y--;
				}
        	}  
        	else if(c == 0x4D)//右  
        	{
        		if((coord.X%100)<99)match++;
        		else if((coord.X)%100==99&&D->right!=NULL) 
				{
					D = D->right;
					match=D->data;
				}
				if ((*match== '\0'&&*(match-1)=='\n'&&R->down != NULL)||(coord.X==MAX-1&&*(match-1)!='\0')) {   //光标在最右边再按右
					coord.X = 0;
					coord.Y++;
				}else if (*match != '\0' || (R->down == NULL&&*(match - 1) != '\0')) {//普通情况，最后一行没有\n
					coord.X++;
				}
        	}
			else if(c == 0x08||c == 0x53)//退格 ，删除
			{
				if (c == 0x08)
				{
					if (coord.Y != 0) {   //判断是不是在第一行
						if (coord.X == 0)
						{
							D = R1->right;
							match = D->data;
							x = 0; //预设值为下一个字符应该在的位置
							while (*match != '\0') {
								if (x % 100 == 0 && x > 0 && D->right != NULL) {
									D = D->right;
									match = D->data;
								}
								else match++, x++;
							}
							screen_bd(c, coord.X, coord.Y);
							coord.X = x - 1;
							coord.Y--;
						}
						else {
							screen_bd(c, coord.X, coord.Y);
							coord.X--;
						}
					}else if(coord.X!=0){
							screen_bd(ch, coord.X, coord.Y);
							coord.X--;
					}
				}
				else
					{
						screen_bd(c, coord.X, coord.Y);
					}
				coord.Y+=3;					
				x=coord.X;
				y=coord.Y;
				coord.X=0;
    			coord.Y=0;
    			SetConsoleCursorPosition(hout,coord);
    			Outputscreen();
				coord.X=x;
				coord.Y=y;
				SetConsoleCursorPosition(hout,coord);   	
			}
			if(c == 0x48||c==0x50||c==0x4B||c==0x4D)
			{
				coord.Y+=3;
        		SetConsoleCursorPosition(hout, coord);//定位光标  
        	}
    	}
		else if(c==0x0D)
		{
			Addchar(ch,coord.X,coord.Y);
			coord.X=0;
			coord.Y++;
			coord.Y+=3;					
			x=coord.X;
			y=coord.Y;
			coord.X=0;
    		coord.Y=0;
    		SetConsoleCursorPosition(hout,coord);
    		Outputscreen();
			coord.X=x;
			coord.Y=y;
			SetConsoleCursorPosition(hout,coord); 
		}
		else if(c != 0xE0 && c != 0x08 && c != 0x7F)
		{
			Addchar(ch,coord.X,coord.Y);
			if(coord.X==MAX-1)
			{
				coord.X=0;
				coord.Y++;
			}
			else
			{
				coord.X++;
			}
			coord.Y+=3;					
			x=coord.X;
			y=coord.Y;
			coord.X=0;
    		coord.Y=0;
    		SetConsoleCursorPosition(hout,coord);
    		Outputscreen();
			coord.X=x;
			coord.Y=y;
			SetConsoleCursorPosition(hout,coord); 
		}
		if(c==0xE0)
		{
			while(!kbhit()){}
        	c=getch();
		}  
	}
	return 0;
}

