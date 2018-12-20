#include <stdio.h>
#include <stdlib.h>
//signal需要使用的头文件
#include <unistd.h>
#include <signal.h>
//进程需要使用的头文件
#include <sys/types.h>
//#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//子进程终止时都会给父进程发送SIGCHLD信号
//重定义SIGCHLD信号处理函数，自动调用wait清理子进程，父进程不必阻塞

void signal_handler(int sig)
{
	printf("child exit\n");
	wait(NULL); //回收资源
}


int main(void)
{
	pid_t pid;
	
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
		
	if (pid == 0) {
		//child
		sleep(1);
		printf("I am child\n");
		exit(2);
	} else {
		//parent
		struct sigaction act_new;
		
		act_new.sa_handler = signal_handler;
		act_new.sa_flags = 0;
		sigemptyset(&act_new.sa_mask);
		sigaction(SIGCHLD, &act_new, NULL);
		
		while (1) {
			printf("I am parent\n");
			sleep(1);
		}
		
	}
	
	return 0;
	
}
