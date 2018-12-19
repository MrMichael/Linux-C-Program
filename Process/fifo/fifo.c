
#include <stdio.h>
#include <stdlib.h>

//进程需要使用的头文件
#include <sys/types.h>
#include <unistd.h>
//wait函数需要的头文件
#include <sys/types.h>
#include <sys/wait.h>
//命名管道需要用的头文件
#include <sys/stat.h>
//文件操作需要的头文件
#include <fcntl.h>

char fifoname[] = {"./pipefifo"};

int main(void)
{
	int fd;
	pid_t pid;
	char buf[20];
	int n;
	
	if (access(fifoname, F_OK) < 0) {
		//FIFO和socket都是特殊文件
		//FIFO也只支持单向传输，双向传输需要使用两个管道
		if (mkfifo(fifoname, 0777) < 0 ) {
			perror("mkfifo");
			exit(1);
		}
		
		
		//创建普通文件也可以达到进程间通信的效果，就是对文件进行读写
		//使用普通文件传输会有数据残留
		/*fd = creat(fifoname, 0777);
		if (fd < 0) {
			perror("creat");
			exit(1);
		}
		close(fd);*/
	}
	
	if((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	
	if (pid == 0) {
		//child
		fd = open(fifoname, O_RDWR);
		if (fd < 0) {
			perror("fork");
			exit(1);
		}
		
		n = read(fd, buf, 20);
		write(STDOUT_FILENO, "child get:", 10);
		write(STDOUT_FILENO, buf, n);
		
		
	} else {
		//parent
		
		fd = open(fifoname, O_RDWR);
		if (fd < 0) {
			perror("fork");
			wait(NULL);
			exit(1);
		}
		write(STDOUT_FILENO, "parent:hello child\r\n", 20);
		write(fd, "hello child\r\n", 13);
		
		wait(NULL);
	}
	
	return 0;
}