#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "helpers.h"

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_address server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, n, ret;
	struct sockaddr_in serv_addr;
	char buffer[BUFLEN];
  
  fd_set read_fds;	// multimea de citire folosita in select()
	fd_set tmp_fds;		// multime folosita temporar
	int fdmax;			// valoare maxima fd din multimea read_fds
  
	if (argc < 3) {
		usage(argv[0]);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	ret = inet_aton(argv[1], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");
  
  int rc;
  FD_SET(sockfd, &read_fds);
  FD_SET(0, &read_fds);
  fdmax = sockfd;
	while (1) {
	  tmp_fds = read_fds;
    
	  rc = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
	  DIE(rc < 0, "select");
	  
	  if (FD_ISSET(0, &tmp_fds)) {
  	  	// se citeste de la tastatura
		  memset(buffer, 0, BUFLEN);
		  fgets(buffer, BUFLEN - 1, stdin);

		  if (strncmp(buffer, "exit", 4) == 0) {
			  break;
		  }
		  
		  // se trimite mesaj la server
		  n = send(sockfd, buffer, strlen(buffer), 0);
		  DIE(n < 0, "send");
		} 
		if (FD_ISSET(sockfd, &tmp_fds)) {
		  memset(buffer, 0, BUFLEN);
		  n = recv(sockfd, buffer, sizeof(buffer), 0);
		  fprintf(stderr, "Received: %s\n", buffer);
		}
		
	}

	close(sockfd);

	return 0;
}
