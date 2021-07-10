/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：file_server.c
 *   创 建 者：zhaoweilong
 *   创建日期：2018年10月31日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include "head.h"

void sqlite_list(const char *username,const char *filename);
void sqlite_list_del(const char *username,const char *filename);
void sqlite_create_table(const char *name);
void sqlite_get_filelist(int fd,const char *name);

void file_server(int cfd,const char *name)
{
	char buf[MAX];
	while(1)
	{
		if( read(cfd,buf,MAX) ==0 )
		{
			exit(0);
		}
		printf("%s\n",buf);
		if(strcmp(buf, "quit") == 0)
		{
			break;
		}
		else if(strcmp(buf, "show") == 0)
		{
			sqlite_get_filelist(cfd,name);
		}
		else if( strncmp(buf,"get",3) == 0)
		{
			int fd_get = open(buf+4,O_RDONLY);
			if(fd_get == -1)
			{
				write(cfd,strcpy(buf,"0"),sizeof(buf));
				continue;
			}

			struct stat st;
			stat(buf+4,&st);
			bzero(buf,MAX);
			sprintf(buf,"%lu",st.st_size);
			write(cfd,buf,MAX);
			printf("get file size:%s\n",buf);

			while(1)
			{
				int rd=read(fd_get,buf,MAX);
				if(rd == 0)
					break;
				write(cfd,buf,rd);
			}
			close(fd_get);
		}
		else if(strncmp(buf, "put",3) == 0)
		{
			char filename[20]={0};
			strcpy(filename,buf+4);
			printf("put file :%s\n",filename);
			fflush(stdout);

			read(cfd,buf,MAX);
			int size=atoi(buf);

			if(size == 0)
			{
				printf("no such file on client\n");
				return;
			}
			int fd=open(filename,O_WRONLY|O_CREAT|O_TRUNC,0666);
			while(size)
			{
				int ret = read(cfd, buf,size<MAX? size:MAX);
				write(fd,buf,ret);
				size-=ret;
			}
			close(fd);
			sqlite_list(name,filename);
		}
		else if(strncmp(buf,"del", 3) == 0)
		{
			sqlite_list_del(name,buf+4);
			strcpy(buf,"del success");
			write(cfd,buf,MAX);
		}
		else if(strncmp(buf,"share",5) == 0)
		{
		    char filename[MAX];
		    char username[MAX];

		    strcpy(filename,strtok(buf,">"));
		    strcpy(username,strtok(NULL,""));
		    strcpy(filename,filename+6);
                    sqlite_list(username,filename);

		     strcpy(buf,"share success");
		     write(cfd,buf,MAX);
		     printf("share success\n");
		}

	}

}
void sqlite_list(const char *username,const char *filename)
{

	sqlite3 *db;

	char **p;
	int r,c;
	char *s;

	if( sqlite3_open("yun.db",&db) != SQLITE_OK)
	{
		printf("error : %s\n",sqlite3_errmsg(db));
		exit(-1);
	}
	char buf[MAX]={0};
	sprintf(buf,"insert into '%s' values('%s');",username,filename);
	if( sqlite3_get_table(db,buf,&p,&r,&c,&s) != SQLITE_OK )
	{
		perror("sqlite3_get_table");
		exit(-1);
	}
}
void sqlite_get_filelist(int fd,const char *name)
{
	sqlite3 *db;

	char **p;
	int r,c;
	char *s;

	if( sqlite3_open("yun.db",&db) != SQLITE_OK)
	{
		printf("error : %s\n",sqlite3_errmsg(db));
		return;
	}
	char buf[MAX]={0};
	sprintf(buf,"select * from '%s';",name);
	if( sqlite3_get_table(db,buf,&p,&r,&c,&s) != SQLITE_OK )
	{
		perror("sqlite3_get_table");
		return;
	}
	int i;
	for(i=1;i<r+1;i++)
	{
		printf("%s\n",p[i]);
		strcpy(buf,p[i]);
		write(fd,buf,MAX);
	}
	strcpy(buf,"&end&");
	write(fd,buf,MAX);
}
void sqlite_create_table(const char *name)
{
	sqlite3 *db;

	char **p;
	int r,c;
	char *s;

	if( sqlite3_open("yun.db",&db) != SQLITE_OK)
	{
		printf("error : %s\n",sqlite3_errmsg(db));
		exit(-1);
	}
	char buf[MAX]={0};
	sprintf(buf,"select * from '%s';",name);
	if( sqlite3_get_table(db,buf,&p,&r,&c,&s) == SQLITE_OK )
	{
		return;
	}
	else
	{
		sprintf(buf,"create table '%s'(filelist);",name);
		if( sqlite3_get_table(db,buf,&p,&r,&c,&s) != SQLITE_OK )
		{
			perror("sqlite3_get_table");
			return;
		}
	}

}
void sqlite_list_del(const char *username,const char *filename)
{

	sqlite3 *db;

	char **p;
	int r,c;
	char *s;

	if( sqlite3_open("yun.db",&db) != SQLITE_OK)
	{
		printf("error : %s\n",sqlite3_errmsg(db));
		return;
	}
	char buf[MAX]={0};
	sprintf(buf,"delete from '%s' where filelist='%s';",username,filename);
	if( sqlite3_get_table(db,buf,&p,&r,&c,&s) != SQLITE_OK )
	{
		perror("sqlite3_get_table");
		return;
	}
	else
	{
		printf("del success\n");
	}
}

