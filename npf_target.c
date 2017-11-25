#include <stdio.h>    
#include <strings.h>    
#include <unistd.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
//#include <linux/in.h>    
#include <stdlib.h>    
#include <memory.h>    
#include <arpa/inet.h>    
#include <netinet/in.h>    

#include <signal.h> //添加信号处理  防止向已断开的连接通信

/**  
 *       信号处理顺序说明：在Linux操作系统中某些状况发生时，系统会向相关进程发送信号，  
 *             信号处理方式是：1，系统首先调用用户在进程中注册的函数，2，然后调用系统的默认  
 *                   响应方式,此处我们可以注册自己的信号处理函数，在连接断开时执行  
 *                         */    


#define PORT    11910    
#define Buflen  1024    

void process_conn_client(int s);    
//void sig_pipe(int signo);    //用户注册的信号函数,接收的是信号值    

int s;  //全局变量 ， 存储套接字描述符    

int main(int argc,char *argv[])    
{    

    struct sockaddr_in server_addr;    
    int err;    
       
    char server_ip[50] = "";    
    //int port = 0;  
    //strcpy(server_ip, argv[1]);  
    //port = atoi(argv[2]);  

    /********************socket()*********************/    
    s= socket(AF_INET,SOCK_STREAM,0);    
    if(s<0)    
    {    
        printf("client : create socket error\n");    
        return 1;    
    }    
    printf("client : socket fd = %d\n", s);   

    /*******************connect()*********************/
    //设置服务器地址结构，准备连接到服务器
    memset(&server_addr,0,sizeof(server_addr));    
    server_addr.sin_family = AF_INET;    
    server_addr.sin_port = htons(PORT);    
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /*将用户数入对额字符串类型的IP格式转化为整型数据*/    
    //inet_pton(AF_INET,argv[1],&server_addr.sin_addr.s_addr);
    printf("please input server ip address : \n");    
    read(0,server_ip,50);    
    //err = inet_pton(AF_INET,server_ip,&server_addr.sin_addr.s_addr);  
    server_addr.sin_addr.s_addr = inet_addr(server_ip);    

    err = connect(s,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));    
    if(err == 0)    
    {    
        printf("client : connect to server\n");    
    }    
    else    
    {    
        printf("client : connect error\n");    
        return -1;    
    }    

    //与服务器端进行通信
    process_conn_client(s);    
    close(s); 

}

void process_conn_client(int s)    
{    

    ssize_t size = 0;    
    char page_address[8];
    char page_content[4096];

    for(;;)    
    {    
        memset(page_address, '\0', 8);
        memset(page_content, '\0', 4096);
        /*从标准输入中读取数据放到缓冲区buffer中*/ 
        // 0，被默认的分配到标准输入  1，标准输出  2，error    
        size = read(0, page_address, 8);
       

        if(size >  0)    
        {    
            //当向服务器发送 “quit” 命令时，服务器首先断开连接
            write(s, page_address, 8);   //向服务器端写  
            //等待读取到数据
            memset(page_content, '\0', 4096);
            //for(size = 0 ; size == 0 ; size = read(s, page_content, 4096));    
            size = read(s, page_content, 4096);
            
            printf("page size: %d\n", size);
            //write(1, page_content, 4096);   //向标准输出写
            int i;
            for(i=0; i<size; i++) {
                putchar(page_content[i]);
            }
            putchar('\n');
        }
    }    
}
