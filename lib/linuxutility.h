#ifndef LIB_WLC_LINUXUTILITY_H
#define LIB_WLC_LINUXUTILITY_H
#include <iostream>
namespace libwlc
{
/////////////////////////////////////////////////
class LinuxUtility
{
public:
    //数字字符 <=> 数字间 ( 0 ～ 9 和 a ～ f 和 A ～ F)
    static int  convertDigitCharacterToInteger(char dc);
    static char convertIntegerToDigitCharacter(char i);
    //目录相关操作
    static std::string getCurrentWorkingPath(void);
    static std::string getAbsolutePath(const std::string &rpath);
    static bool isDirectoryExist(const std::string &path);
    static bool creatDirtectory(const std::string &path, const std::string &name);
    static bool deleteDirectory(const std::string &path);
    //文件相关操作
    static bool isFileExist(const std::string &path, const std::string &name);
    static bool creatFile(const std::string &path, const std::string &name);
    static bool deleteFile(const std::string &path, const std::string &name);
    //杂七杂八
    static bool getDateTime(unsigned char *dt);
    static std::string getCurrentUserName(void);
    static void wlc(void);
private:
    static void opps(std::string &msg);
    ////////////////////////////////////////////////
public:
    //dir  执行命令的目录，空时为当前目录
    //cmd  执行的命令名，例如：ls，mv，mkdir等
    //arg  命令接受参数

    //info_out  命令执行后标准输出的信息
    //info_err  命令执行后标准错误的信息

    //cc 命令执行后的返回码

    //shw 命令执行时是否在终端显示(默认true显示)，显示：目录-命令
    //red 命令执行时的重定向说明(默认值0)
    static bool exec (const std::string &dir, const std::string &cmd, const std::string &arg,
                      std::string &info_out, std::string &info_err,
                      int &cc,
                      bool shw=true, int red=0);
private:
    static bool check(const std::string &cmd, const std::string &arg,
                      const int status, int &err_cc );
};
/////////////////////////////////////////////////
}
#endif // LIB_WLC_LINUXUTILITY_H
