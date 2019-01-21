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

#define MAXLINE 80
#define SERV_PORT 8000


int main(void)
{
	struct sockaddr_in servaddr, cliaddr;	//socket 地址结构体 服务端和客户端地址
	socklen_t cliaddr_len;
	int sockfd;//文件描述符
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i,n;
	int status;
	
	//创建块式套接字，即UDP socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		fprintf(stderr, "create socket\n");
		exit(1);
	}
	
	//初始化socket地址
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;//地址类型
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//可监听任意ip地址
	servaddr.sin_port = htons(SERV_PORT);//可监听的网络端口
	//绑定地址与端口到套接字
	status = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr) );
	if (status == -1) {
		fprintf(stderr, "bind\n");
		exit(1);
	}
	
	printf("Accepting connections ...\n");
	
	while (1) {
		cliaddr_len = sizeof(cliaddr);
		//阻塞等待客户端数据到来
		n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *)&cliaddr, &cliaddr_len);
		if (n == -1) {
			fprintf(stderr, "recvfrom error\n");
			exit(1);
		}
		printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
			
		for (i = 0; i < n; i++) {
			buf[i] = toupper(buf[i]);
		}
		
		n = sendto(sockfd, buf, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		if (n == -1) {
			fprintf(stderr, "sendto error\n");
			exit(1);
		}
	}
	
}