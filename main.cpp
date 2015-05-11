#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "debug.h"
#include "sheets.h"
#include "colorize.h"

using namespace std;
extern char *optarg;//当前带参数的选项的参数
extern int optind;//处理当前选项索引值的下一个,初始化值默认是1; 重置为 1 ,再次扫描
extern int opterr;//对不在optstring中的选项字符,给出警告; 设置成 0 ,阻止警告生成
extern int optopt;//对不在optstring中的选项字符, 将其放在此变量中

int MaxMatchNum = 9;//一次搜索最多可以匹配的文件个数（man分9部分，so...)，可调用 -m/--maxnum 9 自定义
int MaxDisplayNum = 1;//当有多个搜索匹配成功时，要显示的文件的个数，将其默认设置为展示1个文件
std::string userSysName;
int userSearchLanguage = 0;
std::string CMDA_sheets_path_usr_en_abs;
std::string CMDA_sheets_path_usr_zh_abs;

int main(int argc, char **argv)
{
    const char *optstring=":hHvVm:d:L:x:y::";
    /* 字符后跟一个冒号,表示该选项必须提供一个参数
     * 字符后跟两个冒号,表示该选项接受可选参数
     * optstring以冒号开始时:
     *       则后面要求有选项参数的选项字符，当在argv中该选项字符没有参数,
     *       调用getopt函数族处理该选项参数时返回冒号,optopt存放的是该选项字符
     */
    const struct option longopts[]=
    {
        {"help",no_argument,0,'h'},
        {"help",no_argument,0,'H'},
        {"version",no_argument,0,'v'},
        {"version",no_argument,0,'V'},
        {"maxnum",required_argument,0,'m'},
        {"displaymaxnum",required_argument,0,'d'},
        {"language",required_argument,0,'L'},
        {"xarg",required_argument,0,'x'},
        {"yarg",optional_argument,0,'y'},
        {0,0,0,0},
    };
    char optc;
    int longindex = -1;

    /* getopt_long,getopt,getopt_long_only 当检索完所有选项时返回 -1
     * 如果一个选项不接受参数, 则该选项后出现的参数字符串则会出现的顺序依次'追加(位置调整)'到
     * argv的有效解析的参数之后
     */
    while((optc = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1)
    {
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "---optc = " << optc << std::endl;
        std::cout << "---longindex = " << longindex << std::endl;
        std::cout << "---cur-index = " << optind-1 << std::endl;
        std::cout << "---next-index = " << optind << std::endl;
        #endif
        switch(optc)
        {
            case 'h':
            case 'H':
            {//30~36
                std::cout << "How to use me:\n";
                std::cout << "\e[32m\t1、cmda find\t";
                std::cout << "\e[0mGet the 'find' command quick examples\n\n";

                std::cout << "\e[31mcmda -L [en|zh|ez]\n";
                std::cout << "\e[31mcmda --language=[en|zh|ez]";
                std::cout << "\e[0m\t(zh) search for chinese result, (en) search for english result\n";

                std::cout << "\e[36mcmda -m 9\n";
                std::cout << "\e[36mcmda --maxnum=9";
                std::cout << "\e[0m\tThe Max matches num for a search(default is 9)\n";

                std::cout << "\e[33mcmda -d 1\n";
                std::cout << "\e[33mcmda --displaymaxnum=1";
                std::cout << "\e[0m\tThe Max Display matched file num for a search(default is 1, should be [1-9])\n";

                std::cout << "\e[35mcmda -v\n";
                std::cout << "\e[56mcmda --version";
                std::cout << "\e[0m\tVersion\n";

                std::cout << "\e[34mcmda -h\n";
                std::cout << "\e[34mcmda --help";
                std::cout << "\e[0m\tUsage information\n\n";

                std::cout << "全局表单位置(中)：\e[33m\t" << CMDA_sheets_path_sys_zh << std::endl << "\e[0m";
                std::cout << "全局表单位置(英)：\e[32m\t" << CMDA_sheets_path_sys_en << std::endl << "\e[0m";
                std::cout << "用户表单位置：\e[31m\t\t~/" << CMDA_sheets_path_usr << std::endl << "\e[0m";
                std::cout << "软件安装位置：\e[30m\t\t" << CMDA_install_location << std::endl << "\e[0m";
                return 0;
            }
            case 'v':
            case 'V':
            {
                std::cout << CMDA_version;
                std::cout << "Home-page: \e[32mhttps://github.com/charlie-wong/cmda\e[0m\n";
                std::cout << "Rport-bugs: \e[32m1213charlie@gmail.com\e[0m\n";
                break;
            }
            case 'm':
            {
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "-------" << MaxMatchNum << std::endl;
                #endif
                std::string tmp_str(optarg);
                std::stringstream tmp_ss(tmp_str);
                tmp_ss >> MaxMatchNum;
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "-----" << optarg << std::endl;
                std::cout << "-------" << MaxMatchNum << std::endl;
                #endif
                break;
            }
            case 'L':
            {
                std::string tmp =optarg;
                if(tmp == "en")
                {
                    userSearchLanguage = 0;
                }
                else if(tmp == "zh")
                {
                    userSearchLanguage = 1;
                }
                else if(tmp == "ez")
                {
                    userSearchLanguage = 2;
                }
                else
                {
                    std::cout << "无效语言标志--> " << optarg << std::endl;
                    std::cout << "Use default Value(English) \n";
                    std::cout << "For detail information, tpye cmd 'cmda -h'\n";
                }
                break;
            }
            case 'd':
            {
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "-------" << MaxDisplayNum << std::endl;
                #endif
                std::string tmp_str(optarg);
                std::stringstream tmp_ss(tmp_str);
                tmp_ss >> MaxDisplayNum;
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "-----" << optarg << std::endl;
                std::cout << "-------" << MaxDisplayNum << std::endl;
                #endif
                if(MaxDisplayNum > 9)
                {
                    std::cout << "-------" << MaxDisplayNum << std::endl;
                    std::cout << "-d 的有效取值参数是：[1,9]\n";
                }
                break;
            }
            case 'x':
            {
                std::cout << "xarg:" << optarg << std::endl;
                break;
            }
            case 'y':
            {
                std::cout << "yarg:" << optarg << std::endl;
                break;
            }
            case ':':
            {
                std::cout << (char)optopt << " 选项需要一个参数\n";
                return 0;
            }
            case '?':
            {
                std::cout << "无效选项字符 '" << (char)optopt << "'\n";
                std::cout << "Type 'cmda -h' for help\n";
                return 0;
            }
        };
    }

    //加载前资源检查
    init();
    {
    #ifdef CMDA_DEBUG_STD_COUT
    std::cout << "系统英文@：" << CMDA_sheets_path_sys_en << std::endl;//系统英文sheets
    std::cout << "系统中文@：" << CMDA_sheets_path_sys_zh << std::endl;//系统中文sheets
    std::cout << "用户英文@：" << CMDA_sheets_path_usr_en_abs << std::endl;//用户英文sheets
    std::cout << "用户中文@：" << CMDA_sheets_path_usr_zh_abs << std::endl;//用户中文sheets
    #endif
    }
    //搜索前准备工作
    SearchResult result(MaxMatchNum);//搜索结果

    //处理用户给出的非参数选项
    if(optind != argc)
    {
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "待搜索的命令:\n";
        std::cout << argv[optind];
        for(int i = optind+1;i < argc;i++)
            std::cout << ", " << argv[i];
        std::cout << std::endl;
        #endif

        //搜索筛选
        std::string what;
        for(int i = optind;i < argc; i++)
        {
            what = argv[i];
            if(userSearchLanguage == 0)
            {//英文
                int matchNum = 0;
                int showedfilenum = 0;//以显示文件个数

                //系统en目录查找
                sheets *sys_en = readFileList(CMDA_sheets_path_sys_en.data());
                SearchScheme plan_sys_en;//sys_en搜索筛选计划
                plan_sys_en.setLanguage(userSearchLanguage);
                plan_sys_en.setSheets(sys_en);
                matchNum = plan_sys_en.find(&result, what);//查找指定命令文件
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "总共匹配的文件个数" << matchNum << std::endl;
                std::cout << "匹配的文件列表：\n";
                #endif
                if(matchNum > MaxDisplayNum)
                {
                    matchNum = MaxDisplayNum;
                }
                for(int i =0;i<matchNum;i++)
                {
                    #ifdef CMDA_DEBUG_STD_COUT
                    std::cout << "计数器@sys_en i = " << i << std::endl;
                    std::cout << "sys_en已显示文件个数：" << showedfilenum+1 << std::endl;
                    #endif

                    if(showedfilenum >= matchNum)
                    {
                        break;
                    }
                    SheetsBuf buf;
                    std::cout << "@[" << result.pathfile[i] << "] \n";
                    showContent(result.pathfile[i],&buf);

                    Colorize c(buf.line,buf.cnt);
                    c.setDefaultColor();
                    c.colorizeMsg();

                    if(!buf.line)
                    {
                        //此文件空白，处理下一个匹配文件
                        showedfilenum++;
                        continue;
                    }
                    for(int k = 0;k< buf.cnt;k++)
                    {
                        std::cout << buf.line[k];
                    }
                    showedfilenum++;
                }
                free(sys_en);

                //用户en目录查找
                sheets *usr_en = readFileList(CMDA_sheets_path_usr_en_abs.data());
                SearchScheme plan_usr_en;//usr_en搜索筛选计划
                plan_usr_en.setLanguage(userSearchLanguage);
                plan_usr_en.setSheets(usr_en);
                matchNum = plan_usr_en.find(&result, what);//查找指定命令文件
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "总共匹配的文件个数" << matchNum << std::endl;
                std::cout << "匹配的文件列表：\n";
                #endif
                if(matchNum > MaxDisplayNum)
                {
                    matchNum = MaxDisplayNum;
                }
                for(int i =0;i<matchNum;i++)
                {
                    #ifdef CMDA_DEBUG_STD_COUT
                    std::cout << "计数器@usr_en i = " << i << std::endl;
                    std::cout << "usr_en已显示文件个数：" << showedfilenum << std::endl;
                    #endif

                    if(showedfilenum >= matchNum)
                    {
                        break;
                    }
                    SheetsBuf buf;
                    std::cout << "@[" << result.pathfile[i] << "] \n";
                    showContent(result.pathfile[i],&buf);

                    Colorize c(buf.line,buf.cnt);
                    c.setDefaultColor();
                    c.colorizeMsg();

                    if(buf.cnt == 0 || !buf.line)
                    {
                        //此文件空白，处理下一个匹配文件
                        showedfilenum++;
                        continue;
                    }
                    for(int k = 0;k< buf.cnt;k++)
                    {
                        std::cout << buf.line[k];
                    }
                    showedfilenum++;
                }
                free(usr_en);
            }
            else if(userSearchLanguage == 1)
            {//中文
                int matchNum = 0;
                int showedfilenum = 0;//以显示文件个数

                //系统zh目录查找
                sheets *sys_zh = readFileList(CMDA_sheets_path_sys_zh.data());
                SearchScheme plan_sys_zh;//sys_zh搜索筛选计划
                plan_sys_zh.setLanguage(userSearchLanguage);
                plan_sys_zh.setSheets(sys_zh);
                matchNum = plan_sys_zh.find(&result, what);//查找指定命令文件
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "总共匹配的文件个数" << matchNum << std::endl;
                std::cout << "匹配的文件列表：\n";
                #endif
                if(matchNum > MaxDisplayNum)
                {
                    matchNum = MaxDisplayNum;
                }
                for(int i =0;i<matchNum;i++)
                {
                    #ifdef CMDA_DEBUG_STD_COUT
                    std::cout << "计数器@sys_en i = " << i << std::endl;
                    std::cout << "sys_en已显示文件个数：" << showedfilenum+1 << std::endl;
                    #endif

                    if(showedfilenum >= matchNum)
                    {
                        break;
                    }
                    SheetsBuf buf;
                    std::cout << "@[" << result.pathfile[i] << "] \n";
                    showContent(result.pathfile[i],&buf);

                    Colorize c(buf.line,buf.cnt);
                    c.setDefaultColor();
                    c.colorizeMsg();

                    if(!buf.line)
                    {
                        //此文件空白，处理下一个匹配文件
                        showedfilenum++;
                        continue;
                    }
                    for(int k = 0;k< buf.cnt;k++)
                    {
                        std::cout << buf.line[k];
                    }
                    showedfilenum++;
                }
                free(sys_zh);

                //用户zh目录查找
                sheets *usr_zh = readFileList(CMDA_sheets_path_usr_zh_abs.data());
                SearchScheme plan_usr_zh;//usr_zh搜索筛选计划
                plan_usr_zh.setLanguage(userSearchLanguage);
                plan_usr_zh.setSheets(usr_zh);
                matchNum = plan_usr_zh.find(&result, what);//查找指定命令文件
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "总共匹配的文件个数" << matchNum << std::endl;
                std::cout << "匹配的文件列表：\n";
                #endif
                if(matchNum > MaxDisplayNum)
                {
                    matchNum = MaxDisplayNum;
                }
                for(int i =0;i<matchNum;i++)
                {
                    #ifdef CMDA_DEBUG_STD_COUT
                    std::cout << "计数器@usr_en i = " << i << std::endl;
                    std::cout << "usr_en已显示文件个数：" << showedfilenum << std::endl;
                    #endif

                    if(showedfilenum >= matchNum)
                    {
                        break;
                    }
                    SheetsBuf buf;
                    std::cout << "@[" << result.pathfile[i] << "] \n";
                    showContent(result.pathfile[i],&buf);

                    Colorize c(buf.line,buf.cnt);
                    c.setDefaultColor();
                    c.colorizeMsg();

                    if(buf.cnt == 0 || !buf.line)
                    {
                        //此文件空白，处理下一个匹配文件
                        showedfilenum++;
                        continue;
                    }
                    for(int k = 0;k< buf.cnt;k++)
                    {
                        std::cout << buf.line[k];
                    }
                    showedfilenum++;
                }
                free(usr_zh);
            }
            else if(userSearchLanguage == 2)
            {//中英
                int matchNum = 0;
                int showedfilenum = 0;//以显示文件个数

                //系统en目录查找
                sheets *sys_en = readFileList(CMDA_sheets_path_sys_en.data());
                SearchScheme plan_sys_en;//sys_en搜索筛选计划
                plan_sys_en.setLanguage(userSearchLanguage);
                plan_sys_en.setSheets(sys_en);
                matchNum = plan_sys_en.find(&result, what);//查找指定命令文件
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "总共匹配的文件个数" << matchNum << std::endl;
                std::cout << "匹配的文件列表：\n";
                #endif
                if(matchNum > MaxDisplayNum)
                {
                    matchNum = MaxDisplayNum;
                }
                for(int i =0;i<matchNum;i++)
                {
                    #ifdef CMDA_DEBUG_STD_COUT
                    std::cout << "计数器@sys_en i = " << i << std::endl;
                    std::cout << "sys_en已显示文件个数：" << showedfilenum+1 << std::endl;
                    #endif

                    if(showedfilenum >= matchNum)
                    {
                        break;
                    }
                    SheetsBuf buf;
                    std::cout << "@[" << result.pathfile[i] << "] \n";
                    showContent(result.pathfile[i],&buf);

                    Colorize c(buf.line,buf.cnt);
                    c.setDefaultColor();
                    c.colorizeMsg();

                    if(!buf.line)
                    {
                        //此文件空白，处理下一个匹配文件
                        showedfilenum++;
                        continue;
                    }
                    for(int k = 0;k< buf.cnt;k++)
                    {
                        std::cout << buf.line[k];
                    }
                    showedfilenum++;
                }
                free(sys_en);

                //用户en目录查找
                sheets *usr_en = readFileList(CMDA_sheets_path_usr_en_abs.data());
                SearchScheme plan_usr_en;//usr_en搜索筛选计划
                plan_usr_en.setLanguage(userSearchLanguage);
                plan_usr_en.setSheets(usr_en);
                matchNum = plan_usr_en.find(&result, what);//查找指定命令文件
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "总共匹配的文件个数" << matchNum << std::endl;
                std::cout << "匹配的文件列表：\n";
                #endif
                if(matchNum > MaxDisplayNum)
                {
                    matchNum = MaxDisplayNum;
                }
                for(int i =0;i<matchNum;i++)
                {
                    #ifdef CMDA_DEBUG_STD_COUT
                    std::cout << "计数器@usr_en i = " << i << std::endl;
                    std::cout << "usr_en已显示文件个数：" << showedfilenum << std::endl;
                    #endif

                    if(showedfilenum >= matchNum)
                    {
                        break;
                    }
                    SheetsBuf buf;
                    std::cout << "@[" << result.pathfile[i] << "] \n";
                    showContent(result.pathfile[i],&buf);

                    Colorize c(buf.line,buf.cnt);
                    c.setDefaultColor();
                    c.colorizeMsg();

                    if(buf.cnt == 0 || !buf.line)
                    {
                        //此文件空白，处理下一个匹配文件
                        showedfilenum++;
                        continue;
                    }
                    for(int k = 0;k< buf.cnt;k++)
                    {
                        std::cout << buf.line[k];
                    }
                    showedfilenum++;
                }
                free(usr_en);

                //系统zh目录查找
                sheets *sys_zh = readFileList(CMDA_sheets_path_sys_zh.data());
                SearchScheme plan_sys_zh;//sys_zh搜索筛选计划
                plan_sys_zh.setLanguage(userSearchLanguage);
                plan_sys_zh.setSheets(sys_zh);
                matchNum = plan_sys_zh.find(&result, what);//查找指定命令文件
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "总共匹配的文件个数" << matchNum << std::endl;
                std::cout << "匹配的文件列表：\n";
                #endif
                if(matchNum > MaxDisplayNum)
                {
                    matchNum = MaxDisplayNum;
                }
                for(int i =0;i<matchNum;i++)
                {
                    #ifdef CMDA_DEBUG_STD_COUT
                    std::cout << "计数器@sys_en i = " << i << std::endl;
                    std::cout << "sys_en已显示文件个数：" << showedfilenum+1 << std::endl;
                    #endif

                    if(showedfilenum >= matchNum)
                    {
                        break;
                    }
                    SheetsBuf buf;
                    std::cout << "@[" << result.pathfile[i] << "] \n";
                    showContent(result.pathfile[i],&buf);

                    Colorize c(buf.line,buf.cnt);
                    c.setDefaultColor();
                    c.colorizeMsg();

                    if(!buf.line)
                    {
                        //此文件空白，处理下一个匹配文件
                        showedfilenum++;
                        continue;
                    }
                    for(int k = 0;k< buf.cnt;k++)
                    {
                        std::cout << buf.line[k];
                    }
                    showedfilenum++;
                }
                free(sys_zh);

                //用户zh目录查找
                sheets *usr_zh = readFileList(CMDA_sheets_path_usr_zh_abs.data());
                SearchScheme plan_usr_zh;//usr_zh搜索筛选计划
                plan_usr_zh.setLanguage(userSearchLanguage);
                plan_usr_zh.setSheets(usr_zh);
                matchNum = plan_usr_zh.find(&result, what);//查找指定命令文件
                #ifdef CMDA_DEBUG_STD_COUT
                std::cout << "总共匹配的文件个数" << matchNum << std::endl;
                std::cout << "匹配的文件列表：\n";
                #endif
                if(matchNum > MaxDisplayNum)
                {
                    matchNum = MaxDisplayNum;
                }
                for(int i =0;i<matchNum;i++)
                {
                    #ifdef CMDA_DEBUG_STD_COUT
                    std::cout << "计数器@usr_en i = " << i << std::endl;
                    std::cout << "usr_en已显示文件个数：" << showedfilenum << std::endl;
                    #endif

                    if(showedfilenum >= matchNum)
                    {
                        break;
                    }
                    SheetsBuf buf;
                    std::cout << "@[" << result.pathfile[i] << "] \n";
                    showContent(result.pathfile[i],&buf);

                    Colorize c(buf.line,buf.cnt);
                    c.setDefaultColor();
                    c.colorizeMsg();

                    if(buf.cnt == 0 || !buf.line)
                    {
                        //此文件空白，处理下一个匹配文件
                        showedfilenum++;
                        continue;
                    }
                    for(int k = 0;k< buf.cnt;k++)
                    {
                        std::cout << buf.line[k];
                    }
                    showedfilenum++;
                }
                free(usr_zh);
            }
            else
            {}
        }

    }

    /* 测试
    string *test = new string[16];
    test[0] = "# 测试";
    test[1] = "apt-get";
    test[2] = "# 测试-2";
    test[3] = "apt-get-2";
    test[4] = "# 测试";
    test[5] = "apt-get";
    test[6] = "# 测试-2";
    test[7] = "apt-get-2";
    test[8] = "# 测试";
    test[9] = "apt-get";
    test[10] = "# 测试-2";
    test[11] = "apt-get-2";
    test[12] = "# 测试";
    test[13] = "apt-get";
    test[14] = "# 测试-2";
    test[15] = "apt-get-2";

    Colorize a(test,16);
    a.setDefaultColor();
    a.colorizeMsg();

    cout << test[0];
    cout << test[1];
    cout << test[2];
    cout << test[3];
    cout << test[4];
    cout << test[5];
    cout << test[6];
    cout << test[7];
    cout << test[8];
    cout << test[9];
    cout << test[10];
    cout << test[11];
    cout << test[12];
    cout << test[13];
    cout << test[14];
    cout << test[15];
    delete [] test;
    */

    return 0;
}

