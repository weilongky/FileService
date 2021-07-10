/*===============================================================
 *   Copyright (C) 2018 All rights reserved.
 *   
 *   文件名称：file.c
 *   创 建 者：zhaoweilong
 *   创建日期：2018年10月29日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include "head.h"

void show_file_menu();
void show_file_help();

int tcp_sen_init(int port ,const char *ipaddr);


char buf[MAX]={0};

void get_file(int fd)
{
	write(fd, buf, MAX);

	char filename[20]={0};
	strcpy( filename, buf+4);
	read( fd, buf, MAX);
	printf( "%s\n", buf );
	int size = atoi( buf );
	if( size == 0)
	{
		printf("no such file on server\n");
		return;
	}
	char path[MAX]="./userfile/";
        strcat(path,filename);
	int file_d = open( path, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	int ret;
	while( size )
	{
		ret = read(fd, buf,size<MAX? size:MAX);
		write( file_d, buf, ret );
		size -= ret;
	}
	close(ret);
	close(file_d);
	printf("--------------------\n");
	printf("下载成功\n");
}

void put_file(int fd)
{
	write(fd,buf,MAX);
	char path[MAX]="./userfile/";
        strcat(path,buf+4);
	int fd_get = open(path, O_RDONLY, 0666);
	if(fd_get == -1)
	{
		write(fd,strcpy(buf,"0"),MAX);
		perror("open");
		return;
	}

	struct stat st;
	stat(path,&st);
	bzero(buf,MAX);
	sprintf(buf,"%lu",st.st_size);
	write(fd,buf,MAX);
	printf("file size:%s\n",buf);

	while(1)
	{
		int rd=read(fd_get,buf,MAX);
		if(rd == 0)
			break;
		write(fd,buf,rd);
	}
	printf("--------------------\n");
	printf("上传成功\n");
	close(fd_get);
}
void get_list(int fd)
{
	write(fd,buf,MAX);
	int a=0;
	printf("------------云端文件------------\n");
	while( read(fd,buf,MAX) != 0) 
	{
		if(strcmp(buf,"&end&") == 0)
		{
			break;
		}
		printf("%s  ",buf);
		a++;
		if(a > 2)
		{
			a=0;
			putchar('\n');
		}
	}
	putchar('\n');
	printf("------------end------------\n");
}
void del_file(int fd)
{
	write(fd,buf,MAX);
	read(fd,buf,MAX);
	printf("%s\n",buf);
}
void ls()
{
	DIR *dr;
	struct dirent *dir;
	dr=opendir("./userfile");
	if( dr == NULL)
	{
		perror("opendir");
		return;
	}
	printf("------------本机文件------------\n");
	while((dir = readdir(dr)) != NULL)
	{
		printf("%s\t",dir->d_name);
	}
	printf("\n");
	printf("------------end------------\n");
	closedir(dr);
}
void share_file(int fd)
{
	write(fd,buf,MAX);
	read(fd,buf,MAX);
	printf("%s\n",buf);
}
void file_server(int fd,const char *name)
{
	strcpy(buf,"file");
	write(fd,buf,MAX);
	sprintf(buf,"name:%s",name);
	write(fd,buf,MAX);
	show_file_menu();
	while(1)
	{ 
		printf("command:");
		scanf("%s",buf);
		if( strncmp(buf,"put",3) == 0)
		{
			put_file(fd);
		}
		else if( strncmp(buf,"get",3) == 0)
		{
			get_file(fd);
		}
		else if( strncmp(buf,"del",3) == 0)
		{
			del_file(fd);
		}
		else if( strncmp(buf,"share",5) == 0)
		{
			share_file(fd);
		}
		else if(strcmp(buf,"show") == 0)
		{
			get_list(fd);
		}
		else if(strcmp(buf,"quit") == 0)
		{
			write(fd,buf,MAX);
			break; 
		}
		else if(strcmp(buf,"help") == 0)
		{
			show_file_menu();
		}
		else if(strcmp(buf,"ls") == 0)
		{
			ls();
		}
		bzero(buf,MAX);
	}
}
