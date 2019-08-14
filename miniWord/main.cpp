#include<windows.h>
#include"struct.h"
#include"screen.h"
#include"file.h"



int main()
{
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	int exit=0;
	
	Openfile();       
    coord.X=0;
    coord.Y=0;
    SetConsoleCursorPosition(hout,coord);
    
   	Outputscreen();
   	coord.X=0;
   	coord.Y=3;
    SetConsoleCursorPosition(hout,coord);
	
	while(exit==0)
	{
		exit=Boardinput(); 
	}
}
