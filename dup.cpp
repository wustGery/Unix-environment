/*#!/usr/bin/env bash
* ******************************************************
* Author       : Gery
* Last modified: 2018-01-08 13:45
* Email        : 2458314507@qq.com
* Filename     : dup.cpp
* Description  :
* *******************************************************/
#include<cstdio>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<iostream>
#include<sys/wait.h>

const int buf_size = 4096;

int main()
{
    char str[] = {"i am fanbo"};
    int fd[2];
    pipe(fd);//创建管道
    pid_t pid = fork();
    if(pid == 0)//子进程
    {
        close(fd[0]); //关掉管道读取端
     //   write(fd[1],str,strlen(str));
        dup2(fd[1],STDOUT_FILENO);//将标准输出挂接到写管道
        char *args[]={"ls","-l","/",0};
        execvp("ls",args);
        close(fd[1]);
    }
    else
    {
        sleep(5);
        close(fd[1]);
        char buf[buf_size];
        FILE* stream = fdopen(fd[0],"r");
        fprintf(stdout,"Data received:\n");
        while(!feof(stream)&&!ferror(stream)&&fgets(buf,sizeof(buf),stream)!=NULL)
        {
            printf("-------------\n");
            fputs(buf,stdout);
        }
        close(fd[0]);
        waitpid(pid,NULL,0);
    }
    return 0;
}
