#include <stdio.h>
#include <stdlib.h>
//进程需要使用的头文件
#include <sys/types.h>
#include <unistd.h>
//waitpid函数需要的头文件
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 80

int main(void)
{
	int n;
	int fd[2], fd2[2];
	pid_t pid;
	char line[MAXLINE];
	
	if (pipe(fd) < 0) {
		perror("pipe fd");
		exit(1);
	}
	
	if (pipe(fd2) < 0) {
		perror("pipe fd2");
		exit(1);
	}
	
	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	
	if (pid == 0) {
		//child
		close(fd[1]); //关闭写端
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, "child pipe read:", 16);
		write(STDOUT_FILENO, line, n);
		
		close(fd2[0]); //关闭读端
		write(STDOUT_FILENO, "child pipe write\n", 17);
		write(fd2[1], "hello parent\r\n", 14);
		
	} else {
		//parent
		close(fd[0]); //关闭读端
		write(STDOUT_FILENO, "parent pipe write\n", 18);
		write(fd[1], "hello child\r\n", 13);
		
		close(fd2[1]); //关闭写端
		n = read(fd2[0], line, MAXLINE);
		write(STDOUT_FILENO, "parent pipe read:", 17);
		write(STDOUT_FILENO, line, n);
		
		wait(NULL);
	}
	
	
	return 0;
}