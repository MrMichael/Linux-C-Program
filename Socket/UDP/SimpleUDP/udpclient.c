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

#define MAXLINE 80
#define SERV_PORT 8000


int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	int sockfd, n;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	socklen_t servaddr_len;
	
	//创建UDP socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
	
	while (1) {
		if (fgets(buf, MAXLINE, stdin) != NULL) {
			//通过文件描述符发送数据
			n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
			if (n == -1) {
				fprintf(stderr, "sendto error\n");
				exit(1);
			}
			
			//通过文件描述符接收数据
			n = recvfrom(sockfd, buf, MAXLINE, 0, NULL, 0);
			if (n == -1) {
				fprintf(stderr, "recvfrom error\n");
				exit(1);
			}
			
			write(STDOUT_FILENO, buf, n);

		}
	}
	close(sockfd);
	
	return 0;
	
}





