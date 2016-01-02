#include <string>
#include <iostream>

extern char *optarg;  //当前带参数的选项的参数
extern int optind;    //处理当前选项索引值的下一个,初始化值默认是1; 重置为 1 ,再次扫描
extern int opterr;    //对不在optstring中的选项字符,给出警告; 设置成 0 ,阻止警告生成
extern int optopt;    //对不在optstring中的选项字符, 将其放在此变量中

extern int LanguagePriorityList[2];
extern int SearchLanguage;
extern int SearchAreaNum;
extern bool MutilMatchShowFileList;

void searchEngine(const std::string &what)
{
    std::cout << "search for: [" << what << "]\n";
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
