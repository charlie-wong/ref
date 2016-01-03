#include <iostream>
#include "help.h"
int LanguagePriorityList[2] = {2, 1}; // 语言搜索优先级，可用配置文件覆盖默认设置
                                      // 指定搜索语言时此优先级列表失效，仅对搜索全部语言有效
                                      // 默认先中文，后英文，原因自行考虑...
                                      // LanguagePriorityList[0] 优先
                                      // LanguagePriorityList[1] 其次
int SearchLanguage = 0;     // 搜索哪种语言：0 全部， 1 英语， 2 中文
                            // 0 默认值，1 => -L en，2 => -L zh
int SearchAreaNum  = 0;     // 搜索哪个区域：0 全部，1～9 对应 man 手册
                            // 0 默认值， $ ref 2 find ...
int SearchAreaList[10];     // 指定搜索区域
                            // [0] => 值为 1 时表示设定默认搜索区域；0 未设定，不使用
                            // [1] ~ [9] 用于存储有效搜索区域
int SearchAreaMax  = 9;     // 总共 9 个区域，对应 man 手册
bool MutilMatchShowFileList = true;    // 当有多个匹配文件时，默认匹配文件列表

int main(int argc, char **argv)
{
    init();
    argParse(argc, argv);

    return 0;
}

