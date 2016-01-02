#include "linuxutility.h"
#include "colorize.h"
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

namespace libwlc
{
/////////////////////////////////////////////////
//数字字符 <=> 数字间 ( 0 ～ 9 和 a ～ f 和 A ～ F)
int  LinuxUtility::convertDigitCharacterToInteger(char dc)
{
    if     (dc == '0') return 0x0;
    else if(dc == '1') return 0x1;
    else if(dc == '2') return 0x2;
    else if(dc == '3') return 0x3;
    else if(dc == '4') return 0x4;
    else if(dc == '5') return 0x5;
    else if(dc == '6') return 0x6;
    else if(dc == '7') return 0x7;
    else if(dc == '8') return 0x8;
    else if(dc == '9') return 0x9;
    else if(dc == 'a' || dc == 'A') return 0xa;
    else if(dc == 'b' || dc == 'B') return 0xb;
    else if(dc == 'c' || dc == 'C') return 0xc;
    else if(dc == 'd' || dc == 'D') return 0xd;
    else if(dc == 'e' || dc == 'E') return 0xe;
    else if(dc == 'f' || dc == 'F') return 0xf;
    else return -1;
}
char LinuxUtility::convertIntegerToDigitCharacter(char i)
{
    if     (i == 0x0) return '0';
    else if(i == 0x1) return '1';
    else if(i == 0x2) return '2';
    else if(i == 0x3) return '3';
    else if(i == 0x4) return '4';
    else if(i == 0x5) return '5';
    else if(i == 0x6) return '6';
    else if(i == 0x7) return '7';
    else if(i == 0x8) return '8';
    else if(i == 0x9) return '9';
    else if(i == 0xa) return 'a';
    else if(i == 0xb) return 'b';
    else if(i == 0xc) return 'c';
    else if(i == 0xd) return 'd';
    else if(i == 0xe) return 'e';
    else if(i == 0xf) return 'f';
    else              return '?';
}
//目录相关操作
std::string LinuxUtility::getCurrentWorkingPath(void)
{
    char tmp[1024];
    memset(tmp,'\0',1024*sizeof(char));

    FILE *fp = popen("pwd","r");
    if(!fp)
    {
        std::string msg = "Crashed.";
        opps(msg);
    }

    char *i = fgets(tmp,1024*sizeof(char),fp);
    pclose(fp);

    if(!i)
    {
        std::string msg = "Crashed.";
        opps(msg);
    }

    i = tmp;
    while(*i != '\0') i++;
    i--;
    *i = '\0';
    return tmp;
}
std::string LinuxUtility::getAbsolutePath(const std::string &rpath)
{
    if(rpath.empty()) return "";

    char tmp[1024];
    memset(tmp,'\0',1024*sizeof(char));
    if(rpath[0] == '/') return rpath;
    else if(rpath.length()>=2 && rpath[0]=='.' && rpath[1]=='/')
    {
        std::string left = rpath.substr(1);
        std::string cmd = "pwd";
        FILE *fp = popen(cmd.c_str(),"r");
        if(!fp)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        char *i = fgets(tmp,1024*sizeof(char),fp);
        pclose(fp);
        if(!i)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        i = tmp;
        while(*i != '\0') i++;
        i--;
        *i = '\0';
        return tmp+left;
    }
    else if(rpath.length()>=3 && rpath[0]=='.' && rpath[1]=='.' && rpath[2]=='/')
    {
        std::string left = rpath.substr(2);
        std::string cmd = "cd ..;pwd";
        FILE *fp = popen(cmd.c_str(),"r");
        if(!fp)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        char *i = fgets(tmp,1024*sizeof(char),fp);
        pclose(fp);
        if(!i)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        i = tmp;
        while(*i != '\0') i++;
        i--;
        *i = '\0';
        return tmp+left;
    }
    else if(rpath.length()>=2 && rpath[0]=='~' && rpath[1]=='/')
    {
        std::string left = rpath.substr(1);
        std::string cmd = "cd ~;pwd";
        FILE *fp = popen(cmd.c_str(),"r");
        if(!fp)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        char *i = fgets(tmp,1024*sizeof(char),fp);
        pclose(fp);
        if(!i)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        i = tmp;
        while(*i != '\0') i++;
        i--;
        *i = '\0';
        return tmp+left;
    }
    else if(rpath.length()==2 && rpath[0]=='.' && rpath[1]=='.')
    {
        std::string cmd = "cd ..;pwd";
        FILE *fp = popen(cmd.c_str(),"r");
        if(!fp)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        char *i = fgets(tmp,1024*sizeof(char),fp);
        pclose(fp);
        if(!i)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        i = tmp;
        while(*i != '\0') i++;
        i--;
        *i = '\0';
        return tmp;
    }
    else if(rpath.length()==1 && rpath[0]=='.')
    {
        std::string cmd = "pwd";
        FILE *fp = popen(cmd.c_str(),"r");
        if(!fp)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        char *i = fgets(tmp,1024*sizeof(char),fp);
        pclose(fp);
        if(!i)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        i = tmp;
        while(*i != '\0') i++;
        i--;
        *i = '\0';
        return tmp;
    }
    else if(rpath.length()==1 && rpath[0]=='~')
    {
        std::string cmd = "cd ~;pwd";
        FILE *fp = popen(cmd.c_str(),"r");
        if(!fp)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        char *i = fgets(tmp,1024*sizeof(char),fp);
        pclose(fp);
        if(!i)
        {
            std::string msg = "Crashed.";
            opps(msg);
        }

        i = tmp;
        while(*i != '\0') i++;
        i--;
        *i = '\0';
        return tmp;
    }
    else
    {
        std::string msg = "[" + rpath + "] Not leagel path.";
        opps(msg);
    }
}
bool LinuxUtility::isDirectoryExist(const std::string &path)
{
    std::string apath = getAbsolutePath(path);
    if(apath.empty()) return false;
    if(opendir(apath.c_str()) == NULL) return false;
    return true;
}
bool LinuxUtility::creatDirtectory(const std::string &path, const std::string &name)
{
    if(name.empty()) return false;
    if(isDirectoryExist(path+"/"+name)) return true;
    std::string apath = getAbsolutePath(path);

    std::string tmp = "mkdir -p " + apath + "/" +name;
    if(!system(tmp.c_str()))
        return true;
    else
        return false;
}
bool LinuxUtility::deleteDirectory(const std::string &path)
{
    if(path.empty()) return false;
    std::string apath  = getAbsolutePath(path);
    if(apath.empty()) return false;

    apath = "rm -rf " + apath;
    if(!system(apath.c_str()))
        return true;
    else
        return false;
}
//文件相关操作
bool LinuxUtility::isFileExist(const std::string &path, const std::string &name)
{
    if(path.empty() || name.empty()) return false;
    std::string apathName = getAbsolutePath(path);
    apathName = apathName + "/" + name;
    if(!access(apathName.c_str(),F_OK) &&
       !access(apathName.c_str(),R_OK) )
        return true;
    else
        return false;
}
bool LinuxUtility::creatFile(const std::string &path, const std::string &name)
{
    if(path.empty() || name.empty()) return false;
    if(isFileExist(path, name)) return true;
    std::string apathName = getAbsolutePath(path);
    apathName = "touch " + apathName + "/" + name;

    if(!system(apathName.c_str()))
        return true;
    else
        return false;
}
bool LinuxUtility::deleteFile(const std::string &path, const std::string &name)
{
    if(path.empty() || name.empty()) return true;
    if(!isFileExist(path, name)) return true;
    std::string apathName = getAbsolutePath(path);
    apathName = "rm " + apathName + "/" + name;

    if(!system(apathName.c_str()))
        return true;
    else
        return false;
}
//杂七杂八
bool LinuxUtility::getDateTime(unsigned char *dt)
{
    // $ date "+20%y-%m-%d %H:%M:%S"
    time_t t = time(0);
    char tmp[20];
    strftime( tmp, sizeof(tmp), "%Y-%m-%d %X",localtime(&t));

    //tmp[0~3]，年(0,1)
    dt[0] = convertDigitCharacterToInteger(tmp[0]);
    dt[0] = dt[0]<<4;
    dt[0] = dt[0] | convertDigitCharacterToInteger(tmp[1]);
    dt[1] = convertDigitCharacterToInteger(tmp[2]);
    dt[1] = dt[1]<<4;
    dt[1] = dt[1] | convertDigitCharacterToInteger(tmp[3]);
    //tmp[5,6]，月(2)
    dt[2] = convertDigitCharacterToInteger(tmp[5]);
    dt[2] = dt[2]<<4;
    dt[2] = dt[2] | convertDigitCharacterToInteger(tmp[6]);
    //tmp[8,9]，日(3)
    dt[3] = convertDigitCharacterToInteger(tmp[8]);
    dt[3] = dt[3]<<4;
    dt[3] = dt[3] | convertDigitCharacterToInteger(tmp[9]);
    //tmp[11,12]，时(4)
    dt[4] = convertDigitCharacterToInteger(tmp[11]);
    dt[4] = dt[4]<<4;
    dt[4] = dt[4] | convertDigitCharacterToInteger(tmp[12]);
    //tmp[14,15]，分(5)
    dt[5] = convertDigitCharacterToInteger(tmp[14]);
    dt[5] = dt[5]<<4;
    dt[5] = dt[5] | convertDigitCharacterToInteger(tmp[15]);
    //tmp[17,18]，秒(6)
    dt[6] = convertDigitCharacterToInteger(tmp[17]);
    dt[6] = dt[6]<<4;
    dt[6] = dt[6] | convertDigitCharacterToInteger(tmp[18]);
    return true;
}
std::string LinuxUtility::getCurrentUserName(void)
{
    char buffer[50];
    memset(buffer,0,50*sizeof(char));

    FILE * fp = popen("whoami","r");
    char *i = fgets(buffer,50*sizeof(char),fp);
    pclose(fp);

    i = buffer;
    while(*i != '\0') i++;
    i--;
    *i = '\0';
    return buffer;
}
/////////////////////////////////////////////////
bool LinuxUtility::exec (const std::string &dir, const std::string &cmd, const std::string &arg,
                  std::string &info_out, std::string &info_err,
                  int  &cc,
                  bool shw, int red)
{   //dir  执行命令的目录，空时为当前目录
    //cmd  执行的命令名，例如：ls，mv，mkdir等
    //arg  命令接受参数

    //info_out  命令执行后标准输出的信息
    //info_err  命令执行后标准错误的信息

    //cc 命令执行后的返回码

    //shw 命令执行时是否在终端显示(默认true显示)，显示：目录-命令
    //red 命令执行时的重定向说明

    /////////////////////////////////////////////////////////
    // 重定向处理，关于命令执行时在屏幕显示的信息的管理
    std::string larg;
    if     (red == 3) larg = arg + " 1>/dev/null 2>/dev/null";
    else if(red == 2) larg = arg + " 2>/dev/null";
    else if(red == 1) larg = arg + " 1>/dev/null";
    else              larg = arg;
    /////////////////////////////////////////////////////////
    std::string abs_path = getAbsolutePath(dir);
    if(shw)
    {
        for(int i=0;i<81;i++) std::cout << "-";std::cout << std::endl;
        std::cout << "Directory  :";
        fgreen(abs_path);std::cout << std::endl;
        std::cout << "Execute    :";
        fgreen(cmd+" "+larg);std::cout << std::endl;
    }
    ////////////////////////////////////////////////////////
    //生成命令
    std::string lcmd;
        lcmd = "cd " + abs_path + ";" + cmd + " " + larg;
    ////////////////////////////////////////////////////////
    // 执行命令，检测命令执行状态
    if(!check(cmd,arg,system(lcmd.c_str()),cc)) return false;
    ////////////////////////////////////////////////////////
    return true;
}
bool LinuxUtility::check(const std::string &cmd, const std::string &arg,
                  const int status, int &err_cc )
{
    if(cmd.empty())
    {
        if(!status)
        {
            std::cerr << "libwlc.so/libwlc.a: LinuxUtility: Failed to boot ";
            std::cerr << "\e[31m/bin/sh\e[0m\n";
        }
        std::cerr << "libwlc.so/libwlc.a: LinuxUtility: Not given command to execute.\n";
        return false;
    }

    if( status == -1)
    {
        std::cerr << "libwlc.so/libwlc.a: LinuxUtility: Failed to execute command: ";
        std::cerr << "\e[31m" + cmd + " " + arg +"\e[0m\n";
        return false;
    }
    else
    {
        //用户主动，键盘组合按键终止
        if(WIFSIGNALED(status) &&
          (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT ||
           WTERMSIG(status) == SIGSTOP|| WTERMSIG(status) == SIGKILL))
        {
            /* 终端执行命令 [$ stty -a] 显示各种信号的键盘按键组合表示
             * SIGINT    : Ctrl + c，强制中断程序的执行，关闭
             * SIGSTOP   : Ctrl + z，暂停当前程序的执行，挂起
             * SIGQUIT   : Ctrl + \
             * SIGKILL   : Ctrl + u
             */
            std::cout << "Stop: ";
            std::cout << "\e[32m" + cmd + " " + arg +"\e[0m\n";
            return false;
        }

        //正常执行后，命令的退出状态
        if(!WIFEXITED(status))
        {
            std::cerr << "libwlc.so/libwlc.a: LinuxUtility: ";
            std::cerr << "\e[31m" + cmd + " " + arg +"\e[0m";
            std::cerr << " in innormal way.\n";
            return false;
        }
        else
        {
            int cmd_exit_code = WEXITSTATUS(status);//命令执行后，其返回值
            if(cmd_exit_code == 127)
            {
                std::cerr << "libwlc.so/libwlc.a: LinuxUtility: Failed to boot ";
                std::cerr << "\e[31m/bin/sh\e[0m\n";
                return false;
            }

            err_cc = cmd_exit_code;
        }
    }
    return true;
}
/////////////////////////////////////////////////
void LinuxUtility::opps(std::string &msg)
{
    std::cerr << "libwlc.so/libwlc.a: LinuxUtility: "+msg << " exit(1).\n";
    exit(1);
}
/////////////////////////////////////////////////
}
