/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：service.c
 *   创 建 者：zhaoweilong
 *   创建日期：2018年10月28日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include "head.h"

int tcp_rev_init(int port, const char *ipaddr, int nulm);
int login(int cfd,int fd2);
void enroll(int cfd);

void signal_fun(int a)
{
	wait(NULL);
}

int main()
{
	char buf[MAX]={0};
	int fd = tcp_rev_init(POST2, IP, LISTEN);
	int fd2 = tcp_rev_init(POST1, IP, LISTEN);
	struct sockaddr_in c_addr;
	signal(SIGCHLD, signal_fun);

	while(1)
	{
		int size=sizeof(c_addr);
		int cfd = accept(fd,(struct sockaddr *)&c_addr,&size);
		if(cfd == -1)
		{
			perror("accept");
			return -1;
		}
		printf("connect form <%s>\n",inet_ntoa(c_addr.sin_addr));
		//进行登录，注册服务
		if(fork() == 0)
		{
			close(fd);
			while(1)
			{
				if( read(cfd,buf,MAX) == -1)
				{
					perror("read");
					exit(-1);
				}

				if( strcmp(buf, "login") == 0)//收到登录请求
				{
					if( login(cfd, fd2) == 1)//验证账户和密码
					{
						break;
					}
				}
				if( strcmp(buf, "enroll") == 0)//收到注册请求
				{
					enroll(cfd);
				}
			}
			wait(NULL);
			exit(0);
		}
	}
	return 0;
}
