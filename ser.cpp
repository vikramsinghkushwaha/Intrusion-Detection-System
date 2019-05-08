#include<iostream>
// ./server <port>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <fcntl.h>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sys/stat.h>

#include <sys/sendfile.h>

using namespace std;

int main(int argc, char *argv[])
{
    vector<string> valid_ip;
    ifstream infile("valid_ip.txt");
    string temp_ip;
    while(infile >> temp_ip){
        valid_ip.push_back(temp_ip);
    }
    // for (auto i = valid_ip.begin(); i != valid_ip.end(); ++i)
    // {
    //     cout<< *i<<endl;
    // }
    
    int listenfd = 0, connfd = 0,k;
    struct sockaddr_in serv_addr , client; 

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);        
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);             
    serv_addr.sin_port = htons(atoi(argv[1]));                     

    k = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));        


    k = listen(listenfd, 10); 

    
    

    // connfd = accept(listenfd, (struct sockaddr*)NULL,NULL);      

    socklen_t client_size = sizeof(sockaddr_in);
    connfd = accept(listenfd, (struct sockaddr*)&client, &client_size);      

    string client_ip = inet_ntoa(client.sin_addr);

    if (find(valid_ip.begin(), valid_ip.end(),client_ip) != valid_ip.end())
    {
        printf("connected to the client\n");
        printf("IP address is: %s\n", client_ip.c_str());
        // printf("port is: %d\n", (int) ntohs(client.sin_port));
        char buf[100],command[5],filename[20],ext[20],lscommand[20];      
        int size,i,filehandle;
        struct stat obj;
        int already_exits = 0;
        int overwrite_choice = 1;
        char *pos;
        recv(connfd,buf,100,0);
        char buf1[100];
        printf("%s\n",buf );
        strcpy(buf1, "Hello from server\0");
        send(connfd,buf1,100,0);
    }
    else{
        printf("%s\n","Invalid ip address trying to connet" );
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
