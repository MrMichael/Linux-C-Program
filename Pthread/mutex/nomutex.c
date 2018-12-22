#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//线程所需头文件
#include <pthread.h>


//运行两个线程，将某个计数器各累加5000次，看结果是否为10000次?
//在多处理器平台下运行结果为10000，但是在单处理器下运行少于10000

#define NLOOP	5000
int counter = 0;

void *add(void *arg)
{
	int i = 0;
	int val = 0;
	
	for (i = 0; i < NLOOP; i++) {
		val = counter;
		//printf调用，它会执行write系统调用进内核，为内核调度别的线程执行提供了一个很好的时机
		printf("%s %x: val:%d\n", (char *)arg, (unsigned int)pthread_self(), val);
		counter++;
	}
	
	return NULL;
}


int main(void)
{
	pthread_t tid1, tid2;
	int err;
	
	err = pthread_create(&tid1, NULL, add, "thread1");
	if (err != 0) {
		fprintf(stderr, "pthread_create\n");
		exit(1);
	}
	err = pthread_create(&tid2, NULL, add, "thread2");
	if (err != 0) {
		fprintf(stderr, "pthread_create\n");
		exit(1);
	}
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	printf("\nEND counter:%d\n",counter);
	
	
	return 0;
}