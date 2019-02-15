#include <test.h>
#include <add.h>
#include <sub.h>

int main(void)
{
	int a = 3;
    int b = 2;
       
    printf("a=%d\n", a);
    printf("b=%d\n", b);
 
    printf("a+b=%d\n", add(a,b));
    printf("a-b=%d\n", sub(a,b));
	
	c = 12;
	printf("hello makefile %d\n", c);
    return 0;
}