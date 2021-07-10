/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：user.c
 *   创 建 者：zhaoweilong
 *   创建日期：2018年10月31日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include "head.h"

void file_server(int cfd,const char *name);
void del(int cfd,const char *name);
void updete(int cfd,const char *buf);

void login_server(int fd)
{
	char buf[MAX];
	if(fork() == 0)//开子进程
	{
		//开新tcp连接
		int cfd = accept(fd, NULL, NULL);
		if(cfd == -1)
		{
			perror("accept");
			exit(-1);
		}
		while(1)
		{
			if( read(cfd,buf,MAX) == -1)
			{
				perror("read");
				return;
			}
			//更新个人资料
			if(strcmp(buf,"updete") == 0)
			{
				read(cfd,buf,MAX);//读更新信息
				updete(cfd,buf);
			}

			if( strcmp(buf,"file") == 0)
			{
				char name[20]={0};
				read(cfd,buf,MAX);
				if(strncmp(buf,"name",4)==0)
				{	strcpy(name,buf+5);
					sqlite_create_table(name);
				}
				file_server(cfd,name);
				continue;
			}
			if(strcmp(buf,"del") == 0)
			{
				read(cfd,buf,MAX);
				del(cfd,buf);
			}
			if(strcmp(buf,"quit") == 0)
			{
				break;
			}

		}

		close(fd);
		close(cfd);
		exit(0);
	}
}
int login(int cfd,int fd2)
{
	sqlite3 *db;
	char **p;
	int r,c;
	char *s;
        char buf[MAX];
	read(cfd,buf,MAX);//读登录信息

	if( sqlite3_open("yun.db",&db) != SQLITE_OK)
	{   
		printf("error : %s\n",sqlite3_errmsg(db));
		exit(-1);
	}   

	if( sqlite3_get_table(db,buf,&p,&r,&c,&s) != SQLITE_OK )
	{   
		perror("sqlite3_get_table");
		exit(-1);
	}   
	else
	{   
		if(r != 0)//登录成功
		{   
			char username[MAX];
			strcpy(username,buf);

			bzero(buf,MAX);
			strcpy(buf,"login success");
			write(cfd,buf,MAX);
			close(cfd);
			login_server(fd2);

			return 1;
		}   
		else
		{   
			bzero(buf,MAX);
			strcpy(buf,"login fail");
			write(cfd,buf,MAX);
		}   

	}   
       return 0;
}
void enroll(int cfd)
{
	sqlite3 *db;
	char **p;
	int r,c;
	char *s;
	char buf[MAX];

	if( sqlite3_open("yun.db",&db) != SQLITE_OK)
	{   
		printf("error : %s\n",sqlite3_errmsg(db));
		exit(-1);
	}   

	read(cfd,buf,MAX);//读注册信息
	if( sqlite3_get_table(db,buf,&p,&r,&c,&s) != SQLITE_OK )
	{
		perror("sqlite3_get_table");
		bzero(buf,MAX);
		strcpy(buf,"enroll fail");
		write(cfd,buf,MAX);
		return;
	}
	else
	{
		bzero(buf,MAX);
		strcpy(buf,"enroll success");
		write(cfd,buf,MAX);
		printf("注册用户成功\n");

	}

}
void updete(int cfd,const char *buff)
{
	sqlite3 *db;
	char **p;
	int r,c;
	char *s; 
	char buf[MAX];
	strcpy(buf,buff);
	if( sqlite3_open("yun.db",&db) != SQLITE_OK)
	{   
		printf("error : %s\n",sqlite3_errmsg(db));
		exit(-1);
	}   
	if( sqlite3_get_table(db,buf,&p,&r,&c,&s) != SQLITE_OK )
	{
		perror("sqlite3_get_table");
		bzero(buf,MAX);
		strcpy(buf,"updete fail");
		write(cfd,buf,MAX);
		return;
	}
	else
	{
		bzero(buf,MAX);
		strcpy(buf,"updete success");
		write(cfd,buf,MAX);
	}

}
void del(int cfd,const char *buff)
{
	sqlite3 *db;
	char **p;
	int r,c;
	char *s; 
	char buf[MAX];
	strcpy(buf,buff);
	if( sqlite3_open("yun.db",&db) != SQLITE_OK)
	{   
		printf("error : %s\n",sqlite3_errmsg(db));
		exit(-1);
	}

	if( sqlite3_get_table(db,buf,&p,&r,&c,&s) != SQLITE_OK )
	{
		perror("sqlite3_get_table");
		bzero(buf,MAX);
		strcpy(buf,"del fail");
		write(cfd,buf,MAX);
		printf("%s\n",buf);
		return;
	}
	else
	{
		bzero(buf,MAX);
		strcpy(buf,"del success");
		write(cfd,buf,MAX);
		printf("%s\n",buf);

	}
}
