/* server */
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

int main(void)
{
	struct sockaddr_in servaddr, cliaddr;	//socket 地址结构体 服务端和客户端地址
	socklen_t cliaddr_len;
	int listenfd, connfd;//文件描述符
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i,n;
	int status;
	
	//创建流式套接字，即TCP socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd == -1) {
		fprintf(stderr, "create socket\n");
		exit(1);
	}
	
	//初始化socket地址
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;//地址类型
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//可监听任意ip地址
	servaddr.sin_port = htons(SERV_PORT);//可监听的网络端口
	//绑定地址与端口到套接字
	status = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr) );
	if (status == -1) {
		fprintf(stderr, "bind\n");
		exit(1);
	}
	
	//设置socket为监听模式，最多允许有20个客户端处于连接待状态
	listen(listenfd, 20);
	if (status == -1) {
		fprintf(stderr, "listen\n");
		exit(1);
	}
	
	printf("Accepting connections ...\n");
	
	while (1) {
		cliaddr_len = sizeof(cliaddr);
		//服务端阻塞等待客户端连接
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		//通过文件描述符读取数据  阻塞等待
		n = read(connfd, buf, MAXLINE);
		//客户端的端口是随机分配的
		printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
		
		for (i = 0; i < n; i++) {
			buf[i] = toupper(buf[i]);
		}
		//通过文件描述符写入数据
		write(connfd, buf, n);
		close(connfd);
	}
	
	close(listenfd);
	
}








