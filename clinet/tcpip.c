/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：tcpip.c
 *   创 建 者：zhaoweilong
 *   创建日期：2018年10月28日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include "head.h"

int tcp_send_init(int port, const char *ipaddr)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	if(fd == -1)
	{
		perror("socket");
		exit(-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ipaddr);

	if(connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
	        perror("connect");
	        exit(-1);
	}
	return fd;
}

int tcp_rev_init(int port, const char *ipaddr, int num)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	if(fd == -1)
	{
		perror("socket");
		exit(-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ipaddr);

	if( bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("bind");
		exit(-1);
	}

        listen(fd, num);
        return fd;
}
