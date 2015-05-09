#ifndef CMDA_INIT_H
#define CMDA_INIT_H
#include <string>

extern "C" {
char *getCurrentUserName(void);/* 返回用户名,不用时,free返回值 */
int isDirExist(const char *abs_dir_path);/*绝对路径,0不存在,1存在*/
int creatDirtory(const char *mkdir_pathname);/*0创建失败,1创建成功*/
int isFileExist(const char *pathname);/*绝对路径,0不存在,1存在可读可写,-1不存在 或 不可读 或 不可写*/
int creatFile(const char *touch_pathfile);/*0创建失败,1创建成功*/
}

class Init
{
    Init(void);
    ~Init(void);
};
#endif
