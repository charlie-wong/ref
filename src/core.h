#ifndef CORE_H
#define CORE_H
#include <string>
//一次搜索匹配最多可同时匹配的最大文件数目
const int MAX_MATCH_FILE_NUM = 100;
//单个目录拥有的最大文件数目（不包括递归子目录中的文件和目录数据）
const int DIR_MAX_FILE_ENTRY_NUM = 1024;
//单个目录拥有的最大子目录数目（不包括递归子目录中的目录）
const int DIR_MAX_DIRE_ENTRY_NUM = 100;
//单个文件名有效字符个数，包含'\0'
const int MAX_VALID_FILE_NAME_CHAR = 256;
//绝对路径的最大有效字符个数，包含'\0'
const int MAX_VALID_CHAR_NUM_FORAP = 1024;

struct Sheets
{
    char     *curPath;// 目录绝对路径，动态内存

    char     *curFiles[DIR_MAX_FILE_ENTRY_NUM];// 某目录下所有的文件名，动态分配
    int       curFilesCnt;

    Sheets   *childDir[DIR_MAX_DIRE_ENTRY_NUM];//动态分配
    int       childDirCnt;// 当前目录下子目录个数（除 . 和 .. 外)
};
class Search
{
public:
    explicit Search(const std::string &nwhat);
    ~Search(void);
    bool find(Sheets *xdb);
    void showMatchFiles(void);
    std::string getMatchFile(void);

    std::string what;
    Sheets      *db;
    std::string *pathName;
    int          maxCnt;
    int          curCnt;

private:
    static int  index;
    static void clsOldSheets(Sheets *s);
    static void searchSheets(Search *res, Sheets *sub=NULL, bool flag=false);
};
class SearchBasePath
{
public:
    SearchBasePath(void)
    {
        cnt = 0;
    }
    void clear(void)
    {
        int i = 0;
        while(i < cnt)
        {
            bp[i] = "";
            i++;
        }
        cnt = 0;
    }
    std::string bp[36];
    int         cnt;
};
class Content
{
public:
    Content(std::string pathFile);

    void show(void);
private:
    std::string pf;

    class Buffer
    {
    public:
        Buffer(void)
        {
            line = NULL;
            cnt = 0;
        }
        ~Buffer(void)
        {
            switch(cnt)
            {
                //case 0:
                //case 1:
                //    {
                //        delete line;
                //        break;
                //    }
                case 2:
                default:
                    {
                        delete [] line;
                        break;
                    }
            };
        }
        std::string *line;
        int           cnt;
    };
    bool readToBuffer(Buffer *buf);
};
Sheets* getSheets(const char *basePath);// 递归读取指定目录下的内容
void getSearchCandidates(int argc, char **argv);

enum displayColor
{
    ATD=0, Blod=1, HalfBright=2, Underscore=4,
    FBlack=30, FRed=31, FGreen=32, FBrown=33, FBlue=34, FMagenta=35, FCyan=36, FWhite=37,
    BBlack=40, BRed=41, BGreen=42, BBrown=43, BBlue=44, BMagenta=45, BCyan=46, BWhite=47
};
class colorAttribute
{
public:
    colorAttribute(void);
    ~colorAttribute(void);

    colorAttribute& append(int i);
    void setCnt(int count);

    int *v;
    int cnt;//int值总个数
    int xcnt;//待填充索引
};

class Colorize
{
public:
    Colorize(std::string *message, int cnt);
    ~Colorize(void);

    bool setDefaultColor(void);

    void colorizeMsg(void);
    void delAllColor(void);
private:
    /* index[0] Tips
     * index[1] Cmd
     */
    colorAttribute *index;
    int  indexcnt;

    std::string *msg;
    int msgCnt;

    void colorizeTipsAndCmd(const colorAttribute &tips, const colorAttribute &cmd);
};
#endif // CORE_H

