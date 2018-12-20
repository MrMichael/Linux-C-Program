#include <stdio.h>
#include <stdlib.h>
//信号需要的头文件
#include <unistd.h>
#include <signal.h>

//设置进程对SIGINT信号挂起

int main(void)
{
	int i = 0;
	//定义信号集
	sigset_t s,p;
	
	//在信号集中只将SIGINT置位
	sigemptyset(&s);
	sigaddset(&s, SIGINT);
	//在进程信号屏蔽字中添加SIGINT，即该进程将会使收到的SIGINT信号pending
	sigprocmask(SIG_BLOCK, &s, NULL);
	
	while (1) {
		sigpending(&p);
		
		for (i = 0; i < 32; i++) {
			//如果进程中有被pending的信号
			if (sigismember(&p, i) == 1) {
				printf("signal:%d\n",i);
			}
		}
		
		sleep(1);
	}
	
	return 0;
}