#include <stdio.h>
#include <stdlib.h>
//signal需要的头文件
#include <unistd.h>
#include <signal.h>

//改变SIGALRM信号的处理函数
//alarm 触发SIGALRM信号，执行sigalrm_handler函数


void sigalrm_handler(int sig)
{
	printf("Get a signal %d\n", sig);
	
}

int main(void)
{
	struct sigaction actnew, actold;
	
	//重新定义信号处理函数
	actnew.sa_handler = sigalrm_handler;
	actnew.sa_flags = 0;
	sigemptyset(&actnew.sa_mask); //信号处理函数执行期间 不屏蔽信号
	sigaction(SIGALRM, &actnew, &actold); //actold保存原来的处理动作
	
	while (1) {
		alarm(2);
		//bug：如果在alarm与pause之间出现更高级的中断或进程任务，在SIGALRM信号出现后还没恢复，则会导致pluse函数一直挂起程序
		
		//使进程挂起直到有信号抵达
		//信号抵达后先执行信号处理函数，再往下执行
		pause();
		printf("have a signal\n");
	}
	
	return 0;
}
