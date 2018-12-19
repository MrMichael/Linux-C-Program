#include <stdio.h>
#include <stdlib.h>
//进程需要使用的头文件
#include <sys/types.h>
#include <unistd.h>
//waitpid函数需要的头文件
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	char *message;
	int n = 1;
	int count = 0;
	
	pid = fork();
	if (pid < 0) {
		perror("fork failed");
		exit(1);
	}
	
	//fork成功以后，子进程和父进程都会执行下面的代码
	//后续变量都是独立的，操作互不影响
	
	if (pid == 0) {
		//fork函数对子进程返回0
		printf("child id:%d, parent id:%d\r\n",getpid(), getppid());
		message = "This is the child";
		n = 6;
	} else {
		//fork函数对父进程返回子进程id
		printf("parent id:%d, child id:%d\r\n",getpid(), pid);
		message = "This is the parent";
		n = 3;
	}
	
	for (; n > 0; n--) {
		count++;
		printf("%s,count:%d\r\n",message, count);
		sleep(1);
	}
	
	if (pid > 0) {
		int stat_val;
		waitpid(pid, &stat_val, 0);
		//如果子进程是正常终止的，WIFEXITED取出的字段值非零
		if (WIFEXITED(stat_val)) {
			//WEXITSTATUS取出的字段值就是子进程的退出状态
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		} else if (WIFSIGNALED(stat_val)) {
			//如果子进程是收到信号而异常终止的，WIFSIGNALED取出的字段值非零
			//WTERMSIG取出的字段值就是信号的编号
			printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
		}
	}
	
	return 0;
	
}