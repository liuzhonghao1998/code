#include<time.h>
extern int current_time;
void time_count()
{
	double duration;
	clock_t start,finish;
	duration=0.0;
	start=clock();
	while(duration<1.0){
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC; 
	}
	current_time++;
}
