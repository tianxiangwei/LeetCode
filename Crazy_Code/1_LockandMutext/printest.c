/*
 * =====================================================================================
 *
 *       Filename:  printest.c
 *
 *    Description:  usage of lock and mutex
 *
 *        Version:  1.0
 *        Created:  10/14/2017 10:29:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiangwei.tian (), tianxiangwei@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>


/*  static pthread_t pthread_A;
static pthread_t pthread_B;
pthread_mutex_t mutex_A;
pthread_cond_t cond_A;

pthread_mutex_t mutex_B;
pthread_cond_t cond_B;

void* fun_A(void *arg)
{
	static int count=1;
	while(1)
	{
		pthread_mutex_lock(&mutex_A);
		printf("%d  ",count++);
		printf("A,");
		pthread_cond_signal(&cond_B);
		printf("before wait cond_A\n");
		pthread_cond_wait(&cond_A,&mutex_A);
		printf("after wait cond_A\n");
		pthread_mutex_unlock(&mutex_A);
	}
}

void* fun_B(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex_B);
		printf("before wait cond_B\n");
		pthread_cond_wait(&cond_B,&mutex_B);
		printf("B\n");
		pthread_cond_signal(&cond_A);
		pthread_mutex_unlock(&mutex_B);
	}
}*/
int num=0;
pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qready=PTHREAD_COND_INITIALIZER;

void* thread_func(void *arg)
{
	int param=(int)arg;
	int count=1;
	while(1)
	{
		//printf("%c ready to lock\n",param+'A');
		
		pthread_mutex_lock(&mylock);

		while(param!=num)
			pthread_cond_wait(&qready,&mylock);
		/*if(num==0)
			printf("%d  %c ,",count++,param+'A');
		else
			printf("%c\n",param+'A');
			*/

		printf("%c\n",param+'A');

		num=(num+1)%3;
		pthread_mutex_unlock(&mylock);
		pthread_cond_broadcast(&qready);
	}
}

int main()
{
	int ret=0;
	int i=0;
	/*  pthread_mutex_init(&mutex_A,NULL);
	pthread_mutex_init(&mutex_B,NULL);
	pthread_cond_init(&cond_A,NULL);
	pthread_cond_init(&cond_B,NULL);

	ret=pthread_create(&pthread_A,NULL,fun_A,NULL);
	if(ret!=0)
	{
		printf("create thread_A failed");
		return -1;
	}

	ret=pthread_create(&pthread_B,NULL,fun_B,NULL);
	if(ret!=0)
	{
		printf("create thread_B failed");
		return -1;
	}*/
	pthread_t tid[3];
	for(i=0;i<3;i++)
		pthread_create(&tid[i],NULL,thread_func,(void *)i);
	getchar();
	return 0;
}

