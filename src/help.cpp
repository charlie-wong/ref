#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "help.h"
#include "core.h"
#include "setting.h"
extern char *optarg;  //当前带参数的选项的参数
extern int optind;    //处理当前选项索引值的下一个,初始化值默认是1; 重置为 1 ,再次扫描
extern int opterr;    //对不在optstring中的选项字符,给出警告; 设置成 0 ,阻止警告生成
extern int optopt;    //对不在optstring中的选项字符, 将其放在此变量中

extern int LanguagePriorityList[2];
extern int SearchLanguage;
extern int SearchAreaNum;
extern bool MutilMatchShowFileList;

bool version_file_exist_flag = true;
bool config_file_exist_flag  = true;

void showVersionInfo(void)
{
    if(version_file_exist_flag)
    {
        std::cout << libwlc::Version::getVersionInfo(ref_version) << std::endl;
    }
    else
    {
        std::cerr << "Maybe:\n"
                  << "\t1. missing file: '" << ref_version_file_loc+ref_version_file_name << "'\n"
                  << "\t2. can't read that file\n";
    }
}
void showUsage(void)
{
    std::cout
    << "Usage:\n"
    << "\t1. $ ref find      show example of find command.\n"
    << "\t2. $ ref 2 find    show example of find command, search only in area 2.\n"
    << "\t3. $ ref -L [en|zh|ez] find\n"
    << "\t                   show example of find command, search only in given language.\n"
    << "\t4. $ ref -v        show version.\n"
    << "\t5. $ ref -h        show this help.\n"
    << "\n"
    << "Tips: This program installed at: \n"
    << "\t                   " << ref_install_location << "\n"
    << "Tips: You can put youself file in subdirectories of: \n"
    << "\t                   " << ref_sheets_user_path << "\n"
    << "Tips: You config file locate at: \n"
    << "\t                   " << ref_user_config_file_path +"/"+ ref_user_config_file_name << "\n"
    << "Home-page: https://github.com/charlie-wong/ref\n";
    return;
}
int inKeyWordsList(const std::string keyWords)
{
    if(keyWords.empty()) return ref_config_key_works_cnt;
    int cnt = 0;
    while(cnt < ref_config_key_works_cnt)
    {
        if(keyWords == ref_config_key_works_list[cnt])
            return cnt;
        else
            cnt++;
    }
    return ref_config_key_works_cnt;
}
int getLanguageCode(const std::string languageName)
{
    // 0 ez 保持默认配置
    // 1 en 英
    // 2 zh 中
    int cnt = 0;
    while(cnt < ref_support_language_cnt)
    {
        if(languageName == ref_support_language_name[cnt])
            return cnt;
        else
            cnt++;
    }
    return ref_support_language_cnt;
}
void parseKeyWordsValue_0(const std::string valueList)
{
    if(valueList.empty()) return;

    size_t len = valueList.length();
    size_t cnt = 0;
    int index = 0;

    while(cnt < len)
    {
        char cc = valueList[cnt];
        if(cc==' ' || cc==',' || cc=='\t' ||
           cc==':' || cc==';')
        {
            cnt++;
        }
        else
        {
            size_t fcnt = cnt;
            size_t lcnt = cnt;
            while(lcnt < len)
            {
                cc = valueList[lcnt];
                if(cc==' ' || cc==',' || cc=='\t' ||
                   cc==':' || cc==';')
                    break;
                else
                    lcnt++;
            }
            std::string tmpv = valueList.substr(fcnt,lcnt-fcnt);

            int lc = getLanguageCode(tmpv);
            if(lc>0 && lc<ref_support_language_cnt)
            {
                LanguagePriorityList[index] = lc;
                index++;
                index = index%2;
            }

            cnt = lcnt;
        }
    }
}
void parseKeyWordsValue_1(const std::string valueList)
{
    if(valueList.empty()) return;

    size_t len = valueList.length();
    size_t cnt = 0;

    while(cnt < len)
    {
        char cc = valueList[cnt];
        if(cc==' ' || cc==',' || cc=='\t' ||
           cc==':' || cc==';')
        {
            cnt++;
        }
        else
        {
            size_t fcnt = cnt;
            size_t lcnt = cnt;
            while(lcnt < len)
            {
                cc = valueList[lcnt];
                if(cc==' ' || cc==',' || cc=='\t' ||
                   cc==':' || cc==';')
                    break;
                else
                    lcnt++;
            }
            std::string tmpv = valueList.substr(fcnt,lcnt-fcnt);

            int lc = getLanguageCode(tmpv);
            if(lc>=0 && lc<ref_support_language_cnt)
            {
                SearchLanguage = lc;
            }
            cnt = lcnt;
        }
    }
}
void parseKeyWordsValue_2(const std::string valueList)
{
    if(valueList.empty()) return;

    size_t len = valueList.length();
    size_t cnt = 0;

    while(cnt < len)
    {
        char cc = valueList[cnt];
        if(cc==' ' || cc==',' || cc=='\t' ||
           cc==':' || cc==';')
        {
            cnt++;
        }
        else
        {
            size_t fcnt = cnt;
            size_t lcnt = cnt;
            while(lcnt < len)
            {
                cc = valueList[lcnt];
                if(cc==' ' || cc==',' || cc=='\t' ||
                   cc==':' || cc==';')
                    break;
                else
                    lcnt++;
            }
            std::string tmpv = valueList.substr(fcnt,lcnt-fcnt);
            if(tmpv.length() == 1)
            {
                char ch[2] = { tmpv[0], 0,};
                SearchAreaNum = atoi(ch);
            }
            cnt = lcnt;
        }
    }
}
void parseKeyWordsValue_3(const std::string valueList)
{
    if(valueList.empty()) return;

    size_t len = valueList.length();
    size_t cnt = 0;

    std::string str_false = "false";
    std::string str_true = "true";

    while(cnt < len)
    {
        char cc = valueList[cnt];
        if(cc==' ' || cc==',' || cc=='\t' ||
           cc==':' || cc==';')
        {
            cnt++;
        }
        else
        {
            size_t fcnt = cnt;
            size_t lcnt = cnt;
            while(lcnt < len)
            {
                cc = valueList[lcnt];
                if(cc==' ' || cc==',' || cc=='\t' ||
                   cc==':' || cc==';')
                    break;
                else
                    lcnt++;
            }
            std::string tmpv = valueList.substr(fcnt,lcnt-fcnt);

            if(tmpv == str_true)  MutilMatchShowFileList = true;
            if(tmpv == str_false) MutilMatchShowFileList = false;
            cnt = lcnt;
        }
    }
}
void loadConfigFile(void)
{
    std::string pn = ref_user_config_file_path + "/" + ref_user_config_file_name;
    FILE *fp = fopen(pn.c_str(), "r");
    if(fp == NULL)
    {
        std::cerr << "can't open config file: " << pn << std::endl;
        return;
    }

    char buffer[2048];
    while (!feof(fp))
    {
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, sizeof(buffer), fp);  //读取一行
        char leading = buffer[0];
        if(leading == '#' || leading == '\n' || leading == '\t' || leading == '\0')
            continue;

        char *fnwc = buffer;//关键字首个有效字符
        while(*fnwc != '\n')
        {
            if(*fnwc == ' ' || *fnwc == '\t' || *fnwc == '#') fnwc++;
            else break;
        }
        if(*fnwc == '\n') continue;

        char *fcmc = fnwc;//首个冒号分割符号
        while(*fcmc != '\n')
        {
            if(*fcmc == ':') break;
            fcmc++;
        }
        if(*fcmc == '\n')
        {
            *fcmc = '\0';
            std::cerr << "Invalid config line: '"
                      << buffer << "'\n";
            continue;
        }

        *fcmc = '\0';
        std::string keyWords = fnwc;
        int keyWordsCode = inKeyWordsList(keyWords);

        fcmc++;
        fnwc = fcmc;
        while(*fnwc != '\n')
        {
            fnwc++;
        }
        *fnwc = '\0';
        std::string valueList = fcmc;
        switch(keyWordsCode)
        {
        case 0:
        {
            parseKeyWordsValue_0(valueList);
            break;
        }
        case 1:
        {
            parseKeyWordsValue_1(valueList);
            break;
        }
        case 2:
        {
            parseKeyWordsValue_2(valueList);
            break;
        }
        case 3:
        {
            parseKeyWordsValue_3(valueList);
            break;
        }
        default:
        {
            std::cout << "Invalid key words: '" << keyWords << "'\n";
            break;
        }
        }
    }

    fclose(fp);
    return;
}
void init(void)
{
    if(!libwlc::LinuxUtility::isFileExist(ref_version_file_loc, ref_version_file_name))
    {
        std::cerr << "missing file: '"
                  << ref_version_file_loc+ref_version_file_name << "'\n";
        version_file_exist_flag = false;
    }
    if(version_file_exist_flag && !readVersionInfoFromFile())
    {
        std::cerr << "can't load version info" << std::endl;
    }

    if(libwlc::LinuxUtility::isFileExist(ref_user_config_file_path, ref_user_config_file_name))
    {
        loadConfigFile();
    }
}

void argParse(int argc, char **argv)
{
    /* 字符后跟一个冒号,表示该选项必须提供一个参数
     * 字符后跟两个冒号,表示该选项接受可选参数
     * optstring以冒号开始时:
     *       则后面要求有选项参数的选项字符，当在argv中该选项字符没有参数,
     *       调用getopt函数族处理该选项参数时返回冒号,optopt存放的是该选项字符
     */
    const char *optstring=":hHvVL:y::";
    const struct option longopts[]=
    {
        {"help",no_argument,0,'h'},
        {"help",no_argument,0,'H'},
        {"version",no_argument,0,'v'},
        {"version",no_argument,0,'V'},
        {"language",required_argument,0,'L'},
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
        switch(optc)
        {
            case 'h':
            case 'H':
            {
                showUsage();
                break;
            }
            case 'v':
            case 'V':
            {
                showVersionInfo();
                break;
            }
            case 'L':
            {
                std::string tmp = optarg;
                if(tmp == "en")
                {
                    SearchLanguage = 1;
                }
                else if(tmp == "zh")
                {
                    SearchLanguage = 2;
                }
                else
                {
                    std::cout << "Invalid language argument: " << optarg << std::endl;
                    std::cout << "Use default value\n";
                    std::cout << "'$ ref -h', for detail information.\n";
                }
                break;
            }
            case 'y':
            {
                std::cout << "yarg:" << optarg << std::endl;
                break;
            }
            case ':':
            {
                std::cout << "'" << (char)optopt << "' need a argument.\n";
                break;
            }
            case '?':
            {
                std::cout << "Invalid argument: '" << (char)optopt << "'\n";
                std::cout << "'ref -h', for detail information.\n";
                break;
            }
        };
    }

    getSearchCandidates(argc, argv);
}
