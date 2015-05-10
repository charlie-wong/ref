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
class colorAttribute
{
public:
    colorAttribute(void);
    ~colorAttribute(void);

    colorAttribute& append(int i);
    void setCnt(int count);

    int *v;
    int cnt;//int值总个数
    int xcnt;//待填充索引
};

class Colorize
{
public:
    Colorize(std::string *message, int cnt);
    ~Colorize(void);

    bool setDefaultColor(void);

    void colorizeMsg(void);
    void delAllColor(void);
private:
    /* index[0] Tips
     * index[1] Cmd
     */
    colorAttribute *index;
    int  indexcnt;

    std::string *msg;
    int msgCnt;

    void colorizeTipsAndCmd(const colorAttribute &tips, const colorAttribute &cmd);
};

#endif
