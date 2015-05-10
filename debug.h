#ifndef CMDA_DEBUG_H
#define CMDA_DEBUG_H
#include <string>

#define CMDA_DEBUG_STD_COUT

#ifdef __cplusplus
#define C_LANGUAGE_BEGIN extern "C" {
#define C_LANGUAGE_END  }
#else
#define C_LANGUAGE_BEGIN
#define C_LANGUAGE_END
#endif//__cplusplus

const std::string CMDA_version = "cmda version 0.01 (Ubuntu14.04 g++4.8.2)\n";
const std::string CMDA_sheets_path_sys_en = "/opt/cmda/sheets/en/";
const std::string CMDA_sheets_path_sys_zh = "/opt/cmda/sheets/zh/";

const std::string CMDA_sheets_path_usr = ".cmda/sheets/";
const std::string CMDA_sheets_path_usr_en = ".cmda/sheets/en/";
const std::string CMDA_sheets_path_usr_zh = ".cmda/sheets/zh/";

const std::string CMDA_install_location = "/opt/cmda/";

//单个目录拥有的最大文件数目（不包括递归子目录中的文件和目录数据）
const int CMDA_SDFMaxNum = 500;
//单个目录拥有的最大子目录数据（不包括递归子目录中的目录）
const int CMDA_SDCDMaxNum = 50;
//绝对路径/基路径 的最大长度（最大字符个数）,包含'\0'
const int CMDA_APMaxChNum = 1001;
//当个文件名最大的字符个数（包括扩展名等），包含'\0'
const int CMDA_FNMaxChNum = 251;
#endif
