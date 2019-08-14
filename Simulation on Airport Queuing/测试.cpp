#include <windows.h>
#include <conio.h>
#include<stdio.h> 
int main()
{
    printf("如果你三秒钟之内什么也不输入，我就输出-1。\n");
    Sleep(3000);
    if(!_kbhit())
        printf("-1\n");
    else
        printf("输入了%c", getchar());
    return 0;
}
