#include "colorize.h"
#include "debug.h"
#include <sstream>
#include <iostream>

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
    switch(msgCnt)
    {
        case 0:
        case 1:
            delete msg;
            break;
        case 2:
        default:
            delete [] msg;
    };

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

    index[0].append(ATD);
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
        std::cout << "待处理消息为空\n";
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
