#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<sys/time.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

int ticks=0;
pthread_t trigger_thread[1];
//pthread_attr_t attr;
pthread_cond_t trigger = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *time_triggered()
{
	pthread_mutex_lock(&mutex);
	printf("asdfasf\n");
	time_t current_time;
	struct tm *t;
	struct timeval tv;
	while(1)
	{
		pthread_cond_wait(&trigger, &mutex);
		printf("\n");//if delete this line, don't work...I don't know why
		gettimeofday(&tv, NULL);
		t = localtime(&tv.tv_sec);
		printf("y-%d m-%d d-%d %d:%d:%d ", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
		//print current time
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void alarm_handler(int signo)
{
//	printf("Timer Hit\n");
	pthread_mutex_lock(&mutex);
	ticks++;
	if(ticks % 100 == 0)
	{
		ticks = 0;
		pthread_cond_signal(&trigger);//wake up the thread
	}
	pthread_mutex_unlock(&mutex);
	signal(SIGALRM, alarm_handler);
}

int main(int argc, char* argv[])
{

	struct itimerval delay;
	int ret;
	int rc;//thread id

	signal(SIGALRM, alarm_handler);
	delay.it_value.tv_sec = 0;//first alarm
	delay.it_value.tv_usec = 10000;//micro sec
	delay.it_interval.tv_sec = 0;//periodic
	delay.it_interval.tv_usec = 10000;//micro sec

	//ret = setitimer(ITIMER_REAL, &delay, NULL);
	rc = pthread_create(&trigger_thread[0], NULL, time_triggered, NULL);
	if(rc)
	{
		printf("Error %d\n", rc);
		exit(-1);
	}
	
	ret = setitimer(ITIMER_REAL, &delay, NULL);
	if(ret) 
	{ 
		perror("setitimer"); 
		return 0; 
	}
	while(1)
		pause();

	return 0;
}
