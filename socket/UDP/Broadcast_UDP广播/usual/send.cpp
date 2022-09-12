#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include<iostream>
 
int main()
{
    //
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1)
    {
        perror("socket");
        exit(0);
    }

    //
    int op = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));

    //
    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(50503);
    inet_pton(AF_INET, "10.0.2.255", &cliaddr.sin_addr.s_addr);
 
    //while(1)
    //{

        char *a ="abc";
        printf("send:%s",a);
        //for(int i = 0;i < sizeof(a); i++){
        //    printf("%X",a[i]);
        //}
        printf("\n");
        sendto(fd, a, sizeof(a), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
        sleep(1);
    //}
 
    close(fd);
 
    return 0;
}