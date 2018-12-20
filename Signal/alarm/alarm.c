#include <stdio.h>
#include <stdlib.h>
//信号需要的头文件
#include <unistd.h>


int main(void)
{
	int i = 0;
	
	//5秒后产生SIGALARM信号
	alarm(5);
	
	for (i = 0; i < 10; i++) {
		printf("i = %d\n",i);
		sleep(1);
	}
	
	return 0;
}