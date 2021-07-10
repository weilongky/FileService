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
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX 128


int tcp_send_init(int port, const char *ipaddr);
int tcp_rev_init(int port, const char *ipaddr, int nulm);

int login(int fd);
int enroll(int fd);
int updete(int fd,const char *name);
int del(int fd,const char *name);

void show_login();
void show_menu();
void show_file_menu();

void menu(int fd,const char *name);
void file_server(int fd,const char *name);

#endif
