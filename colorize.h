#ifndef CMDA_COLORIZE_H
#define CMDA_COLORIZE_H
/*色彩显示输出*/
#include <string>


enum displayColor
{
    ATD=0, Blod=1, HalfBright=2, Underscore=4,
    FBlack=30, FRed=31, FGreen=32, FBrown=33, FBlue=34, FMagenta=35, FCyan=36, FWhite=37,
    BBlack=40, BRed=41, BGreen=42, BBrown=43, BBlue=44, BMagenta=45, BCyan=46, BWhite=47
};

class Colorize
{
public:
    Colorize(std::string *message, int cnt, displayColor *uScheme=NULL, int uCnt=0);
    ~Colorize(void);

    void colorizeMsg(int begtip=0, int endtip=0, int begcmd=1, int endcmd=6);

    void delAllColor(void);
    bool colored;//彩色标志
private:
    std::string *msg;
    int msgCnt;

    displayColor *colorizeScheme;
    int colorCnt;
};

#endif
