/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：tcpip.h
 *   创 建 者：zhaoweilong
 *   创建日期：2018年10月29日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sqlite3.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 128
#define LISTEN 50

#define POST1 2222
#define POST2 8888
#define IP "0.0.0.0"

void sqlite_list(const char *username,const char *filename);
void sqlite_list_del(const char *username,const char *filename);
void sqlite_create_table(const char *name);
void sqlite_get_filelist(int fd,const char *name);

void file_server(int cfd,const char *name);
int login(int cfd,int fd2);
void enroll(int cfd);

int tcp_rev_init(int port, const char *ipaddr, int nulm);

#endif
