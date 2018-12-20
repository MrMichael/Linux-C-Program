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


void sigusr1_handler(int sig)
{
	printf("parent get a signal %d\n", sig);
}

void sigusr2_handler(int sig)
{
	printf("child get a signal %d\n", sig);
	
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
		struct sigaction act_new;
		
		act_new.sa_handler = sigusr2_handler;
		act_new.sa_flags = 0;
		sigemptyset(&act_new.sa_mask);
		sigaction(SIGUSR2, &act_new, NULL);
		
		while (1) {
			pause();
			
			kill(getppid(), SIGUSR1); //信号产生函数不能放在信号处理函数中
		}
		
	} else {
		//parent
		struct sigaction act_new;
		
		act_new.sa_handler = sigusr1_handler;
		act_new.sa_flags = 0;
		sigemptyset(&act_new.sa_mask);
		sigaction(SIGUSR1, &act_new, NULL);
		
		while (1) {
			sleep(2);
			kill(pid, SIGUSR2);
		}
	}
	
}