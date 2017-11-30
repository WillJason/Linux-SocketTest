#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 

#include <unistd.h>
#include <fcntl.h>
#include<sys/stat.h>



#define portnumber 3333

#define BUFFER_SIZE 128                               //每次读写缓存大小，影响运行效率
#define SRC_FILE_NAME "src_file.txt"              //源文件名
#define OFFSET 0                                             //文件指针偏移量
#define TEMP 19.2367

#define MAX_SIZE 1024

int main(int argc, char *argv[]) 
{ 
	int sockfd,new_fd,j; 
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr; 
	int sin_size; 
	int nbytes;
	char buffer[1024];
	
        int src_file,i;
        int data_size;
        unsigned char src_buff[BUFFER_SIZE];
        int real_read_len = 0;
        char str[BUFFER_SIZE] = "this is a testabout\nopen()\nclose()\nwrite()\nread()\nlseek()\nend of the file\n";
        char test[BUFFER_SIZE] = "2017-10-19";
        char data[BUFFER_SIZE]="";


	char buf[MAX_SIZE];
	FILE *fp;



	/* 服务器端开始建立sockfd描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	/* 服务器端填充 sockaddr结构 */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); // 初始化,置0
	server_addr.sin_family=AF_INET;                 // Internet
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // (将本机器上的long数据转化为网络上的long数据)和任何主机通信  //INADDR_ANY 表示可以接收任意IP地址的数据，即绑定到所有的IP
	//server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //用于绑定到一个固定IP,inet_addr用于把数字加格式的ip转化为整形ip
	server_addr.sin_port=htons(portnumber);         // (将本机器上的short数据转化为网络上的short数据)端口号
	
	/* 捆绑sockfd描述符到IP地址 */ 
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	/* 设置允许连接的最大客户端数 */ 
	if(listen(sockfd,5)==-1) 
	{ 
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 


       //创建源文件
//       src_file=open(SRC_FILE_NAME,O_RDWR|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);  
//       if(src_file<0)
//       {
//            printf("open file error!!!\n");
//            exit(1);
//       }

	if((fp=fopen("src_file.txt","r"))==NULL)
	{
		perror("fail to read");
		exit(1);
	}





	while(1) 
	{ 
		/* 服务器阻塞,直到客户程序建立连接 */ 
		sin_size=sizeof(struct sockaddr_in); 
		if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1) 
		{ 
			fprintf(stderr,"Accept error:%s\n\a",strerror(errno)); 
			exit(1); 
		}
                inet_ntoa(client_addr.sin_addr); 
		//fprintf(stderr," %s\n",inet_ntoa(client_addr.sin_addr)); // 将网络地址转换成.字符串
		//printf("Server get connection from \n");
//		if((nbytes=read(new_fd,buffer,1024))==-1) 
//		{ 
//			fprintf(stderr,"Read Error:%s\n",strerror(errno)); 
//			exit(1); 
//		} 		
//		buffer[nbytes]='\0';
//		printf("Server received %s\n",buffer);
		
		/* 发送数据 */
		
///	        read(src_file,buffer,1024);
//
//	        write(new_fd,buffer,strlen(buffer));
//		printf("Send success!\n"); 
  

		while(fgets(buf,MAX_SIZE,fp)!=NULL)
		{
			write(new_fd,buf,strlen(buf));
	                printf("Send success!\n"); 
		}


      	
		
		/* 这个通讯已经结束 */ 
		close(new_fd); 
		/* 循环下一个 */ 
	} 
	/* 结束通讯 */ 
	close(sockfd); 
	exit(0); 
} 
