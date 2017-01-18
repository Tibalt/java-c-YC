#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <syslog.h>
#include "DataPoolDefine.h"


#define PORT_FTP        12345              /* FTP connection port */
#define SERVER_ADDR     "127.0.0.1"     /* localhost */
#define MAXBUF          1024
int p_num = 1;

struct packet{
    float ai;
    char di;
    char align[3];
} ;

float HTONF(float f){
    char *p = &f;

    //printf("%d,%d,%d,%d\n",p[0],p[1],p[2],p[3]);
    char tmp=0;
    tmp= p[0];
    p[0]=p[3];
    p[3]= tmp;

    tmp= p[2];
    p[2]=p[1];
    p[1]= tmp;
    //printf("%d,%d,%d,%d\n",p[0],p[1],p[2],p[3]);
    return f;
}
float NTOHF(float f){
    return HTONF(f);
}



int convertToHostByteOrder(_YC *pYc){
    if(pYc == NULL)
        return -1;

    pYc->Yc_Num = ntohl(pYc->Yc_Num); 
    int i=0;
    for(i=0;i<pYc->Yc_Num;i++){
        pYc->Yc_Data[i].Yc_Value = NTOHF(pYc->Yc_Data[i].Yc_Value);
        //no need to convert for char
	    //pYc->Yc_Data[i].OV ;
        //pYc->Yc_Data[i].BL ;
        //pYc->Yc_Data[i].SB ;
        //pYc->Yc_Data[i].NT ;
        //pYc->Yc_Data[i].IV ;
    }
    return 0;
}
void initializeYCWithNetworkOrder(){
    //we assume 1 device with 1 points
    memset(YC,0xff,sizeof(_YC) * MAXDEVNUM);
    YC[0].Yc_Num = htonl(p_num);
    YC[0].Yc_Data[0].Yc_Value = HTONF(123.45);
    YC[0].Yc_Data[0].OV = 1;
    YC[0].Yc_Data[0].BL = 45;
    YC[0].Yc_Data[0].SB = 129;
    YC[0].Yc_Data[0].NT = 234;
    YC[0].Yc_Data[0].IV = 255;
}
int main()
{   
    openlog("c_app", LOG_PID,LOG_LOCAL0);
    initializeYCWithNetworkOrder();
    syslog(LOG_DEBUG,"size of YC_DATA is %d,size of YC is %d\n",
                sizeof(YCDATA),sizeof(_YC));
    int sockfd;
    struct sockaddr_in dest;
    int i=0;

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
    syslog(LOG_DEBUG,"begin to connect!");

    /*---Connect to server---*/
    if ( connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) != 0 )
    {
        perror("Connect ");
        exit(errno);
    }
    syslog(LOG_DEBUG,"begin to send packet!");


/*
    struct packet p;
    p.ai = 123.45;
    p.di = 1; 
    char *x = &(p.ai);
    p.ai = htonf(p.ai);
*/
    //printf("point num is %d\n",YC[0].Yc_Num);
    //printf("point value is %f\n",YC[0].Yc_Data[0].Yc_Value);
    int rtn = write(sockfd,YC, sizeof(_YC));
    if(rtn <0){
        syslog(LOG_ERR,"wrong in sending:%s",strerror(errno));
        exit(-1);
    }


    if(rtn != sizeof(_YC))
        syslog(LOG_ERR,"%d is sent while %d should be sent", rtn, sizeof(_YC));
    syslog(LOG_DEBUG,"sent a packet!");
    
    _YC rtn_YC; 
    int recv_num = 0;
   
    
    fd_set rfds;
    struct timeval tv;
    FD_ZERO(&rfds);
    FD_SET(sockfd, &rfds);
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    

    do{
        rtn = select(sockfd+1,&rfds,NULL,NULL,&tv);
        if(rtn == -1){
            syslog(LOG_ERR,"select error:%s",strerror(errno));
            close(sockfd);
            exit(-1); 
        }
        else if(rtn){
            rtn = read(sockfd,(char *)(&(rtn_YC)) + recv_num ,DEVPACKETSIZE);
            if(rtn > 0)
                recv_num += rtn;
            else{
                syslog(LOG_ERR,"read return <=0: ",strerror(errno));
                close(sockfd);
                exit(-1);
            }
        }
        else
            break;
    }while(1);

 
   syslog(LOG_INFO,"Received %d bytes from java",recv_num);

    if(recv_num  != p_num * 12 + 4){
        syslog(LOG_WARNING,"invalid echo data, we got %d bytes while packet of size %d is expected",recv_num, p_num* 12 + 4);
        exit(0);
    }

    convertToHostByteOrder(&rtn_YC);
    syslog(LOG_INFO,"total point num: %d", rtn_YC.Yc_Num);
    for(i=0;i< rtn_YC.Yc_Num;i++){
        syslog(LOG_INFO,"point [%d]: ",i);
        syslog(LOG_INFO,"value:%f", rtn_YC.Yc_Data[i].Yc_Value);
        syslog(LOG_INFO,"       OV:%u", rtn_YC.Yc_Data[i].OV);
        syslog(LOG_INFO,"       BL:%u", rtn_YC.Yc_Data[i].BL);
        syslog(LOG_INFO,"       SB:%u", rtn_YC.Yc_Data[i].SB);
        syslog(LOG_INFO,"       NT:%u", rtn_YC.Yc_Data[i].NT);
        syslog(LOG_INFO,"       IV:%u", rtn_YC.Yc_Data[i].IV);
    }
    close(sockfd);


    /*---Get "Hello?"---*/
    //    bzero(buffer, MAXBUF);
    //   recv(sockfd, buffer, sizeof(buffer), 0);
    //  printf("%s", buffer);

    /*---Clean up---*/
    // close(sockfd);
    return 0;
}


