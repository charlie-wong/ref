#ifndef SETTING_H
#define SETTING_H
#include <string>
#include "../lib/libwlc.h"
extern libwlc::Version ref_version;

const std::string ref_install_location = "/opt/ref/";
const std::string ref_sheets_root_path = "/opt/ref/sheets/";
const std::string user_name = libwlc::LinuxUtility::getCurrentUserName();
const std::string ref_sheets_user_path = "/home/" + user_name + "/.config/ref/";

//单个目录拥有的最大文件数目（不包括递归子目录中的文件和目录数据）
const int CMDA_SDFMaxNum = 500;
//单个目录拥有的最大子目录数据（不包括递归子目录中的目录）
const int CMDA_SDCDMaxNum = 50;
//绝对路径/基路径 的最大长度（最大字符个数）,包含'\0'
const int CMDA_APMaxChNum = 1001;
//当个文件名最大的字符个数（包括扩展名等），包含'\0'
const int CMDA_FNMaxChNum = 301;
//sheets文件中每行字符的最大个数
const int CMDA_MaxLineChNum = 2048;

#endif // SETTING_H

