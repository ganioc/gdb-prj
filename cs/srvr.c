// a server to remotely run the w command

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define WPORT 2000
#define BUFSIZE 1000

int clntdesc; // socket descriptor for individual client
int svrdesc; // socket descriptor for server

char outbuf[BUFSIZ]; // messages to client


void respond(){
  int fd, nb;

  memset(outbuf, 0, sizeof(outbuf));

  system("w > tmp.client");

  fd = open("tmp.client", O_RDONLY);

  nb = read(fd, outbuf, BUFSIZE);

  write(clntdesc, outbuf, nb);

  unlink("tmp.client");

  close(clntdesc);
}

int main(){
  struct sockaddr_in bindinfo;

  // create socket to be used to accept connections
  srvdesc = socket(AF_INET, SOCK_STREAM, 0);
  bindinfo.sin_family = AF_INET;
  bindinfo.sin_port = WPORT;
  bindinfo.sin_addr.s_addr = INADDR_ANY;
  bind(svrdesc, (struct sockaddr *)&bindinfo, sizeof(bindinfo));

  // OK

  listen(svrdesc, 5);

  while(1){
    // wait for a call
    clntdesc = accept(svrdesc, 0 , 0);
    // process the command
    respond();
  }
}

  
