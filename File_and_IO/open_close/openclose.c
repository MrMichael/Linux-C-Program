#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char filename[] = "text.txt";

int main(void)
{
	int fd;

	fd = open(filename, O_RDWR | O_CREAT, 0777);
	if (fd != -1) {
		printf("open %s ok\r\n",filename);
		if (close(fd) != -1) {
			printf("close %s ok\r\n",filename);
			
		} else {
			printf("close %s fail\r\n",filename);
		}
	} else {
		printf("open %s fail\r\n",filename);
	}

	return 0;
}

