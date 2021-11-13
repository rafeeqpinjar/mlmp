/*Server*/

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>

int main()
{
int cont,create_socket,new_socket,addrlen,fd;
int bufsize = 1024;
char *buffer = malloc(bufsize);
char fname[256];
struct sockaddr_in address;

// Create a socket using socket() system call.

if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
printf("The socket was created\n");
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(15003);

//  Bind the socket to an address using bind() system call.

if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) == 0)
printf("Binding Socket\n");

// Listen to the connection using listen() system call.

listen(create_socket,3);
addrlen = sizeof(struct sockaddr_in);

// accept connection using accept().

new_socket = accept(create_socket,(struct sockaddr *)&address,&addrlen);
if (new_socket> 0)
 {
printf("The Client %s is Connected...\n",
inet_ntoa(address.sin_addr) );
 }

// Receive filename and transfer contents of file with client.

recv(new_socket,fname, 255,0);
printf("A request for filename %s Received..\n", fname);

if ((fd=open(fname, O_RDONLY))<0)
 {perror("File Open Failed"); exit(0);}
while((cont=read(fd, buffer, bufsize))>0) {
send(new_socket,buffer,cont,0);
 }
printf("Request Completed\n");
close(new_socket);
return close(create_socket);
}
