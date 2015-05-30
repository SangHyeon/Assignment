#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<sys/time.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

int ticks=0;
pthread_t trigger_thread;
pthread_cond_t trigger = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *time_triggered()
{
	//set time
	time_t current_time;
	struct tm *t;
	time_t timer = time(NULL);
	pthread_mutex_lock(&mutex);
	while(1)
	{
		pthread_cond_wait(&trigger, &mutex);//wait signal...
		timer = time(NULL);
		t = localtime(&timer);//get time
		printf("y-%d m-%d d-%d %d:%d:%d \n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void alarm_handler(int signo)
{
	pthread_mutex_lock(&mutex);
	ticks++;//increase tick for 10ms
	if(ticks%100 == 0)//1sec
	{
		ticks = 0;
		pthread_cond_signal(&trigger);//wake up the thread
	}
	pthread_mutex_unlock(&mutex);
	signal(SIGALRM, alarm_handler);//set SIGALRM handler again
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

	rc = pthread_create(&trigger_thread, NULL, time_triggered, NULL);
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
