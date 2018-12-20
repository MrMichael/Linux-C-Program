#include <stdio.h>
#include <stdlib.h>
//signal需要的头文件
#include <unistd.h>
#include <signal.h>

//改变SIGALRM信号的处理函数
//alarm 触发SIGALRM信号，执行sigalrm_handler函数
//sigsuspend保证进程一定可以监听到SIGALRM信号


void signal_handler(int sig)
{
	printf("get a signal %d\n", sig);
}


int main(void)
{
	struct sigaction act_new, act_old;
	sigset_t mask_new, mask_old;
	
	//重新定义信号处理函数
	act_new.sa_handler = signal_handler;
	act_new.sa_flags = 0;
	sigemptyset(&act_new.sa_mask);
	sigaction(SIGALRM, &act_new, &act_old);
	
	//进程先屏蔽SIGALRM信号
	sigemptyset(&mask_new);
	sigaddset(&mask_new, SIGALRM);
	sigprocmask(SIG_BLOCK, &mask_new, &mask_old);
	
	while (1) {
		alarm(2);
		
		//临时设置新的信号屏蔽(打开SIGALRM信号)，并挂起进程
		//直到有信号抵达恢复原来的信号屏蔽并往下执行
		sigsuspend(&mask_old);//将挂起pluse()函数和sigprocmask函数合并
		printf("have a signal\n");
	}
	
	return 0;
}