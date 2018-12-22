#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//线程所需头文件
#include <pthread.h>



#define NLOOP	5000
int counter = 0;

//静态初始化互斥量（静态初始化要比动态初始化好）
pthread_mutex_t	counter_mutex = PTHREAD_MUTEX_INITIALIZER;


void *add(void *arg)
{
	int i = 0;
	int val = 0;
	
	for (i = 0; i < NLOOP; i++) {
		//阻塞获取互斥量
		pthread_mutex_lock(&counter_mutex);
		
		val = counter;
		//printf调用，它会执行write系统调用进内核，为内核调度别的线程执行提供了一个很好的时机
		printf("%s %x: val:%d\n", (char *)arg, (unsigned int)pthread_self(), val);
		counter++;
		
		//解除互斥量
		pthread_mutex_unlock(&counter_mutex);
		
	}
	
	return NULL;
}


int main(void)
{
	pthread_t tid1, tid2;
	int err;
	
	err = pthread_create(&tid1, NULL, add,"thread1");
	if (err != 0) {
		fprintf(stderr, "pthread_create\n");
		exit(1);
	}
	
	err = pthread_create(&tid2, NULL, add,"thread2");
	if (err != 0) {
		fprintf(stderr, "pthread_create\n");
		exit(1);
	}
	
	pthread_join(tid1, NULL);
	pthread_join(tid1, NULL);
	
	printf("\nEND counter:%d\n",counter);
}