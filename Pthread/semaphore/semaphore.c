#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//线程所需头文件
#include <pthread.h>
//信号量所需头文件
#include <semaphore.h>

//生产者－消费者的例子是基于链表的，其空间可以动态分配，
//现在基于固定大小的环形队列重写这个程序

#define NUM		5
int queue[NUM];
sem_t blank_number, product_number;


void *producer(void *arg)
{
	int  p = 0;
	
	while (1) {
		//等待信号量
		sem_wait(&blank_number);
		queue[p] = rand() % 1000 + 1;
		printf("Produce %d\n", queue[p]);
		//释放信号量
		sem_post(&product_number);
		p = (p+1)%NUM;
		sleep(rand()%5);
	}
}

void *consumer(void *arg)
{
	int c = 0;
	
	while(1) {
		sem_wait(&product_number);
		printf("Comsume %d\n", queue[c]);
		queue[c] = 0;
		sem_post(&blank_number);
		c = (c+1)%NUM;
		sleep(rand()%5);
	}
}


int main(void)
{
	pthread_t tid1, tid2;
	int err;
	
	//初始化信号量,0代表信号量用于线程间同步，NUM代表信号量可用资源数量
	sem_init(&blank_number, 0, NUM);
	sem_init(&product_number, 0, 0);
	//创建线程
	err = pthread_create(&tid1, NULL, producer, NULL);
	if (err != 0) {
		fprintf(stderr, "pthread_create\n");
		exit(1);
	}
	err = pthread_create(&tid2, NULL, consumer, NULL);
	if (err != 0) {
		fprintf(stderr, "pthread_create\n");
		exit(1);
	}
	//等待线程退出
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	//删除信号量
	sem_destroy(&blank_number);
	sem_destroy(&product_number);
	
	return 0;
}

