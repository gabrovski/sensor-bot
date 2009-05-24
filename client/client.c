#include "client.h"

void *connectMover(void *ptr){
 struct sockaddr_in servaddr;
 //char sendline[MAXLINE], recvline[MAXLINE];
	
 //Create a socket for the client
 //If sockfd<0 there was an error in the creation of the socket
 if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("Problem in creating the socket");
  exit(2);
 }
	
 //Creation of the socket
 memset(&servaddr, 0, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
	
 //Connection of the client to the socket 
 if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
  perror("Problem in connecting to the server");
  exit(3);
 }


}

int main(int count, char **args) {
  argc = count;
  argv = args;

 //basic check of the arguments
 //additional checks can be inserted
 if (argc !=2) {
  perror("Usage: TCPClient <IP address of the server"); 
  exit(1);
 }
	
 /*
 // char text[MAXLINE];
 memset(sendline, '\0', MAXLINE);
 while (scanf("%s", sendline) == 1) {	
  send(sockfd, sendline, strlen(sendline), 0);
		
  if (recv(sockfd, recvline, MAXLINE,0) == 0){
   //error: server terminated prematurely
   perror("The server terminated prematurely"); 
   exit(4);
  }
  printf("\n");
  
  
  memset(sendline, '\0', MAXLINE);
 
 }
 */ 

  pthread_t t1;
  int iret1 = pthread_create(&t1, NULL, connectMover, NULL);
  //ptr = connectMover(argc, argv, ptr);

  runGUI(argc, argv); 

  

 

 return 0;
}
