#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <pthread.h>


#define MAXDISTANCE 25
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/

int sockfd;
int argc;
char **argv;


void *connectMover(void *);
void runGUI(int, char **);
void forward(GtkWidget *, gpointer);
void back(GtkWidget *, gpointer);
void turnL(GtkWidget *, gpointer);
void turnR(GtkWidget *, gpointer);
void destroy(GtkWidget *, gpointer);


