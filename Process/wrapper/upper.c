#include <stdio.h>
#include <stdlib.h>
//toupper函数所需头文件
#include <ctype.h>

int main(void)
{
	int ch;
	
	//EOF == CTRL+D
	while ((ch = getchar()) != EOF) {
		putchar(toupper(ch));
	}
	
	return 0;
}