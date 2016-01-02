#include "colorize.h"
#include "value.h"
#include <sstream>
#include <iostream>
#include <stdio.h>

namespace libwlc
{
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
using namespace std;
///////////////////////////////////////////////////////////
ColorAttribute::ColorAttribute(void)
{
    color_list_num = 0;
    color_list_max_num = 0;
    color_list = NULL;
    flag = false;
}
ColorAttribute::ColorAttribute(int max)
{
    color_list_num = 0;
    color_list_max_num = max;
    color_list = new ColorCode[max];
    for(int i=0; i<max; i++)
        color_list[i] = ATD;
    flag = true;
}
ColorAttribute::~ColorAttribute(void)
{
    if(flag)
    {
        switch(color_list_max_num)
        {
            case 0:
            case 1:
                delete color_list;
                break;
            case 2:
            default:
                delete [] color_list;
        };
    }
}
ColorAttribute& ColorAttribute::addToColorList(ColorCode cc)
{
    if(!flag || !color_list || color_list_max_num == 0)
    {
            return *this;
    }
    if(color_list_max_num == color_list_num)
    {
        ColorCode *tmp = new ColorCode[color_list_max_num*2];
        for(int i=0; i<color_list_max_num; i++)
            tmp[i] = color_list[i];
        for(int i=color_list_max_num; i<color_list_max_num*2; i++)
            tmp[i] = ATD;

        delete [] color_list;

        color_list = tmp;
        color_list_max_num = color_list_max_num*2;
    }
    color_list[color_list_num] = cc;
    color_list_num++;
    return *this;
}
ColorAttribute& ColorAttribute::delFromColorList(ColorCode cc)
{
    if(!flag || !color_list || color_list_max_num == 0 || color_list_num == 0 )
        return *this;
    int  i_index;
    bool i_flag = false;
    for(int k=0; k<color_list_num; k++)
    {
        if(!i_flag && color_list[k] == cc)
        {
            i_flag = true;
            i_index = k;
        }
        else
        {
            color_list[i_index] = color_list[k];
            i_index = k;
        }
    }

    if(i_flag)
    {
        color_list_num--;
    }

    return *this;
}
void ColorAttribute::listColorList(void) const
{
    if(!flag || !color_list || color_list_max_num == 0 || color_list_num == 0 )
        return;

    for(int k=0; k<color_list_num; k++)
    {
        ColorCode tmp = color_list[k];
        switch(tmp)
        {
        case ATD:
                cout << "[" << ATD << "]\t" << "恢复默认\n";
                break;
        case Blod:
                cout  << "[" << Blod << "]\t" << "黑体\n";
                break;
        case HalfBright:
                cout << "[" << HalfBright << "]\t" << "半亮\n";
                break;
        case Underscore:
                cout << "[" << Underscore << "]\t" << "下划线\n";
                break;
        //case 24:
        //        cout << "关闭下划线\n";
        //        break;
        //case 25:
        //        cout << "关闭闪烁\n";
        //        break;
        case FBlack:
                cout << "[" << FBlack << "]\t" << "黑色-前景\n";
                break;
        case FRed:
                cout << "[" << FRed << "]\t" << "红色-前景\n";
                break;
        case FGreen:
                cout << "[" << FGreen << "]\t" << "绿色-前景\n";
                break;
        case FBrown:
                cout << "[" << FBrown << "]\t" << "棕色-前景\n";
                break;
        case FBlue:
                cout << "[" << FBlue << "]\t" << "蓝色-前景\n";
                break;
        case FMagenta:
                cout << "[" << FMagenta << "]\t" << "紫色-前景\n";
                break;
        case FCyan:
                cout << "[" << FCyan << "]\t" << "品红-前景\n";
                break;
        case FWhite:
                cout << "[" << FWhite << "]\t" << "白色-前景\n";
                break;
        case BBlack:
                cout << "[" << BBlack << "]\t" << "黑色-背景\n";
                break;
        case BRed:
                cout << "[" << BRed << "]\t" << "红色-背景\n";
                break;
        case BGreen:
                cout << "[" << BGreen << "]\t" << "绿色-背景\n";
                break;
        case BBrown:
                cout << "[" << BBrown << "]\t" << "棕色-背景\n";
                break;
        case BBlue:
                cout << "[" << BBlue << "]\t" << "蓝色-背景\n";
                break;
        case BMagenta:
                cout << "[" << BMagenta << "]\t" << "紫色-背景\n";
                break;
        case BCyan:
                cout << "[" << BCyan << "]\t" << "品红-背景\n";
                break;
        case BWhite:
                cout << "[" << BWhite << "]\t" << "白色-背景\n";
                break;
        //case 49:
        //        cout << "默认-背景\n";
        //        break;
        default:
                cout << "未知颜色代码\n";
                break;
        };
    }
}
void ColorAttribute::setFlag(bool v)
{
    flag = v;
}
///////////////////////////////////////////////////////////
Colorize::Colorize(void)
{
    s_msg = NULL;// C++ 标准串
    c_msg = NULL;// C 风格串
    c_msg_cnt = 0;
    s_msg_cnt = 0;
    setDefaultColorizeSchedule();// 设置成默认着色方案
}
Colorize::Colorize(const std::string &msg)
{
    s_msg     = &msg;
    s_msg_cnt = 1;
    c_msg     = NULL;
    c_msg_cnt = 0;
    setDefaultColorizeSchedule();// 设置成默认着色方案
}
Colorize::Colorize(const std::string *msg, int cnt)
{
    s_msg     = msg;
    s_msg_cnt = cnt;
    c_msg     = NULL;
    c_msg_cnt = 0;
    setDefaultColorizeSchedule();// 设置成默认着色方案
}
Colorize::Colorize(const char *msg)
{
    s_msg     = NULL;
    s_msg_cnt = 0;
    c_msg     = &msg;
    c_msg_cnt = 1;
    setDefaultColorizeSchedule();// 设置成默认着色方案
}
Colorize::Colorize(const char **msg, int cnt)
{
    s_msg     = NULL;
    s_msg_cnt = 0;
    c_msg     = msg;
    c_msg_cnt = cnt;
    setDefaultColorizeSchedule();// 设置成默认着色方案
}
Colorize::~Colorize(void)
{
    delete color_attr;
}
bool Colorize::setDefaultColorizeSchedule(void)
{
    color_attr = new ColorAttribute(6);
    if(!color_attr)
    {
        std::cout << "[libwlc]-[colorize] => can't get memory & exit.\n";
        return false;
    }

    //color_attr->addToColorList(ATD);//默认显示
    color_attr->addToColorList(FRed);//红色
    color_attr->addToColorList(FGreen);//绿色
    color_attr->addToColorList(FBrown);//棕色
    color_attr->addToColorList(FBlue);//蓝色
    color_attr->addToColorList(FMagenta);//紫色
    color_attr->addToColorList(FCyan);//天蓝
    return true;
}

void Colorize::listColorizeSchedule(void)
{
    color_attr->listColorList();
}
void Colorize::cleanColorizeSchedule(void)
{
    delete color_attr;
    color_attr = new ColorAttribute(10);
}
bool Colorize::addColor(ColorCode cc)
{
    color_attr->addToColorList(cc);
    return true;
}
bool Colorize::delColor(ColorCode cc)
{
    color_attr->delFromColorList(cc);
    return true;
}
void Colorize::showMessage(int index) const
{
    std::string cur_msg;
    if((!s_msg || s_msg_cnt == 0) && (!c_msg || c_msg_cnt == 0))
    {
        return;
    }
    else if(s_msg_cnt)
    {
        if(index < s_msg_cnt)
            cur_msg = s_msg[index];
        else
            return;
    }
    else if(c_msg_cnt)
    {
        if(index < c_msg_cnt)
            cur_msg = c_msg[index];
        else
            return;
    }

    int cur_color_index = index%(color_attr->color_list_num);
    int cur_color_code_num = color_attr->color_list[cur_color_index];
    char cur_color_code_str[10];
    sprintf(cur_color_code_str,"%d",cur_color_code_num);
    cout << "\e[" << cur_color_code_str << "m" << cur_msg << "\e[0m" << endl;
    return;
}
void Colorize::showMessage(void) const
{
    std::string cur_msg;
    if((!s_msg || s_msg_cnt == 0) && (!c_msg || c_msg_cnt == 0))
    {
        return;
    }
    int s_cnt = 0;
    int c_cnt = 0;
    while(s_cnt<s_msg_cnt || c_cnt<c_msg_cnt)
    {
        int x_cnt = -1;
        if(s_cnt < s_msg_cnt)
        {
            cur_msg = s_msg[s_cnt];
            x_cnt = s_cnt;
            s_cnt++;
        }
        else
        {
            cur_msg = c_msg[c_cnt];
            x_cnt = c_cnt;
            c_cnt++;
        }

        int cur_color_index = x_cnt%(color_attr->color_list_num);
        int cur_color_code_num = color_attr->color_list[cur_color_index];
        char cur_color_code_str[10];
        sprintf(cur_color_code_str,"%d",cur_color_code_num);
        cout << "\e[" << cur_color_code_str << "m" << cur_msg << "\e[0m" << endl;
    }
    return;
}
///////////////////////////////////////////////////////////
void Color::setColor(ColorCode cc, const std::string &str, std::string &tmp, bool b, bool e)
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    if(b)
    {
        tmp = "\n" + Value(cc).asString();
        tmp = tmp + str;
        if(e) tmp = tmp + "\e[0m\n";
        else  tmp = tmp + "\e[0m";
    }
    else
    {
        tmp = Value(cc).asString();
        tmp = tmp + str;
        if(e) tmp = tmp + "\e[0m\n";
        else  tmp = tmp + "\e[0m";
    }
}
void Color::fred(const std::string &str, bool b, bool e)		//31
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(FRed,str,tmp,b,e);
    std::cout << tmp;
}
void Color::fgreen(const std::string &str, bool b, bool e)	//32
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(FGreen,str,tmp,b,e);
    std::cout << tmp;
}
void Color::fbrown(const std::string &str, bool b, bool e)	//33
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(FBrown,str,tmp,b,e);
    std::cout << tmp;
}
void Color::fblue(const std::string &str, bool b, bool e)	//34
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(FBlue,str,tmp,b,e);
    std::cout << tmp;
}
void Color::fmagenta(const std::string &str, bool b, bool e)	//35
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(FMagenta,str,tmp,b,e);
    std::cout << tmp;
}
void Color::fcyan(const std::string &str, bool b, bool e)	//36
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(FCyan,str,tmp,b,e);
    std::cout << tmp;
}
void Color::bred(const std::string &str, bool b, bool e)		//41
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(BRed,str,tmp,b,e);
    std::cout << tmp;
}
void Color::bgreen(const std::string &str, bool b, bool e)	//42
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(BGreen,str,tmp,b,e);
    std::cout << tmp;
}
void Color::bbrown(const std::string &str, bool b, bool e)	//43
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(BBrown,str,tmp,b,e);
    std::cout << tmp;
}
void Color::bblue(const std::string &str, bool b, bool e)	//44
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(BBlue,str,tmp,b,e);
    std::cout << tmp;
}
void Color::bmagenta(const std::string &str, bool b, bool e)	//45
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(BMagenta,str,tmp,b,e);
    std::cout << tmp;
}
void Color::bcyan(const std::string &str, bool b, bool e)	//46
{
    // b=1时，前面有换行符号，否则前面没有换行
    // e=1时，行尾有换行符号，否则行尾没有换行
    std::string tmp;
    Color::setColor(BCyan,str,tmp,b,e);
    std::cout << tmp;
}
///////////////////////////////////////////////////////////
}
