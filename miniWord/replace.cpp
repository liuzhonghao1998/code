#include"struct.h"
#include"add.h"
#include"delete.h"
#include"search.h"
void replace(char old_string[], char new_string[],int x,int y) 
{
	search(old_string,x,y); //调用查找函数定位坐标	 
	x=coord.X;
	y=coord.Y-3;
	int i=0;
	const int old_string_len=strlen(old_string); //主串长度 
	const int new_string_len=strlen(new_string); //子串长度 
	
	for(i=0;i<=old_string_len-1;i++)
	{
		screen_bd(0x53,x,y);
	}
	for(i=0;i<=new_string_len-1;i++)
	{
		Addchar(new_string[i],x,y);
	}
}

