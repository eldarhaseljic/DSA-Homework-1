// kompajlirajte sa: $gcc fileserver.c -o fileserver  i startajte sa $./fileserver
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>  // socket
#include<arpa/inet.h> //inet_addr
#include<unistd.h>

int main(void)
{
    int listenfd = 0;
    int c;
    int bytesReceived = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr,client;
    char recvBuff[512]; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
    	  printf("Could not create socket");
    }

    printf("Socket created\n");

    //Prepare the sockaddr_in structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( 8888 );


    //Bind
    if( bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
    	{
    	    //print the error message
    	    perror("bind failed. Error");
    	    return 1;
    	}
    	puts("bind done");



    if(listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }



    /* Create file where data will be stored */
    
    /*
    FILE *fp;
    fp = fopen("server.dat", "wb"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }  
    */

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    while(1) {
    connfd = accept(listenfd,(struct sockaddr *)&client, (socklen_t*)&c);

    if (connfd < 0)
    	{
    	    perror("accept failed");
    	    return 1;
    	}
     puts("Connection accepted");
///////////////////////////////////////
  
  int i = 0;
  if(recv(connfd, recvBuff,sizeof(recvBuff),0) >0)
    {
      while(recvBuff[i]!='\n')
      {
        //printf("%c",recvBuff[i]);
        //printf("%d",bytesReceived);
        ++i;
      }
    }
  
  char title [i];
  i=0;
  while(recvBuff[i]!='\n')
  {
    title[i]=recvBuff[i];
    ++i;
  }

//////////////////////////////////////
     FILE *fp;
     fp = fopen(title, "wb"); 
     if(NULL == fp)
     {
         printf("Error opening file");
         return 1;
     }  
    printf("Successfully created a file.\n");
    printf("The file is \" %s \" \n ", title);
    /* Receive data in chunks of 512 bytes */

  while((bytesReceived=recv(connfd, recvBuff,sizeof(recvBuff),0)) >0)
    {
      fwrite(recvBuff,1,bytesReceived,fp);
    }
  printf("File update was made.\n");
	if(bytesReceived == 0)
    	{
    	puts("Client disconnected"); 
    	}
    	else if(bytesReceived == -1)
    	{
    	    perror("recv failed");
    	}    
        close(connfd);
        fclose(fp);
  }
	
    return 0;
}
