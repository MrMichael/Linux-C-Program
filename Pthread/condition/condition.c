#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//线程所需头文件
#include <pthread.h>

//程序演示一个生产者-消费者的例子，生产者生产一个结构体串在链表的表头上，消费者从表头取走结构体。


//定义链表
struct msg {
	struct msg *next;
	int value;
};

struct msg *head;

//静态初始化互斥量
pthread_mutex_t product_mutex = PTHREAD_MUTEX_INITIALIZER;

//静态初始化条件变量
pthread_cond_t	product_cond = PTHREAD_COND_INITIALIZER;	


void *consumer(void *arg)
{
	struct msg *mp;
	
	while (1) {
		//阻塞获取互斥量
		pthread_mutex_lock(&product_mutex);
		while (head == NULL) {
			//释放互斥量并阻塞线程，直到被唤醒时重新获取互斥量
			pthread_cond_wait(&product_cond, &product_mutex);
		}
		//修改全局变量
		mp = head;
		head = mp->next;
		//释放互斥量
		pthread_mutex_unlock(&product_mutex);
		
		printf("Consume %d\n", mp->value);
		//释放内存空间
		free(mp);
		sleep(rand() % 5);
	}
	
	
	return NULL;
}


void *producer(void *arg)
{
	struct msg *mp;
	
	while (1) {
		//申请内存空间
		mp = malloc(sizeof(struct msg));
		mp->value = rand() % 1000 + 1;
		printf("Produce %d\n", mp->value);
		
		//阻塞获取互斥量
		pthread_mutex_lock(&product_mutex);
		//修改全局变量
		mp->next = head;
		head = mp;
		//释放互斥量
		pthread_mutex_unlock(&product_mutex);
		
		//唤醒一个在等待条件变量的线程
		pthread_cond_signal(&product_cond);
		sleep(rand() % 5);
	}
	
	
	
	return NULL;
}



int main(void)
{
	pthread_t tid_p, tid_c;
	int err;
	
	//设置随机数种子
	srand(time(NULL));
	
	err = pthread_create(&tid_p, NULL, producer, "thread producer");
	if (err != 0) {
		fprintf(stderr, "pthread_create\n");
		exit(1);
	}
	
	err = pthread_create(&tid_p, NULL, consumer, "thread consumer");
	if (err != 0) {
		fprintf(stderr, "pthread_create\n");
		exit(1);
	}
	
	pthread_join(tid_p, NULL);
	pthread_join(tid_c, NULL);
	
	return 0;
}