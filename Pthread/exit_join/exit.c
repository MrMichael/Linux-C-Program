#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//线程所需头文件
#include <pthread.h>


void *thread1_handler(void *arg)
{
	printf("%s running\n", (char*)arg);
	return (void *)1;	//return 终止线程返回return值
}

void *thread2_handler(void *arg)
{
	printf("%s running\n", (char*)arg);
	pthread_exit((void *)2); //pthread_exit终止线程返回其参数值
}

void *thread3_handler(void *arg)
{
	while (1) {
		printf("%s waiting\n", (char*)arg);
		sleep(1);
	}
	//线程被异常终止，返回常数PTHREAD_CANCELED，即-1。
}



int main(void)
{
	pthread_t tid1, tid2, tid3;
	void *ptr;
	int err;
	
	//thread 1
	err = pthread_create(&tid1, NULL, thread1_handler, "new thread1");
	if (err != 0) {
		fprintf(stderr, "pthread_create1\n");
		exit(1);
	}
	
	//阻塞等待thread 1终止  （主进程同时也是一个线程）
	err = pthread_join(tid1, &ptr);
	if (err != 0) {
		fprintf(stderr, "pthread_join\n");
		exit(1);
	}
	printf("thread1 exit code %d\n", (int)ptr);
	
	//thread 2
	err = pthread_create(&tid2, NULL, thread2_handler, "new thread2");
	if (err != 0) {
		fprintf(stderr, "pthread_create2\n");
		exit(1);
	}
	
	//阻塞等待thread 2终止
	err = pthread_join(tid2, &ptr);
	if (err != 0) {
		fprintf(stderr, "pthread_join\n");
		exit(1);
	}
	printf("thread2 exit code %d\n", (int)ptr);
	
	//thread 3
	err = pthread_create(&tid3, NULL, thread3_handler, "new thread3");
	if (err != 0) {
		fprintf(stderr, "pthread_create3\n");
		exit(1);
	}
	
	sleep(3);
	//主线程将thread 3异常终止
	pthread_cancel(tid3);
	//阻塞等待thread 3终止
	err = pthread_join(tid3, &ptr);
	if (err != 0) {
		fprintf(stderr, "pthread_join\n");
		exit(1);
	}
	printf("thread3 exit code %d\n", (int)ptr);
	
	
	return 0;
}










