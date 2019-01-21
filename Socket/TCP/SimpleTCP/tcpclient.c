/* client */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//socket 所需的头文件
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>
#include <ctype.h>

#define MAXLINE	80
#define SERV_PORT	8000

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd; //文件描述符
	int n;
	char *str;
	
	if (argc != 2) {
		fputs("usage: ./client message\n", stderr);
		exit(1);
	}
	str = argv[1];
	
	//创建流式套接字，即TCP socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		fprintf(stderr, "create socket\n");
		exit(1);
	}
	
	//初始化socket地址
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
	
	//客户端请求连接服务器
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	//通过文件描述符写入数据 
	write(sockfd, str, strlen(str));
	
	//通过文件描述符读取数据  阻塞等待
	n = read(sockfd, buf, MAXLINE);
	printf("Response from server:\n");
	write(STDOUT_FILENO, buf, n);
	
	close(sockfd);
	
	return 0;
	
}