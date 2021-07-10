/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：client.c
 *   创 建 者：zhaoweilong
 *   创建日期：2018年10月28日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include "head.h"

void show_login();
void file_server();

int tcp_send_init(int port,const char *ipaddr);

int main()
{
	int fd =tcp_send_init(8888,"127.0.0.1");
	while(1)
	{
	        char ctr[MAX]={0};
	        show_login();
		printf("input> ");
		scanf("%s",ctr);
		if(strcmp(ctr,"1") == 0)
		{
			login(fd);
		}else if(strcmp(ctr,"2") == 0)
		{
			enroll(fd);
		}else{
			printf("uncomd,plese try again\n");
		}

	}
	return 0;
}
