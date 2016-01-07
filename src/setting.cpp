#include <iostream>
#include "setting.h"
libwlc::Version ref_version(0,0,4,"Diego");

bool writeVersionInfoToFile(std::string loc, std::string name)
{
    if(ref_version.writeToFile(loc.c_str(),name.c_str()))
        return true;
    else
        return false;
}

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
