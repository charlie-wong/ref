#include "colorize.h"
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

Colorize::Colorize(std::string *message, int cnt, displayColor *uScheme, int uCnt)
{
    colored = false;

    msg = message;
    msgCnt = cnt;

    if(uScheme && !uCnt)
    {
        colorizeScheme = uScheme;
        colorCnt = uCnt;
    }
    else
    {
        colorizeScheme = new displayColor[7];
        colorCnt = 7;

        colorizeScheme[0] = ATD;

        colorizeScheme[1] = FRed;//红色
        colorizeScheme[2] = FGreen;//绿色
        colorizeScheme[3] = FBrown;//棕色
        colorizeScheme[4] = FBlue;//蓝色
        colorizeScheme[5] = FMagenta;//紫色
        colorizeScheme[6] = FCyan;//天蓝
    }
}
Colorize::~Colorize(void)
{
    delete [] msg;
    delete [] colorizeScheme;
    std::cout << "delete";
}
void Colorize::colorizeMsg(int begtip, int endtip, int begcmd, int endcmd)
{
    if(!msg || msgCnt <= 0)
    {
        std::cout << "待处理消息为空\n";
        return;
    }
    if(begtip < 0 && endtip >= colorCnt && begcmd < 0 && endcmd >= colorCnt)
    {
        std::cout << "自定义彩色计划无效";
        return;
    }

    for(int i=0;i< msgCnt;i++)
    {
        int cmdcolor = begcmd;
        if(msg[i].data()[0] == '#')
        {
            std::string attr = "\e[";
            while(begtip <= endtip)
            {
                std::stringstream tmp("");
                tmp << colorizeScheme[begtip];
                attr.append(tmp.str());

                if(begtip == endtip)
                {
                    attr.append(1,'m');
                    break;
                }
                else
                {
                    attr.append(1,';');
                }

                begtip++;
            }

            msg[i].insert(0,attr);
            msg[i].append("\e[0m\n");
        }
        else
        {
            std::string attr = "\e[";

            std::stringstream tmp("");
            tmp << colorizeScheme[cmdcolor%6 + 1];

            attr.append(tmp.str());
            attr.append("m  ");

            msg[i].insert(0,attr);
            msg[i].append("\e[0m\n");

            begcmd++;
        }
    }

    colored = true;
}

void Colorize::delAllColor(void)
{}
