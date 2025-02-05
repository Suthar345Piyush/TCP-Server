//Own  TCP server

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>    
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>


int main(){
  // creating a  socket 

  int server_fd = socket(AF_INET , SOCK_STREAM , 0);

  // bind a  ip address and  port to socket 
  
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(8080);
  bind(server_fd , (struct sockaddr *)&address , sizeof(address));

  // listening  to incoming  connections

  listen(server_fd , 5);

  printf("Server is running on port 8080...\n");

  //loop to keep accepting  connections 

  while(1){

    // three way handshake(connection establishment / accepting  connection)

    int addrlen = sizeof(address);
    int new_socket = accept(server_fd , (struct sockaddr *)&address , (socklen_t*)&addrlen);

    if(new_socket < 0){
      perror("error , failed to accept connections");
      continue;
    }

    printf("conncetion accepted\n");

    // handling  the  data  transfer 

    char buffer[1024] = {0};

    //reading data from client

    read(new_socket , buffer , 1024);
    printf("client: %s\n" , buffer);

    //sending  response to client 

    char *hello = "Hello from server";
    write(new_socket , hello , strlen(hello));

    //four way handshake(connection termination)

    close(new_socket);
    printf("connection closed\n");
  }
  
   //closing the  listening socket
   close(server_fd);

   return 0;
}

