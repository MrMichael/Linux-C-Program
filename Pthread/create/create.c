#include <stdio.h>
#include <stdlib.h>
//线程所需要的头文件
#include <pthread.h>
//getpid需要的头文件
#include <unistd.h>

//线程编译需要加上-lpthread


int temp = 0;


void printids(char *s)
{
	pid_t pid;
	pthread_t tid;
	
	pid = getpid();
	tid = pthread_self();//获取当前线程id
	//由于pthread_t并不是一个整型，所以需要做强制类型转换
	printf("%s pid:%d, tid:%u\n", s, pid, (unsigned int)tid);
	
}


//线程处理函数
void  *thread_handler(void *arg)
{
	static int value = 0;
	
	temp++;	//线程间共享全局变量、局部变量、函数
	value++;
	printf("%s value:%d, temp:%d\n", (char*)arg, value, temp);
	
	printids(arg);
	return NULL;
}


int main(void)
{
	pthread_t tid;
	int err;
	
	/*
	 * 返回线程id
	 * 线程属性设置
	 * 线程处理函数
	 * 线程处理函数参数
	 */
	err = pthread_create(&tid, NULL, thread_handler, "new_thread1");
	//pthread_create失败返回错误码
	if (err != 0) {
		//由于pthread_create的错误码不保存在errno中，因此不能直接用perror()打印错误信息
		fprintf(stderr, "pthread_create1\n");
		exit(1);
	}
	printf("create tid %u\n", (unsigned int)tid);
	
	err = pthread_create(&tid, NULL, thread_handler, "new_thread2");
	//pthread_create失败返回错误码
	if (err != 0) {
		//由于pthread_create的错误码不保存在errno中，因此不能直接用perror()打印错误信息
		fprintf(stderr, "pthread_create2\n");
		exit(1);
	}
	printf("create tid %u\n", (unsigned int)tid);
	
	
	printids("main_thread");
	sleep(2);//预留线程调度的时间
	
	return 0;
	
}
