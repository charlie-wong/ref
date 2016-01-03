#include <iostream>
#include "setting.h"
libwlc::Version ref_version(0,1,0,"Diego");

bool writeVersionInfoToFile(void)
{
    if(ref_version.writeToFile(ref_version_file_loc.c_str(),ref_version_file_name.c_str()))
        return true;
    else
        return false;
}
bool readVersionInfoFromFile(void)
{
    if(ref_version.readFromFile(ref_version_file_loc.c_str(),ref_version_file_name.c_str()))
        return true;
    else
        return false;
}
