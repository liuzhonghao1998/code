#include <windows.h>
#include <conio.h>
#include<stdio.h> 
int main()
{
    printf("�����������֮��ʲôҲ�����룬�Ҿ����-1��\n");
    Sleep(3000);
    if(!_kbhit())
        printf("-1\n");
    else
        printf("������%c", getchar());
    return 0;
}
