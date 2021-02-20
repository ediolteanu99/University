#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DIE(assertion, call_description)	\
	do {									\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",	\
					__FILE__, __LINE__);	\
			perror(call_description);		\
			exit(EXIT_FAILURE);				\
		}									\
	} while(0)

#define BUFLEN		256	
#define MAX_CLIENTS	5	

struct shr {
  char nume[BUFLEN];
  int port;
  char IP[20];
  int isShared;
};


int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	char buffer[BUFLEN];
	struct sockaddr_in serv_addr, cli_addr;
	int n, i, ret;
	socklen_t clilen;

	fd_set read_fds;	// multimea de citire folosita in select()
	fd_set tmp_fds;		// multime folosita temporar
	int fdmax;			// valoare maxima fd din multimea read_fds

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	portno = atoi(argv[1]);
	DIE(portno == 0, "atoi");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind");

	ret = listen(sockfd, MAX_CLIENTS);
	DIE(ret < 0, "listen");
  struct shr *shared = (struct shr *) malloc(10 * sizeof(struct shr));
  int nr_shared = 0;
	// se adauga noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
	FD_SET(sockfd, &read_fds);
	fdmax = sockfd;

	while (1) {
		tmp_fds = read_fds;
		
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		for (i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
				if (i == sockfd) {
					// a venit o cerere de conexiune pe socketul inactiv (cel cu listen),
					// pe care serverul o accepta
					clilen = sizeof(cli_addr);
					newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
					DIE(newsockfd < 0, "accept");
          
					// se adauga noul socket intors de accept() la multimea descriptorilor de citire
					FD_SET(newsockfd, &read_fds);
					if (newsockfd > fdmax) { 
						fdmax = newsockfd;
					}

					printf("Noua conexiune de la %s, port %d, socket client %d\n",
							inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), newsockfd);
			    /*char msg[BUFLEN] = "Clienti conectati:\n";
			    send(newsockfd, msg, sizeof(msg), 0);
			    
				  for (int j = 0; j <= fdmax; j++) {
				    if ((FD_ISSET(j, &read_fds)) && (j != sockfd) && (j != newsockfd)) {
				      memset(msg, 0 , BUFLEN);
				      sprintf(msg, "%d\n", j);
				      send(newsockfd, msg, sizeof(msg), 0);
				      memset(msg, 0 , BUFLEN);
				      sprintf(msg, "Client nou conectat %d\n", newsockfd);
				      send(j, msg, sizeof(msg), 0);
				    }
				  }*/
				  
				  
				} else {
					// s-au primit date pe unul din socketii de client,
					// asa ca serverul trebuie sa le receptioneze
					memset(buffer, 0, BUFLEN);
					n = recv(i, buffer, sizeof(buffer), 0);
					DIE(n < 0, "recv");

					if (n == 0) {
						// conexiunea s-a inchis
						printf("Socket-ul client %d a inchis conexiunea\n", i);
						close(i);
						char msg[BUFLEN];
						for (int j = 0; j <= fdmax; j++) {
				      if ((FD_ISSET(j, &read_fds)) && (j != sockfd) && (j != i)) {
			          memset(msg, 0 , BUFLEN);
				        sprintf(msg, "Client deconectat %d\n", i);
				        send(j, msg, sizeof(msg), 0);
				      }
				    }
						// se scoate din multimea de citire socketul inchis 
						FD_CLR(i, &read_fds);
					} else {
						printf ("S-a primit de la clientul de pe socketul %d mesajul: %s\n", i, buffer);
						char *token;
						token = strtok(buffer, " ");
						char *command = (char *) calloc(BUFLEN, sizeof(char));
						strcpy(command, token);
					  token = strtok(NULL, " ");
					  char *filename = (char *) calloc(BUFLEN, sizeof(char));
					  strcpy(filename, token);
					  if (strcmp(command, "SHARE") == 0) {

					    shared[nr_shared].port = ntohs(cli_addr.sin_port);
					    strcpy(shared[nr_shared].IP,inet_ntoa(cli_addr.sin_addr));
					    strcpy(shared[nr_shared].nume, filename);
					    nr_shared++;
					    shared[nr_shared].isShared = 1;
					    printf("fisierul a fost adaugat\n");
					    printf("Fisiere:\n"); 
			        for (int i = 0; i < nr_shared; i++) {
			          printf("%s %d %s\n", shared[i].nume, shared[i].port, shared[i].IP);
			        }
					  } else if (strcmp(command, "UNSHARE") == 0) {
					    for (int i = 0; i < nr_shared; i++) {
					      if (strcmp(shared[i].nume, filename) == 0) {
					        printf("fisierul exista\n");
					        
					        for (int i = 0; i < nr_shared; i++) {
					          if (strcmp(shared[i].nume, filename) != 0) {
					            shared[i].isShared = 0;
					          }
					        }

					      }
					    }
					    
			        printf("Fisiere:\n"); 
			        for (int i = 0; i < nr_shared; i++) {
			          printf("%s %d %s\n", shared[i].nume, shared[i].port, shared[i].IP);
			        }
					  } else if (strcmp(command, "DOWNLOAD") == 0) {
					    printf("se doreste descarcarea\n");
					    for (int j = 0; j < nr_shared; j++) {
					      if (strcmp(shared[j].nume, filename) == 0) {
					        char buf[BUFLEN];
					        strcpy(buf, shared[j].IP);
					        char portc[10];
					        sprintf(portc, "%d", shared[j].port);
					        strcat(buf, " ");
					        strcat(buf, portc);
					        int rc = send(i, buf, sizeof(buf), 0);
					        
					      }
					    }
					    
					    
					  }
					}
				}
			}
		}
	}

	close(sockfd);

	return 0;
}
