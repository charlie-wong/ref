#ifndef CMDA_SHEETS_H
#define CMDA_SHEETS_H
#include "debug.h"
#include <string>

C_LANGUAGE_BEGIN

char *getCurrentUserName(void);/* 返回用户名,不用时,free返回值 */
int isDirExist(const char *abs_dir_path);/*绝对路径,0不存在,1存在*/
int creatDirtory(const char *mkdir_pathname);/*0创建失败,1创建成功*/
int isFileExist(const char *pathname);/*绝对路径,0不存在,1存在可读,-1不存在 或 不可读*/
int creatFile(const char *touch_pathfile);/*0创建失败,1创建成功*/

struct sheets
{
    const char *curpath;//当前目录绝对路径

    const char *curfiles[CMDA_SDFMaxNum];//某目录下所有的文件名
    int curfilescnt;

    sheets *childDir[CMDA_SDCDMaxNum];
    int childDirCnt;//当前目录下子目录个数（除 . 和 .. 外)
};
sheets* readFileList(const char *basePath);/*递归读取表单目录下的文件*/

C_LANGUAGE_END

bool init(void);//启动初始化，相关资源查检索
class SearchResult
{
public:
    explicit SearchResult(int mmn);

    ~SearchResult(void);

    std::string *pathfile;
    int cnt;
};
class SearchScheme
{
public:
    SearchScheme(void);
    ~SearchScheme(void);
    int find(SearchResult *result, int index, std::string what);//查找指定命令文件

    void setSheets(sheets *sh);
    void setLanguage(int lan);
private:
    sheets *db;
    int language;//0,英文；1，中文；2，中英

    sheets *next;//指向子目录
    int nextcnt;//搜索的目录计数
};



#endif
