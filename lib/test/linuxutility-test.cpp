#include <iostream>
#include "../linuxutility.h"
using namespace std;

int main()
{
    cout << "digit<-char " << libwlc::LinuxUtility::convertDigitCharacterToInteger('f') << endl;
    cout << "digit->char " << libwlc::LinuxUtility::convertIntegerToDigitCharacter(13) << endl;
    cout << "CurrentPath " << libwlc::LinuxUtility::getCurrentWorkingPath() << endl;
    cout << "ABSpath     " << libwlc::LinuxUtility::getAbsolutePath("~/project") << endl;
    cout << "DirExist    " << libwlc::LinuxUtility::isDirectoryExist("./x") << endl;
    cout << "CreatDir    " << libwlc::LinuxUtility::creatDirtectory(".","wlc") << endl;
    cout << "DeleteDir   " << libwlc::LinuxUtility::deleteDirectory("./x") << endl;
    cout << "FileExist   " << libwlc::LinuxUtility::isFileExist(".", "qt") << endl;
    cout << "CreateFile  " << libwlc::LinuxUtility::creatFile(".", "wxy") << endl;
    cout << "DeleteFile  " << libwlc::LinuxUtility::deleteFile(".", "abc") << endl;
    unsigned char dt[7];
    cout << "GetSysTime  " << libwlc::LinuxUtility::getDateTime(dt) << endl;
    cout << "UserName    " << libwlc::LinuxUtility::getCurrentUserName() << endl;
    for(int i=0;i<7;i++)
    {
        cout << hex << (int)dt[i];
        if(i==1) cout << '/';
        else if(i==2) cout << '/';
        else if(i==3) cout << ' ';
        else if(i==4) cout << ':';
        else if(i==5) cout << ':';
    }
    cout << endl;
    return 0;
}

