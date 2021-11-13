#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>
#include<string.h>
int main()
{
int cont,create_socket,new_socket,addrlen,fd;

int bufsize = 1024;
char *buffer = malloc(bufsize);
char reciev[256];
struct sockaddr_in address;
if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
printf("The socket was created\n");
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(15000);
if (bind(create_socket,(struct sockaddr
*)&address,sizeof(address)) == 0)
printf("Binding Socket\n");
listen(create_socket,3);
addrlen = sizeof(struct sockaddr_in);
new_socket = accept(create_socket,(struct sockaddr
*)&address,&addrlen);
if (new_socket > 0)
printf("The Client %s is Connected...\n ",
inet_ntoa(address.sin_addr));
int bytes;
while((bytes = recv(new_socket,reciev, 255,0))>0)
{
reciev[bytes] ='\0';
if(strcmp(reciev,"end")==0)
{
close(new_socket);
close(create_socket);
exit(0);
}
else
{
printf("Request recieved for command: %s\n",
reciev);
system(reciev);
}
}

close(new_socket);
return close(create_socket);
}
