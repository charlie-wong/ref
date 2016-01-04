#ifndef SETTING_H
#define SETTING_H
#include <string>
#include "../lib/libwlc.h"
extern libwlc::Version ref_version;

const std::string ref_language_dir_en = "en";
const std::string ref_language_dir_zh = "zh";
const std::string ref_install_location = "/opt/ref";
const std::string ref_version_file_loc = "/opt/ref/bin/";
const std::string ref_version_file_name= "version";
const std::string ref_sheets_root_path = "/opt/ref/sheets";
const std::string user_name = libwlc::LinuxUtility::getCurrentUserName();
const std::string ref_sheets_user_path = "/home/" + user_name + "/.config/ref/sheets";
const std::string ref_user_home_dir_path    = "/home/" + user_name + "/.config";
const std::string ref_user_home_dir_name    = "ref";
const std::string ref_user_config_file_path = "/home/" + user_name + "/.config/ref";
const std::string ref_user_config_file_name = "config";
const int         ref_config_key_works_cnt = 5;
const std::string ref_config_key_works_list[] =
{
    "LanguagePriorityList",
    "SearchLanguage",
    "SearchAreaNum",
    "MutilMatchShowFileList",
    "SearchAreaNumList",
};
const int         ref_support_language_cnt    = 3;
const std::string ref_support_language_name[] =
{
    "ez",
    "en",
    "zh",
};
bool writeVersionInfoToFile(std::string loc, std::string name);
bool writeVersionInfoToFile(void);
bool readVersionInfoFromFile(void);
#endif // SETTING_H

