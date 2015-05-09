#include "init.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int system(const char *command);
void *malloc(size_t size);
void *memset(void *s, int c, size_t n);
int access(const char *pathname, int mode);//F_OK,R_OK,W_OK,X_OK
DIR *opendir(const char *name);
DIR *fdopendir(int fd);

char* getCurrentUserName(void)
{
    FILE * fp;
    char *buffer = (char *)malloc(50*sizeof(char));/* 假设用户名的字符串长度不超过 50 各字符 */
    if(!buffer)
        printf("无法动态分配内存\n");
    memset(buffer,0,50*sizeof(char));

    fp=popen("who","r");
    fgets(buffer,50*sizeof(char),fp);
    pclose(fp);
    //printf("%s",buffer);

    char *tmp = buffer;
    int cnt = 0;
    while(*tmp != ' ')
    {
       tmp++;
       cnt++;
    }

    memset(tmp,0,50*sizeof(char)- cnt);

    return buffer;
}
int isDirExist(const char *abs_dir_path)/*使用绝对路径*/
{
    if(abs_dir_path == NULL)
        return 0;//目录不存在
    if(opendir(abs_dir_path) == NULL)
        return 0;//目录不存在
    return 1;//目录存在
}
int creatDirtory(const char *mkdir_pathname)
{
    int ret = system(mkdir_pathname);
    if(!ret)//0=ret时，表示mkdir 成功，即成功创建目录
        return 1;/* 创建成功 */
    else
        return 0; /* 创建失败 */
}
int isFileExist(const char *pathname)/*使用绝对路径*/
{
    if(pathname == NULL)
        return 0;//指定文件不存在
    if( !(access(pathname,F_OK) && access(pathname,R_OK) && access(pathname,W_OK)) )//
        return 1;//指定文件存在，且可读，可写
    return -1;//指定文件 不存在 或 不可读 或 不可写
}
int creatFile(const char *touch_pathfile)
{
    int ret = system(touch_pathfile);
    if(!ret)//0=ret时，表示touch 成功，即成功创指定文件
        return 1;/* 文件已经创建 */
    else
        return 0; /* 文件创建失败 */
}

