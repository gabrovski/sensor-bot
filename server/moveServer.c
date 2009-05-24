#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "garcia.h"
//#include "vidcat/simplevideo.h"
#include "./vidcat/simplevideo.h"
#include <ctype.h>


#include "moveServer.h"

void move(char *);

int listenfd, connfd, n;

int main (int argc, char **argv)
{

 init(NULL);

 pid_t childpid;
 socklen_t clilen;
 char buf[MAXLINE];
 struct sockaddr_in cliaddr, servaddr;
	
 //creation of the socket
 listenfd = socket (AF_INET, SOCK_STREAM, 0);
	
 //preparation of the socket address 
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(SERV_PORT);
	
 bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
 listen (listenfd, LISTENQ);
	
 printf("%s\n","Server running...waiting for connections.");
	
 //for ( ; ; ) {
		
  clilen = sizeof(cliaddr);
  connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
  printf("%s\n","Received request...");
				
  while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {

  // Move around with non-blocking API
   move(buf);
   memset(buf, '\0', MAXLINE);

  }
			
 if (n < 0) {
  perror("Read error"); 
  exit(1);
 }
 close(connfd);
	
 // }
 //close listening socket
 close (listenfd); 
 
 // destroy();


 //start again if connection with client closes
 main(argc, argv);
}

void move(char *comm){
  float num;
  int i = 0;
  // printf("%s\n", comm);
  switch (comm[0]){
    
  case 'f': 
    comm++;
    sscanf(comm,"%f", &num);
    i = GarciaWalkN(num);
    // printf(" this is %f\n", num);
    //fflush(stdout);
    break;
  case 'b':
    comm++;
    sscanf(comm,"%f", &num);
    i = GarciaWalkN((num)*(-1));
    break;
  case 'l':
    comm++;
    sscanf(comm,"%f", &num);
    i = GarciaTurnN(num / 180.0 * 3.14159);
    break;
  case 'r':
    comm++;
    sscanf(comm,"%f", &num);
    i = GarciaTurnN((num / 180.0 * 3.14159)*(-1));
    break;
  case 's':
    GarciaStop();
    break;
  case 'd':
    close(connfd);
    close(listenfd);
    destroy();
    break;
  
  default: 
    
    printf("Unknown command\n");
    break;

    if (i)
      printf("Command failed miserably\n");

  }
}
