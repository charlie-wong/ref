#include <iostream>
#include <typeinfo>
#include "../colorize.h"
using namespace std;

int main()
{
    std::string aa="abc";
    libwlc::Colorize y(aa);
    y.showMessage(0);
    y.listColorizeSchedule();
    cout << "-----------------------\n";
    /////////////////////////////////////
    std::string bb[8];
    bb[0] = "good1";
    bb[1] = "good2";
    bb[2] = "good3";
    bb[3] = "good4";
    bb[4] = "good5";
    bb[5] = "good6";
    bb[6] = "good7";
    bb[7] = "good8";
    libwlc::Colorize z(bb,8);
    z.showMessage(1);
    cout << "--------\n";
    z.showMessage();
    z.listColorizeSchedule();
    cout << "--------\n";
    z.delColor(libwlc::FRed);
    z.showMessage();
    z.listColorizeSchedule();
    cout << "--------\n";
    z.addColor(libwlc::FRed);
    z.showMessage();
    z.listColorizeSchedule();
    cout << "-----------------------\n";
    char cc[] = "good";
    libwlc::Colorize yy(cc);
    yy.showMessage(0);
    yy.listColorizeSchedule();
    cout << "-----------------------\n";
    const char *ss[4];
    char cs_1[] = "abc";
    char cs_2[] = "def";
    char cs_3[] = "hig";
    char cs_4[] = "klm";
    ss[0] = cs_1;
    ss[1] = cs_2;
    ss[2] = cs_3;
    ss[3] = cs_4;
    libwlc::Colorize zz(ss,4);
    zz.showMessage(2);
    zz.showMessage();
    /////////////////////////////////////
    cout << "-----------------------\n";
    std::string yyy = "yyyyyyyy";
    std::cout << libwlc::fred(yyy) << std::endl;
    std::cout << libwlc::fgreen(yyy) << std::endl;
    std::cout << libwlc::fbrown(yyy) << std::endl;
    std::cout << libwlc::fblue(yyy) << std::endl;
    std::cout << libwlc::fmagenta(yyy) << std::endl;
    /////////////////////////////////////
    cout << "-----------------------\n";
    cout << "ADT=" << typeid(libwlc::FRed).name() << endl;
    /////////////////////////////////////
    cout << "-----------------------\n";
    std::cout << "Before";
    libwlc::Color::fgreen("Green",true,true);
    std::cout << "End";
    return 0;
}
