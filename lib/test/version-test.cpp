#include <iostream>
#include "../version.h"
#include "../linuxutility.h"
using namespace std;

int main(int argc, char **argv)
{
    char wlc[] = "nick name";
    libwlc::Version x(1,2,3,wlc);
    cout << x.getVersionInfo(x) << endl;
    x.setMaj(0);
    x.setMin(0);
    x.setPat(1);
    cout << x.getVersionInfo(x) << endl;
    x.setCCMaj(1);
    x.setCCMin(2);
    x.setCCPat(3);
    cout << x.getVersionInfo(x) << endl;
    x.setHosID(2);
    cout << x.getVersionInfo(x) << endl;
    return 0;
}
