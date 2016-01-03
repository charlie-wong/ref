#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "core.h"
#include "setting.h"
#include "debug.h"

#define MAX_LINE_CHAR_NUM 2048

extern char *optarg;  //当前带参数的选项的参数
extern int optind;    //处理当前选项索引值的下一个,初始化值默认是1; 重置为 1 ,再次扫描
extern int opterr;    //对不在optstring中的选项字符,给出警告; 设置成 0 ,阻止警告生成
extern int optopt;    //对不在optstring中的选项字符, 将其放在此变量中

extern int SearchAreaNum;
extern int SearchAreaList[10];
extern int SearchLanguage;
extern int LanguagePriorityList[2];
extern bool MutilMatchShowFileList;
SearchBasePath searchArea;

#ifdef DEBUG_REF
void showSheets(const Sheets *wlc)
{
    // files
    int cnt = 0;
    while(cnt < wlc->curFilesCnt)
    {
        std::cout << wlc->curPath << "/" << wlc->curFiles[cnt] << std::endl;
        cnt++;
    }

    // subdirs
    std::cout << "-----------------\n";
    cnt = 0;
    while(cnt < wlc->childDirCnt)
    {
        showSheets(wlc->childDir[cnt]);
        cnt++;
    }
}
void showSearchArea(void)
{
    int i = 0;
    while(i < searchArea.cnt)
    {
        std::cout << searchArea.bp[i] << std::endl;
        i++;
    }
}
#endif

void setSearchArea(void)
{
    searchArea.clear();
    std::string man9dir[] = {"0","1","2","3","4","5","6","7","8","9"};

    if(SearchAreaNum < 0 || SearchAreaNum > 9) SearchAreaNum = 0;
    if(SearchLanguage < 0 || SearchLanguage > 2) SearchLanguage = 0;

    if(SearchAreaList[0])
    {
        if(SearchLanguage == 0)// en/zh
        {
            if(LanguagePriorityList[0] == 1)// en 优先
            {
                int cnt = 1;
                while(cnt < 10)
                {
                    int area = SearchAreaList[cnt];
                    if(area == 0) break;
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[area] + "/en";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[area] + "/en";
                    searchArea.cnt++;
                    cnt++;
                }
                cnt = 1;
                while(cnt < 10)
                {
                    int area = SearchAreaList[cnt];
                    if(area == 0) break;
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[area] + "/zh";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[area] + "/zh";
                    searchArea.cnt++;
                    cnt++;
                }
            }
            else// zh 优先
            {
                int cnt = 1;
                while(cnt < 10)
                {
                    int area = SearchAreaList[cnt];
                    if(area == 0) break;
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[area] + "/zh";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[area] + "/zh";
                    searchArea.cnt++;
                    cnt++;
                }
                cnt = 1;
                while(cnt < 10)
                {
                    int area = SearchAreaList[cnt];
                    if(area == 0) break;
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[area] + "/en";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[area] + "/en";
                    searchArea.cnt++;
                    cnt++;
                }
            }
        }
        else if(SearchLanguage == 1)// en
        {
            int cnt = 1;
            while(cnt < 10)
            {
                int area = SearchAreaList[cnt];
                if(area == 0) break;
                searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[area] + "/en";
                searchArea.cnt++;
                searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[area] + "/en";
                searchArea.cnt++;
                cnt++;
            }
        }
        else// zh
        {
            int cnt = 1;
            while(cnt < 10)
            {
                int area = SearchAreaList[cnt];
                if(area == 0) break;
                searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[area] + "/zh";
                searchArea.cnt++;
                searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[area] + "/zh";
                searchArea.cnt++;
                cnt++;
            }
        }
    }
    else
    {
        if(SearchAreaNum == 0)// 1 ~ 9
        {
            if(SearchLanguage == 0)// en/zh
            {
                if(LanguagePriorityList[0] == 1)// en 优先
                {
                    int cnt = 1;
                    while(cnt < 10)
                    {
                        searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[cnt] + "/en";
                        searchArea.cnt++;
                        searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[cnt] + "/en";
                        searchArea.cnt++;
                        cnt++;
                    }
                    cnt = 1;
                    while(cnt < 10)
                    {
                        searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[cnt] + "/zh";
                        searchArea.cnt++;
                        searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[cnt] + "/zh";
                        searchArea.cnt++;
                        cnt++;
                    }
                }
                else// zh 优先
                {
                    int cnt = 1;
                    while(cnt < 10)
                    {
                        searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[cnt] + "/zh";
                        searchArea.cnt++;
                        searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[cnt] + "/zh";
                        searchArea.cnt++;
                        cnt++;
                    }
                    cnt = 1;
                    while(cnt < 10)
                    {
                        searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[cnt] + "/en";
                        searchArea.cnt++;
                        searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[cnt] + "/en";
                        searchArea.cnt++;
                        cnt++;
                    }
                }
            }
            else if(SearchLanguage == 1)// en
            {
                int cnt = 1;
                while(cnt < 10)
                {
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[cnt] + "/en";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[cnt] + "/en";
                    searchArea.cnt++;
                    cnt++;
                }
            }
            else// zh
            {
                int cnt = 1;
                while(cnt < 10)
                {
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[cnt] + "/zh";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[cnt] + "/zh";
                    searchArea.cnt++;
                    cnt++;
                }
            }
        }
        else  // 指定
        {
            if(SearchLanguage == 0)// en/zh
            {
                if(LanguagePriorityList[0] == 1)// en 优先
                {
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[SearchAreaNum] + "/en";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[SearchAreaNum] + "/en";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[SearchAreaNum] + "/zh";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[SearchAreaNum] + "/zh";
                    searchArea.cnt++;
                }
                else// zh 优先
                {
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[SearchAreaNum] + "/zh";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[SearchAreaNum] + "/zh";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[SearchAreaNum] + "/en";
                    searchArea.cnt++;
                    searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[SearchAreaNum] + "/en";
                    searchArea.cnt++;
                }
            }
            else if(SearchLanguage == 1)// en
            {
                searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[SearchAreaNum] + "/en";
                searchArea.cnt++;
                searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[SearchAreaNum] + "/en";
                searchArea.cnt++;
            }
            else// zh
            {
                searchArea.bp[searchArea.cnt] = ref_sheets_root_path + "/" + man9dir[SearchAreaNum] + "/zh";
                searchArea.cnt++;
                searchArea.bp[searchArea.cnt] = ref_sheets_user_path + "/" + man9dir[SearchAreaNum] + "/zh";
                searchArea.cnt++;
            }
        }
    }
}
Sheets* getSheets(const char *basePath)
{
    DIR *dir = opendir(basePath);

    if(dir == NULL)
    {
        fprintf(stderr,"Open dir: '%s' error...\n", basePath);
        return NULL;
    }
    Sheets *buf = (Sheets*)malloc(sizeof(Sheets));
    if(buf == NULL)
    {
        fprintf(stderr,"Can not get enough memory.\n");
        return NULL;
    }

    memset((void*)buf,'\0',sizeof(Sheets));

    buf->curPath = (char*)malloc(MAX_VALID_CHAR_NUM_FORAP*sizeof(char));
    if(!buf->curPath)
    {
        fprintf(stderr,"Can not get enough memory.\n");
        free(buf);
        return NULL;
    }
    memset((void*)buf->curPath,'\0',MAX_VALID_CHAR_NUM_FORAP*sizeof(char));
    strcpy(buf->curPath,basePath);
    buf->curFilesCnt = 0;
    buf->childDirCnt = 0;

    struct dirent *ptr;
    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)
            continue;
        else if(ptr->d_type == 8)   //file
        {
            if(buf->curFilesCnt <= DIR_MAX_FILE_ENTRY_NUM)
            {
                char *wlc_tmp = (char*)malloc(MAX_VALID_FILE_NAME_CHAR*sizeof(char));
                if(!wlc_tmp)
                {
                    fprintf(stderr,"Can not get enough memory.\n");
                    free(buf);
                    return NULL;
                }
                memset((void*)wlc_tmp,'\0',MAX_VALID_FILE_NAME_CHAR*sizeof(char));

                strcpy(wlc_tmp,ptr->d_name);

                buf->curFiles[buf->curFilesCnt] = wlc_tmp;
                buf->curFilesCnt += 1;
            }
            else
            {
                fprintf(stderr,"Too much file matched ...\n");
            }
        }
        else if(ptr->d_type == 10)  //software link file
        {
            if(buf->curFilesCnt <= DIR_MAX_FILE_ENTRY_NUM)
            {
                char *wlc_tmp = (char*)malloc(MAX_VALID_FILE_NAME_CHAR*sizeof(char));
                if(!wlc_tmp)
                {
                    fprintf(stderr,"Can not get enough memory.\n");
                    free(buf);
                    return NULL;
                }
                memset((void*)wlc_tmp,'\0',MAX_VALID_FILE_NAME_CHAR*sizeof(char));

                strcpy(wlc_tmp,ptr->d_name);

                buf->curFiles[buf->curFilesCnt] = wlc_tmp;
                buf->curFilesCnt += 1;
            }
            else
            {
                fprintf(stderr,"Too much file matched ...\n");
            }
        }
        else if(ptr->d_type == 4)   //dir
        {
            char *base = (char*)malloc(MAX_VALID_CHAR_NUM_FORAP*sizeof(char));
            if(!base)
            {
                fprintf(stderr,"Can not get enough memory.\n");
                free(buf);
                return NULL;
            }
            memset((void*)base,'\0',MAX_VALID_CHAR_NUM_FORAP*sizeof(char));

            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            //strcat(base,"/");
            if(buf->childDirCnt <= DIR_MAX_DIRE_ENTRY_NUM)
            {
                buf->childDir[buf->childDirCnt] = getSheets(base);
                buf->childDirCnt += 1;
            }
            else
            {
                fprintf(stderr,"Too much subdirectories ...\n");
            }
        }
    }
    closedir(dir);
    return buf;
}

void searchEngine(const std::string &what)
{
    Search result(what);

    setSearchArea();
    int i = 0;
    while(i < searchArea.cnt)
    {
        result.find(getSheets(searchArea.bp[i].data()));
        i++;
    }

    if(result.curCnt > 1 && MutilMatchShowFileList)
    {
        std::cout << "search for: [" << what << "]\n";
        result.showMatchFiles();
    }
    else
    {
        std::string tmp;
        while(!(tmp=result.getMatchFile()).empty())
        {
            Content ts(tmp);
            ts.show();
        }
    }
}
void getSearchCandidates(int argc, char **argv)
{
    if(optind != argc)
    {
        //搜索筛选
        std::string what;
        for(int i = optind; i < argc; i++)
        {
            what = argv[i];
            size_t len = what.length();
            if(len == 1)
            {
                char ch[] = {what[0],0};
                int area = atoi(ch);
                if(area >=1 && area <= 9)
                {
                    SearchAreaNum = area;
                    continue;
                }

            }
            searchEngine(what);
        }
    }
}

Search::Search(const std::string &nwhat)
{
    maxCnt   = MAX_MATCH_FILE_NUM;
    curCnt   = 0;
    pathName = new std::string[maxCnt];

    db       = NULL;
    this->what = nwhat;
}
Search::~Search(void)
{
    delete [] pathName;
}
bool Search::find(Sheets *xdb)
{
    clsOldSheets(this->db);
    this->db = xdb;

    searchSheets(this, NULL, true);
    return true;
}
void Search::showMatchFiles(void)
{
    for(int i=0; i<curCnt; i++)
    {
        std::cout << pathName[i] << std::endl;
    }
}
std::string Search::getMatchFile(void)
{
    if(index<0 || index>=curCnt)
    {
        index = 0;
        return "";
    }

    std::string tmp = pathName[index];
    index++;
    return tmp;
}

int Search::index = 0;
void Search::clsOldSheets(Sheets *s)
{
    if(s == NULL) return;

    free(s->curPath);

    for(int i=0; i<s->curFilesCnt; i++)
    {
        free(s->curFiles[i]);
    }
    for(int i=0; i<s->childDirCnt; i++)
    {
        Search::clsOldSheets(s->childDir[i]);
    }

    free(s);
}
void Search::searchSheets(Search *res, Sheets *sub, bool flag)
{

    std::string file = "";  //候选文件
    std::string dir;  //当前查找路径
    int filesCnt;
    int dirsCnt;
    Sheets *curSheets = NULL;
    if(sub)
    {
        curSheets = sub;
        dir      = sub->curPath;
        filesCnt = sub->curFilesCnt;
        dirsCnt  = sub->childDirCnt;
    }
    if(flag)
    {
        curSheets = res->db;
        dir      = res->db->curPath;
        filesCnt = res->db->curFilesCnt;
        dirsCnt  = res->db->childDirCnt;;
    }

    if(!curSheets) return;

    // 文件
    for(int i=0; i < filesCnt; i++)
    {
        file = curSheets->curFiles[i];//候选文件

        if(file == res->what)
        {
            if(res->curCnt < res->maxCnt)
            {
                res->pathName[res->curCnt] = dir + "/" + file;
                res->curCnt++;
            }
            else
            {
                std::cerr << "Too much file matched ...\n";
            }
            break;//每个目录下的文件名是唯一的，找到后不再搜索
        }
    }

    // 子目录
    for(int i=0; i < dirsCnt; i++)
    {
        searchSheets(res, curSheets->childDir[i]);
    }

}

Content::Content(std::string pathFile)
{
    pf = pathFile;
}
void Content::show(void)
{
    Buffer buf;
    if(!readToBuffer(&buf))
    {
        std::cerr << "can read file: " << pf << std::endl;
        return;
    }
    /////////////////////////////////////////////
    //libwlc::Colorize bc(buf.line,buf.cnt);
    //for(int i=0; i<buf.cnt; i++)
    //{
    //    bc.showMessage(i);
    //}
    /////////////////////////////////////////////
    Colorize bc(buf.line,buf.cnt);
    bc.setDefaultColor();
    bc.colorizeMsg();
    for(int k = 0; k< buf.cnt; k++)
    {
        std::cout << buf.line[k];
    }
}
bool Content::readToBuffer(Buffer *buf)
{
    /* 按行读取文件
     * ifstream 在 C++11 之前仅接受 const char *类型参数
     * 在C++11 之后可以接受 std::string 等类型参数
     */

    char line[MAX_LINE_CHAR_NUM] = {0};
    int  lineNum = 0;
    {
        /*
         * 为什么用seekg重置后无效？
         * 暂时只能这样了！！！
         */
        std::ifstream fin(pf, std::ios::in);
        while(fin.getline(line, MAX_LINE_CHAR_NUM,'\n'))
        {
            lineNum++;//统计文件的行数
        }
        fin.clear();
        fin.close();
    }

    if(lineNum == 0)
    {
        return true;//空文件，直接返回
    }

    buf->cnt = lineNum;
    buf->line = new std::string[lineNum];

    int i = 0;
    std::ifstream fin(pf, std::ios::in);
    while(fin.getline(line, MAX_LINE_CHAR_NUM,'\n'))
    {
        buf->line[i] = line;
        i++;
    }
    fin.clear();
    fin.close();
    return true;
}

/*
    \e[0m   恢复默认
    \e[1m   黑体
    \e[2m   半亮
    \e[4m   下划线
    \e[24m  关闭下划线
    \e[25m  关闭闪烁

    \e[30m  黑色-前景
    \e[31m  红色-前景
    \e[32m  绿色-前景
    \e[33m  棕色-前景
    \e[34m  蓝色-前景
    \e[35m  紫色-前景
    \e[36m  品红-前景
    \e[37m  白色-前景

    \e[40m  黑色-背景
    \e[41m  红色-背景
    \e[42m  绿色-背景
    \e[43m  棕色-背景
    \e[44m  蓝色-背景
    \e[45m  紫色-背景
    \e[46m  品红-背景
    \e[47m  白色-背景
    \e[49m  默认-背景

    \e[31;47m   红色前景,白色背景
*/
colorAttribute::colorAttribute(void)
{
    cnt = 0;
    v = NULL;
    xcnt = 0;
}
colorAttribute::~colorAttribute(void)
{
    switch(cnt)
    {
        case 0:
        case 1:
            delete v;
            break;
        case 2:
        default:
            delete [] v;
    };
    #ifdef CMDA_DEBUG_STD_COUT
    std::cout << "delete colorAttribute\n";
    #endif
}
colorAttribute& colorAttribute::append(int i)
{
    if(!v || cnt == 0 || xcnt == cnt )
        return *this;
    v[xcnt] = i;
    xcnt++;
    return *this;
}
void colorAttribute::setCnt(int count)
{
    if(count < 0)
        return;
    cnt = count;
    v = new int[cnt];
}

Colorize::Colorize(std::string *message, int cnt)
{
    msg = message;
    msgCnt = cnt;

    index = NULL;
    indexcnt = 0;
}
Colorize::~Colorize(void)
{
    switch(indexcnt)
    {
        case 0:
        case 1:
            delete index;
            break;
        case 2:
        default:
            delete [] index;
    };
    #ifdef CMDA_DEBUG_STD_COUT
    std::cout << "delete Colorize\n";
    #endif
}
bool Colorize::setDefaultColor(void)
{
    indexcnt = 2;
    index = new colorAttribute[2];
    if(!index)
    {
        std::cout << "can't get memory\n";
        return false;
    }

    index[0].setCnt(1);
    index[1].setCnt(6);

    index[0].append(ATD);//默认显示
    index[1].append(FRed);//红色
    index[1].append(FGreen);//绿色
    index[1].append(FBrown);//棕色
    index[1].append(FBlue);//蓝色
    index[1].append(FMagenta);//紫色
    index[1].append(FCyan);//天蓝

    return true;
}
void Colorize::colorizeMsg(void)
{
    colorizeTipsAndCmd(index[0],index[1]);
}
void Colorize::delAllColor(void)
{}
void Colorize::colorizeTipsAndCmd(const colorAttribute &tips, const colorAttribute &cmd)
{
    if(!msg || msgCnt <= 0)
    {
        std::cout << " 空白文件\n";
        return;
    }
    if(!tips.v || tips.cnt <= 0 || !cmd.v || cmd.cnt <= 0)
    {
        std::cout << "自定义彩色计划无效";
        return;
    }

    int cmdcolor = 0;
    for(int i=0;i< msgCnt;i++)
    {
        if(msg[i].data()[0] == '#')
        {
            std::string attr = "\e[";
            int k = 0;
            while(k < tips.cnt)
            {
                std::stringstream tmp("");
                tmp << tips.v[k];
                attr.append(tmp.str());

                if(k == tips.cnt-1)
                {
                    attr.append(1,'m');
                    break;
                }
                else
                {
                    attr.append(1,';');
                }

                k++;
            }

            msg[i].insert(0,attr);
            msg[i].append("\e[0m\n");
        }
        else
        {
            std::string attr = "\e[";

            std::stringstream tmp("");
            tmp << cmd.v[cmdcolor%cmd.cnt];

            attr.append(tmp.str());
            attr.append("m  ");

            msg[i].insert(0,attr);
            msg[i].append("\e[0m\n");

            cmdcolor++;
        }
    }
}
