#include <iostream>
#include "setting.h"
#ifdef DEBUG
 #include "debug.h"
#endif
libwlc::Version ref_version(0,0,1,"Diego");
using namespace std;

int main(int argc, char **argv)
{
#ifdef WRITE_VERSION_TO_FILE
    ref_version.writeToFile("./","version");
#endif
    if(ref_version.readFromFile("./","version"))
        cout << "read ok\n";

    cout << ref_version.getVersionInfo(ref_version) << endl;
    return 0;
}

