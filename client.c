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

#define BUFFER_SIZE 128                               //每次读写缓存大小，影响运行效率
#define SRC_FILE_NAME "src_file_client.txt"              //源文件名
#define OFFSET 0                                             //文件指针偏移量
#define TEMP 19.2367


#define portnumber 3333

int main(int argc, char *argv[]) 
{ 
	int sockfd; 
	char buffer[1024]=""; 
	struct sockaddr_in server_addr; 
	struct hostent *host;
	
	int src_file,i;
      int data_size;
      unsigned char src_buff[BUFFER_SIZE];
      int real_read_len = 0;
      char str[BUFFER_SIZE] = "this is a testabout\nopen()\nclose()\nwrite()\nread()\nlseek()\nend of the file\n";
      char test[BUFFER_SIZE] = "2017-10-19";
      char data[BUFFER_SIZE]="";


int nbytes; 
        /* 使用hostname查询host 名字 */
	if(argc!=2) 
	{ 
		fprintf(stderr,"Usage:%s hostname \a\n",argv[0]); 
		exit(1); 
	} 
	if((host=gethostbyname(argv[1]))==NULL) 
	{ 
		fprintf(stderr,"Gethostname error\n"); 
		exit(1); 
	} 
	/* 客户程序开始建立 sockfd描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:Internet;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 
	/* 客户程序填充服务端的资料 */ 
	bzero(&server_addr,sizeof(server_addr)); // 初始化,置0
	server_addr.sin_family=AF_INET;          // IPV4
	server_addr.sin_port=htons(portnumber);  // (将本机器上的short数据转化为网络上的short数据)端口号
	server_addr.sin_addr=*((struct in_addr *)host->h_addr); // IP地址
	
	/* 客户程序发起连接请求 */ 
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 
	/* 连接成功了 */ 
	printf("Please input char:\n");



	//创建源文件
      src_file=open(SRC_FILE_NAME,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);  
      if(src_file<0)
      {
            printf("open file error!!!\n");
            exit(1);
      }


                if((nbytes=read(sockfd,buffer,1024))==-1) 
		{ 
			fprintf(stderr,"Read Error:%s\n",strerror(errno)); 
			exit(1); 
		} 		
		buffer[nbytes]='\0';
		printf("Server received %s\n",buffer);
        

	//向源文件中写数据
        write(src_file,buffer,sizeof(buffer));	

	
	/* 发送数据 */
//	fgets(buffer,1024,stdin); 
//	write(sockfd,buffer,strlen(buffer)); 
	/* 结束通讯 */ 
	close(sockfd); 
	exit(0); 
} 
