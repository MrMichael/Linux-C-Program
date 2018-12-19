#include <stdio.h>
//内存映射需要的头文件
#include <sys/mman.h>
//文件操作需要的头文件
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>


int main(void)
{
	int *p;
	int fd;

	fd	= open("text.txt", O_RDWR);
	if (fd == -1) {
		perror("open text.txt");
		exit(1);
	}
	
	//映射之前文件内容不能为空，否则映射出错
	//mmap没法增加文件长度，通过内存对文件操作的数据长度不会超过文件本身包含的数据长度的
	//length==2，代表将文件中2word的数据映射到内存，但如果length小于一个内存页的长度，
	//实际设置共享内存的大小是一页。
	p = mmap(NULL, 2, PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	
	if (close(fd) == -1)
	{
		perror("close text.txt");
		exit(1);
	}
	
	p[0] = 0x31303030;	//低位在前，高位在后 X86架构下
	p[1] = 0x32303030;
	p[2] = 0x33303030;
	p[3] = 0x34303030;
	p[4] = 0x35303030;
	p[5] = 0x36303030;

	if (munmap(p, 16) == -1) {
		perror("munmap");
		exit(1);
	}
	
	
	return 0;
}