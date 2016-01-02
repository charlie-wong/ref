#ifndef LIB_WLC_COLORIZE_H
#define LIB_WLC_COLORIZE_H
#include <string>
#include "debug.h"
/*色彩显示输出*/
namespace libwlc
{
///////////////////////////////////////////////////////////
inline std::string fred(std::string s)
{
    return ("\e[31m"+s+"\e[0m");
}
inline std::string fgreen(std::string s)
{
    return ("\e[32m"+s+"\e[0m");
}
inline std::string fbrown(std::string s)
{
    return ("\e[33m"+s+"\e[0m");
}
inline std::string fblue(std::string s)
{
    return ("\e[34m"+s+"\e[0m");
}
inline std::string fmagenta(std::string s)
{
    return ("\e[35m"+s+"\e[0m");
}
///////////////////////////////////////////////////////////
enum ColorCode
{
    ATD=0, Blod=1, HalfBright=2, Underscore=4,
    FBlack=30, FRed=31, FGreen=32, FBrown=33, FBlue=34, FMagenta=35, FCyan=36, FWhite=37,
    BBlack=40, BRed=41, BGreen=42, BBrown=43, BBlue=44, BMagenta=45, BCyan=46, BWhite=47
};
class ColorAttribute
{
public:
     ColorAttribute(void);
     ColorAttribute(int max);
    ~ColorAttribute(void);

    ColorAttribute&	addToColorList(ColorCode cc);
    ColorAttribute&	delFromColorList(ColorCode cc);
    void listColorList(void) const;
    void setFlag(bool v);
    

    ColorCode *color_list;	//列表
    int  color_list_num;	//当前个数
    int  color_list_max_num;//最大个数
    
    bool flag;	//有效标志
};
class Colorize
{
public:
    Colorize(void);
    Colorize(const std::string &msg);
    Colorize(const std::string *msg, int cnt);
    Colorize(const char *msg);
    Colorize(const char **msg, int cnt);
    ~Colorize(void);

    void listColorizeSchedule(void);
    void cleanColorizeSchedule(void);

    bool addColor(ColorCode cc);
    bool delColor(ColorCode cc);

    void showMessage(int index) const;
    void showMessage(void) const;

private:
    bool setDefaultColorizeSchedule(void);

private:
    ColorAttribute *color_attr;

    const std::string *s_msg;// C++ 标准串
    int s_msg_cnt;
    const char **c_msg;// C 风格串
    int c_msg_cnt;
};
class Color
{
/* str	原始字符串
** b	true(开头有回车)，false(开头无回车)
** e	true(结尾有回车)，false(结尾无回车)
**/
public:
    static void     fred(const std::string &str, bool b=false, bool e=false);	//31，红色
    static void   fgreen(const std::string &str, bool b=false, bool e=false);	//32，绿色
    static void   fbrown(const std::string &str, bool b=false, bool e=false);	//33，褐色
    static void    fblue(const std::string &str, bool b=false, bool e=false);	//34，蓝色
    static void fmagenta(const std::string &str, bool b=false, bool e=false);    //35，品红
    static void    fcyan(const std::string &str, bool b=false, bool e=false);	//36，蓝绿

    static void     bred(const std::string &str, bool b=false, bool e=false);	//41
    static void   bgreen(const std::string &str, bool b=false, bool e=false);	//42
    static void   bbrown(const std::string &str, bool b=false, bool e=false);	//43
    static void    bblue(const std::string &str, bool b=false, bool e=false);	//44
    static void bmagenta(const std::string &str, bool b=false, bool e=false);   //45
    static void    bcyan(const std::string &str, bool b=false, bool e=false);	//46
private:
    static void setColor(ColorCode cc, const std::string &str, std::string &tmp, bool b, bool e);
};
///////////////////////////////////////////////////////////
}
#endif
