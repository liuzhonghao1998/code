#include<stdio.h>
#include<conio.h>
#include<time.h>
int main()
{
	clock_t t0,dt;
	int flag;
	int x;
	t0=clock();
	flag=1;
	printf("�����룺\n");
	while(!_kbhit()){
		dt=clock()-t0;
		if(dt>5*CLOCKS_PER_SEC){
			flag=0;
			printf("��ʱ�ˣ�\n");
		}
		scanf("%d",&x);
		printf("%d",x);
	}
	return 0;
 } 
