#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "DataPoolDefine.h"


#define PORT_FTP        12345              /* FTP connection port */
#define SERVER_ADDR     "127.0.0.1"     /* localhost */
#define MAXBUF          1024

struct packet{
    float ai;
    char di;
    char align[3];
} ;



float HTONF(float f){
    char *p = &f;

    printf("%d,%d,%d,%d\n",p[0],p[1],p[2],p[3]);
    char tmp=0;
    tmp= p[0];
    p[0]=p[3];
    p[3]= tmp;

    tmp= p[2];
    p[2]=p[1];
    p[1]= tmp;
    printf("%d,%d,%d,%d\n",p[0],p[1],p[2],p[3]);
    return f;
}
void initializeYCWithNetworkOrder(){
    //we assume 1 device with 1 points
    memset(YC,0xff,sizeof(_YC) * MAXDEVNUM);
    YC[0].Yc_Num = htonl(1);
    YC[0].Yc_Data[0].Yc_Value = HTONF(123.45);
    YC[0].Yc_Data[0].OV = 1;
    YC[0].Yc_Data[0].BL = 45;
    YC[0].Yc_Data[0].SB = 129;
    YC[0].Yc_Data[0].NT = 234;
    YC[0].Yc_Data[0].IV = 255;
}
int main()
{   
    initializeYCWithNetworkOrder();
    printf("size of YC_DATA is %d\n,size of YC is %d\n",
                sizeof(YCDATA),sizeof(_YC));
    int sockfd;
    struct sockaddr_in dest;

    /*---Open socket for streaming---*/
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("Socket");
        exit(errno);
    }

    /*---Initialize server address/port struct---*/
    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT_FTP);
    if ( inet_aton(SERVER_ADDR, &dest.sin_addr.s_addr) == 0 )
    {
        perror(SERVER_ADDR);
        exit(errno);
    }
    printf("begin to connect!\n");

    /*---Connect to server---*/
    if ( connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) != 0 )
    {
        perror("Connect ");
        exit(errno);
    }
    printf("begin to send packet!\n");


/*
    struct packet p;
    p.ai = 123.45;
    p.di = 1; 
    char *x = &(p.ai);
    p.ai = htonf(p.ai);
*/
    printf("point num is %d\n",YC[0].Yc_Num);
    printf("point value is %f\n",YC[0].Yc_Data[0].Yc_Value);
    int rtn = write(sockfd,YC, sizeof(_YC));
    if(rtn <0)
        perror("wrong in sending");


    if(rtn != sizeof(_YC))
        printf("%d is sent while %d should be sent\n", rtn, sizeof(_YC));
    printf("sent a packet!\n");

    close(sockfd);

    /*---Get "Hello?"---*/
    //    bzero(buffer, MAXBUF);
    //   recv(sockfd, buffer, sizeof(buffer), 0);
    //  printf("%s", buffer);

    /*---Clean up---*/
    // close(sockfd);
    return 0;
}


