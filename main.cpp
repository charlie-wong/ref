#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include "debug.h"
#include "init.h"
#include "colorize.h"

using namespace std;
extern char *optarg;//当前带参数的选项的参数
extern int optind;//处理当前选项索引值的下一个,初始化值默认是1; 重置为 1 ,再次扫描
extern int opterr = 0;//对不在optstring中的选项字符,给出警告; 设置成 0 ,阻止警告生成
extern int optopt;//对不在optstring中的选项字符, 将其放在此变量中

int main(int argc, char **argv)
{
    const char *optstring=":hHvVx:y::";
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
        {"xarg",required_argument,0,'x'},
        {"yarg",optional_argument,0,'y'},
        {0,0,0,0},
    };
    char optc;
    int longindex = -1;

    /* getopt_long,getopt,getopt_long_only 当检索完所有选项时返回 -1
     */
    while((optc = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1)
    {
        #ifdef CMDA_DEBUG_STD_COUT
        std::cout << "---optc = " << optc << std::endl;
        std::cout << "---longindex = " << longindex << std::endl;
        std::cout << "---cur-index = " << optind-1 << std::endl;
        std::cout << "---next-index = " << optind << std::endl;
        #endif
        if(optc == -1)
        {

            return 0;
        }
        switch(optc)
        {
            case 'h':
            case 'H':
                std::cout << "\e[33mcmda -v\n\e[34mcmda --version\e[0m\tVersion\n";
                std::cout << "\e[31mcmda -h\n\e[32mcmda --help\e[0m\tUsage information\n";
                break;
            case 'v':
            case 'V':
                std::cout << CMDA_version;
                break;
            case 'x':
                std::cout << "xarg:" << optarg << std::endl;
                break;
            case 'y':
                std::cout << "yarg:" << optarg << std::endl;
                break;
            case ':':
                std::cout << (char)optopt << " 选项需要一个参数\n";
                return 0;
            case '?':
                std::cout << "无效选项字符 '" << (char)optopt << "'\n";
                return 0;
        };
    }
    /* 如果一个选项不接受参数, 则该选项后出现的参数字符串则会出现的顺序依次'追加(位置调整)'到argv的有效解析的参数之后
     */
    if(optind != argc)
    {
        std::cout << "该选项不接受参数,这些参数是:\n";
        std::cout << argv[optind];
        for(int i = optind+1;i < argc;i++)
            std::cout << ", " << argv[i];
        std::cout << std::endl;
    }



/*
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
*/
    return 0;
}

