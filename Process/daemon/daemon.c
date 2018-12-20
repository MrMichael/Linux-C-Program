#include <stdio.h>
#include <stdlib.h>
//进程需要使用的头文件
#include <sys/types.h>
#include <unistd.h>

//file操作需要的头文件
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
	pid_t pid;
	
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	
	if (pid > 0) {
		//终结父进程
		exit(0);
	}
	
	//子进程调用setsid创建新的Session，成为守护进程
	setsid();
	
	//按照守护进程的惯例，通常将当前工作目录切换到根目录
	if (chdir("/") < 0) {
		perror("chdir");
		exit(1);
	}
	
	//将标准输入0、标准输出1、标准错误2指向/dev/null
	close(0);
	open("/dev/null", O_RDWR);
	dup2(0, 1);
	dup2(0, 2);
	
	while (1) {
		//执行守护进程的操作
		sleep(1);
		;
	}
	
	return 0;
}