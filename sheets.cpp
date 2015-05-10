#include "sheets.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <dirent.h>
#include <string>
#include <iostream>
extern std::string userSysName;
extern std::string CMDA_sheets_path_usr_en_abs;
extern std::string CMDA_sheets_path_usr_zh_abs;

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
    if( !(access(pathname,F_OK) && access(pathname,R_OK)) )//
        return 1;//指定文件存在，且可读
    return -1;//指定文件 不存在 或 不可读
}
int creatFile(const char *touch_pathfile)
{
    int ret = system(touch_pathfile);
    if(!ret)//0=ret时，表示touch 成功，即成功创指定文件
        return 1;/* 文件已经创建 */
    else
        return 0; /* 文件创建失败 */
}
sheets* readFileList(const char *basePath)
{
    DIR *dir;
    struct dirent *ptr;

    if ((dir=opendir(basePath)) == NULL)
    {
        printf("Open dir: '%s' error...",basePath);
        exit(1);
    }

    sheets *buf = (sheets*)malloc(sizeof(sheets));
    if(!buf)
    {
        perror("Can not get enough memory for sheets\n");
        exit(1);
    }
    memset((void*)buf,'\0',sizeof(sheets));
    buf->curpath = basePath;
    buf->curfilescnt = 0;
    buf->childDirCnt = 0;

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0) //current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    //file
        {
            if(buf->curfilescnt <= CMDA_SDFMaxNum)
            {
                char *wlc_tmp = (char*)malloc(CMDA_FNMaxChNum*sizeof(char));
                if(!wlc_tmp)
                {
                    perror("Can not get enough memory for file name\n");
                    exit(1);
                }
                memset((void*)wlc_tmp,'\0',CMDA_FNMaxChNum*sizeof(char));

                strcpy(wlc_tmp,ptr->d_name);

                buf->curfiles[buf->curfilescnt] = wlc_tmp;
                #ifdef CMDA_DEBUG_STD_COUT
                printf("filename:\t%s\n",buf->curfiles[buf->curfilescnt]);
                #endif
                buf->curfilescnt += 1;
            }
            else
            {
                perror("in file 'debug.h', to reset a big number of 'CMDA_SDFMaxNum'");
                exit(1);
            }
        }
        else if(ptr->d_type == 10)  //software link file
        {
            if(buf->curfilescnt <= CMDA_SDFMaxNum)
            {
                char *wlc_tmp = (char*)malloc(CMDA_FNMaxChNum*sizeof(char));
                if(!wlc_tmp)
                {
                    perror("Can not get enough memory for file name\n");
                    exit(1);
                }
                memset((void*)wlc_tmp,'\0',CMDA_FNMaxChNum*sizeof(char));

                strcpy(wlc_tmp,ptr->d_name);

                buf->curfiles[buf->curfilescnt] = wlc_tmp;
                #ifdef CMDA_DEBUG_STD_COUT
                printf("filename:slink:\t%s\n",buf->curfiles[buf->curfilescnt]);
                #endif
                buf->curfilescnt += 1;
            }
            else
            {
                perror("in file 'debug.h', to reset a big number of 'CMDA_SDFMaxNum'");
                exit(1);
            }
        }
        else if(ptr->d_type == 4)   //dir
        {
            char *base = (char*)malloc(CMDA_APMaxChNum*sizeof(char));
            if(!base)
            {
                perror("Can not get enough memory for dir name\n");
                exit(1);
            }
            memset((void*)base,'\0',CMDA_FNMaxChNum*sizeof(char));

            //memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,ptr->d_name);
            strcat(base,"/");
            if(buf->childDirCnt <= CMDA_SDCDMaxNum)
            {
                buf->childDir[buf->childDirCnt] = readFileList(base);
                buf->childDirCnt += 1;
            }
            else
            {
                perror("in file 'debug.h', to reset a big number of 'CMDA_SDCDMaxNum'");
                exit(1);
            }
        }
    }
    closedir(dir);
    #ifdef CMDA_DEBUG_STD_COUT
    printf("Dir:\t%s\n",buf->curpath);
    printf("Current Dir total files:\t%d\n\n",buf->curfilescnt);
    #endif

    return buf;
}

SearchResult::SearchResult(int mmn)
{
    cnt = mmn;
    pathfile = new std::string[mmn];
}
SearchResult::~SearchResult(void)
{
    switch(cnt)
    {
        case 0:
        case 1:
        {
            delete pathfile;
            break;
        }
        case 2:
        default:
        {
            delete [] pathfile;
        }
    };
}

SearchScheme::SearchScheme(void)
{
    db = NULL;
    language = 0;//0,英文；1，中文；2，中英

    next = NULL;//指向子目录
    nextcnt = 0;//搜索的子目录计数
}
SearchScheme::~SearchScheme(void)
{}
void SearchScheme::setSheets(sheets *sh)
{
    db = sh;
}
void SearchScheme::setLanguage(int lan)
{
    language = lan;
}
int SearchScheme::find(SearchResult *result, std::string what, int index)
{
    int howmuch = 0;//成功找到文件的个数

    if(nextcnt == 0)
    {
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "当前搜索目录：" << db->curpath << std::endl;
        std::cout << "搜索：" << what << std::endl;
        #endif

        std::string f;//候选文件
        std::string d = db->curpath;//当前目录，首个路径不需要free
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "目录文件列表如下：" << std::endl;
        #endif

        for(int i=0;i < db->curfilescnt;i++)
        {
            #ifdef CMDA_DEBUG_STD_COUT
            std::cout << db->curfiles[i] << std::endl;
            #endif
            f = db->curfiles[i];//候选文件
            free((void*)db->curfiles[i]);

            if(f == what)
            {
                result->pathfile[index] = d + f;
                howmuch++;
                index++;
                break;//每个目录下的文件名是唯一的，找到后不再搜索
            }
        }

        //处理当前目录子目录
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "子目录个数:" << db->childDirCnt << std::endl;
        #endif
        for(int i =0; i < db->childDirCnt; i++)
        {
            next = db->childDir[i];
            nextcnt++;

            if(index >= 9)
            {
                std::cout << "搜索：" << what << "超过 " << 9 << " 个\n";
                break;
            }
            int k = find(result,what,index);//子目录下成功匹配的个数
            howmuch += k;
            if(k)
            {
                index++;//只有在子目录下匹配成功时，记k的值大于0时才加
            }
            free(db->childDir[i]);
        }
    }
    else
    {
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "当前搜索目录：" << next->curpath << std::endl;
        std::cout << "搜索：" << what << std::endl;
        #endif

        std::string f;//候选文件
        std::string d = next->curpath;//当前目录
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "目录文件列表如下：" << std::endl;
        #endif

        for(int i=0;i < next->curfilescnt;i++)
        {
            #ifdef CMDA_DEBUG_STD_COUT
            std::cout << next->curfiles[i] << std::endl;
            #endif
            f = next->curfiles[i];//候选文件
            free((void*)next->curfiles[i]);

            if(f == what)
            {
                if(index >= 9)
                {
                    std::cout << "搜索：" << what << "超过 " << 9 << " 个\n";
                    return howmuch;
                }

                result->pathfile[index] = d + f;
                howmuch++;
                index++;
                break;//每个目录下的文件名是唯一的，找到后不再搜索
            }
        }

        //处理当前目录子目录
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "子目录个数:" << next->childDirCnt << std::endl;
        #endif
        for(int i =0; i < next->childDirCnt; i++)
        {
            next = next->childDir[i];
            nextcnt++;

            if(index >= 9)
            {
                std::cout << "搜索：" << what << "超过 " << 9 << " 个\n";
                return howmuch;
            }

            int k = find(result,what,index);//子目录下成功匹配的个数
            howmuch += k;
            if(k)
            {
                index++;//只有在子目录下匹配成功时，记k的值大于0时才加
            }

            free(next->childDir[i]);
        }
    }

    #ifdef CMDA_DEBUG_STD_COUT
    std::cout << "匹配个数：" << howmuch << std::endl;
    #endif
    return howmuch;
}

bool init(void)
{
    char *tmpc = getCurrentUserName();
    #ifdef CMDA_DEBUG_STD_COUT
    printf("用户名：%s\n",tmpc);
    #endif
    if(!tmpc)
    {
        printf("Something wrong happened when to get user's system name\n");
        exit(1);
    }
    userSysName = tmpc;
    free(tmpc);

    std::string tmps_en = "/home/" + userSysName + "/" + CMDA_sheets_path_usr_en;
    std::string tmps_zh = "/home/" + userSysName + "/" + CMDA_sheets_path_usr_zh;
    CMDA_sheets_path_usr_en_abs = tmps_en;
    CMDA_sheets_path_usr_zh_abs = tmps_zh;
    #ifdef CMDA_DEBUG_STD_COUT
    std::cout << "中文目录@init：" << tmps_en << std::endl;
    std::cout << "英文目录@init：" << tmps_zh << std::endl;
    #endif

    //系统，en
    bool no_sheets_dir_sys_en = false;
    bool new_sheets_dir_sys_en = false;
    if(!isDirExist(CMDA_sheets_path_sys_en.data()))
    {
        std::string mkdir_tmps_en = "sudo mkdir -p " + CMDA_sheets_path_sys_en;
        if(creatDirtory(mkdir_tmps_en.data()))
        {
            std::cout << "新建：'" << CMDA_sheets_path_sys_en << "'目录\n";
            new_sheets_dir_sys_en = true;
        }
        else
        {
            std::cout << "无法创建'" << CMDA_sheets_path_sys_en << "'目录\n";
            no_sheets_dir_sys_en = true;

        }
    }
    //系统，zh
    bool no_sheets_dir_sys_zh = false;
    bool new_sheets_dir_sys_zh = false;
    if(!isDirExist(CMDA_sheets_path_sys_zh.data()))
    {
        std::string mkdir_tmps_zh = "sudo mkdir -p " + CMDA_sheets_path_sys_zh;
        if(creatDirtory(mkdir_tmps_zh.data()))
        {
            std::cout << "新建：'" << CMDA_sheets_path_sys_zh << "'目录\n";
            new_sheets_dir_sys_zh = true;
        }
        else
        {
            std::cout << "无法创建'" << CMDA_sheets_path_sys_zh << "'目录\n";
            no_sheets_dir_sys_zh = true;
        }
    }

    //用户，en
    bool no_sheets_dir_usr_en = false;
    bool new_sheets_dir_usr_en = false;
    if(!isDirExist(tmps_en.data()))
    {
        std::string mkdir_tmps_en = "mkdir -p " + tmps_en;
        if(creatDirtory(mkdir_tmps_en.data()))
        {
            std::cout << "新建：'" << tmps_en << "'目录\n";
            new_sheets_dir_usr_en = true;
        }
        else
        {
            std::cout << "无法创建'" << tmps_en << "'目录\n";
            no_sheets_dir_usr_en = true;
        }
    }
    //用户，zh
    bool no_sheets_dir_usr_zh = false;
    bool new_sheets_dir_usr_zh = false;
    if(!isDirExist(tmps_zh.data()))
    {
        std::string mkdir_tmps_zh = "mkdir -p " + tmps_zh;
        if(creatDirtory(mkdir_tmps_zh.data()))
        {
            std::cout << "新建：'" << tmps_zh << "'目录\n";
            new_sheets_dir_usr_zh = true;
        }
        else
        {
            std::cout << "无法创建'" << tmps_zh << "'目录\n";
            no_sheets_dir_usr_zh = true;
        }
    }

    if(no_sheets_dir_sys_en)
    {
        printf("None exist of dir %s, and i can't creat it\n",CMDA_sheets_path_sys_en.data());
    }
    if(no_sheets_dir_sys_zh)
    {
        printf("None exist of dir %s, and i can't creat it\n",CMDA_sheets_path_sys_zh.data());
    }
    if(no_sheets_dir_usr_en)
    {
        printf("None exist of dir %s, and i can't creat it\n",tmps_en.data());
    }
    if(no_sheets_dir_usr_zh)
    {
        printf("None exist of dir %s, and i can't creat it\n",tmps_zh.data());
    }
    if(no_sheets_dir_sys_en && no_sheets_dir_sys_zh &&
       no_sheets_dir_usr_en && no_sheets_dir_usr_zh)
    {
        printf("None exist dir for sheets, do checking...\n");
        exit(0);
    }

    if(new_sheets_dir_sys_en && new_sheets_dir_sys_zh &&
       new_sheets_dir_usr_en && new_sheets_dir_usr_zh)
    {
        printf("in sheets dir there is nothing, they are new creating\n");
        exit(0);
    }

    return true;
}
