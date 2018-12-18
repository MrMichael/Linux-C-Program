#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char filename[] = "./text.txt";

int main(void)
{
	int fd;
	char buf[10];
	int n;
	int i = 0;
	int len;
	
	//如果文件不存在就创建文件
	fd = open(filename, O_RDWR | O_CREAT, 0777);
	//fd = open(filename, O_RDONLY | O_WRONLY);
	if(fd == -1) {
		printf("open %s fail\r\n",filename);
		exit(1);
	} else {
		printf("open %s ok\r\n", filename);
	}
	
	n = write(fd, "1234567890", 10);
	if(n == -1) {
		printf("write %s fail\r\n",filename);
	} else {
		printf("write %s %d buff\r\n",filename, n);
	}
	
	//由于write操作会使读写位置处于内容末尾，需要指向到当前位置的前10偏移位置
	lseek(fd, -10, SEEK_CUR);
	
	n = read(fd, buf, 10);
	if(n == -1) {
		printf("read %s fail\r\n",filename);
	} else {
		printf("read %s %d buff\r\n",filename, n);
	}

	printf("read buf len:%d\r\n", n);
	//write(STDOUT_FILENO, buf, 10);
	for (i = 0; i < 10; i++)
	{
		printf("%c",buf[i]);
	}
	
	
	if(close(fd) == -1) {
		printf("close %s fail\r\n",filename);
		exit(1);
	} else {
		printf("close %s ok\r\n", filename);
	}

	return 0;
}
