/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：user.c
 *   创 建 者：zhaoweilong
 *   创建日期：2018年10月29日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include "head.h"


void menu(int fd,const char *name);
void file_server(int cd,const char *name);


int login(int fd)
{
	char buf[MAX]={0};
	char password[MAX/8];
        char username[MAX/8];
        
	strcpy(buf, "login");
	if( write(fd, buf, MAX) == -1 )
	{
		perror("write");
		return -1;
	}
        bzero(buf, MAX);

	printf("username:");
	scanf("%s", username);
	printf("password:");
	scanf("%s", password);

	sprintf(buf, "select * from user where username='%s' and password='%s';", username, password);

	if( write(fd, buf, MAX) == -1 )
	{
		perror("write");
		return -1;
	}
	if( read(fd, buf, MAX) == -1)
	{
		perror("read");
		return -1;
	}

	if( strcmp(buf,"login success") == 0)
	{
		printf("登录成功\n");
		menu(fd,username);
	}
	else
	{
		printf("登录失败\n");
	}

	return 0;
}
int enroll(int fd)
{
	char buf[MAX]={0};
	char new_id[MAX/8], new_pwd[MAX/8], sex[2];

	strcpy(buf, "enroll");
	if( write(fd, buf, MAX) == -1 )
	{
		perror("write");
		return -1;
	}
        bzero(buf, MAX);

	printf("请输入帐号：");
	scanf("%s", new_id);
	printf("请输入密码：");
	scanf("%s", new_pwd);
	printf("请输入性别（0：女|1 ：男）");
	scanf("%s", sex);
	sprintf(buf,"insert into user values('%s','%s','%s');", new_id, new_pwd, sex);
	if( write(fd,buf,MAX) == -1 )
	{
		perror("write");
		return -1;
	}
	if(read(fd,buf,MAX) == -1)
	{
		perror("read");
		return -1;
	}
	if( strcmp(buf,"enroll success") == 0)
	{
		printf("注册成功\n");
	}
	else
	{
		printf("注册失败\n");
	}
	return 0;
}

int updete(int fd,const char *name)
{
	char pwd[MAX]={0},sex[2];
	char buf[MAX]={0};

	strcpy(buf, "updete");
	if( write(fd, buf, MAX) == -1 )
	{
		perror("write");
		return -1;
	}
        bzero(buf, MAX);

	printf("%s",name);
	printf("请输入新的密码:");
	scanf("%s",pwd);
	printf("请输入性别:");
	scanf("%s",sex);
	sprintf(buf,"update user set password='%s',sex='%s' where username='%s';",pwd,sex,name);
	if( write(fd, buf, MAX) == -1 )
	{
		perror("write");
		return -1;
	}
	printf("aaa\n");
	if( read(fd,buf,MAX) == -1)
	{
		perror("read");
		return -1;
	}
	if( strcmp(buf, "updete success") == 0 )
	{
		printf("upadte success\n");
	}
	else
	{
		printf("upadte fail\n");
	}
	return 0;
}

int del(int fd,const char *name)
{
	char buf[MAX]={0};
	char a;
	strcpy(buf, "del");
	if( write(fd, buf, MAX) == -1 )
	{
		perror("write");
		return -1;
	}
        bzero(buf, MAX);

	printf("请确定删除本帐号？y/n :\n");
	getchar();
	scanf("%c",&a);
	if( a == 'y')
	{
		sprintf(buf,"delete from user where username='%s';",name);
		if( write(fd, buf, MAX) == -1)
		{
			perror("write");
			return -1;
		}
		if( read(fd, buf, MAX) == -1)
		{
			perror("read");
			return -1;
		}
			printf("%s\n",buf);
	}
	return 0;
}
void menu(int o_fd, const char *name)
{       
	char buf[MAX];
	strcpy(buf, name);
	write(o_fd,buf, MAX);
	bzero(buf,MAX);
	close(o_fd);
        char ctr[MAX];

	//连接2222端口服务器
	int fd=tcp_send_init(2222,"0.0.0.0");
	while(1)
	{

		show_menu(); 
		printf("input> ");fflush(stdout);
		scanf("%s",ctr);
	      if(strcmp(ctr,"1") == 0)
	      {  
		      updete(fd,name);
	      }else if( strcmp(ctr,"2") == 0)
	      {
			file_server(fd,name);
	      }
	      else if( strcmp(ctr,"3") == 0)
	      {
			del(fd,name);
	      }else if( strcmp(ctr,"4") == 0)
	      {
			bzero(buf,MAX);
			strcpy(buf,"quit");
			write(fd,buf,MAX);
			close(fd);
			exit(0);
	      }
	}
}
