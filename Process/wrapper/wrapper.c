#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int fd;
	
	if (argc != 2) {
		fputs("usage: wrapper file\r\n", stderr);
		exit(1);
	}
	
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open failed");
		exit(1);
	}
	
	//将文件描述符重定向为标准输入设备
	dup2(fd, STDIN_FILENO);
	if (close(fd) < 0) {
		perror("close failed");
		exit(1);
	}
	
	execl("./upper", "upper", NULL);
	perror("execl failed");
	exit(1);
	
	return 0;
	
}
