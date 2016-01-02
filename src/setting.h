#ifndef SETTING_H
#define SETTING_H
#include <string>
#include "../lib/libwlc.h"
extern libwlc::Version ref_version;

const std::string ref_install_location = "/opt/ref";
const std::string ref_version_file_loc = "./";
const std::string ref_version_file_name= "version";
const std::string ref_sheets_root_path = "/opt/ref/sheets";
const std::string user_name = libwlc::LinuxUtility::getCurrentUserName();
const std::string ref_sheets_user_path = "/home/" + user_name + "/.config/ref/sheet";
const std::string ref_user_config_file_path = "/home/" + user_name + "/.config/ref";
const std::string ref_user_config_file_name = "config";
const int         ref_config_key_works_cnt = 4;
const std::string ref_config_key_works_list[] =
{
    "LanguagePriorityList",
    "SearchLanguage",
    "SearchAreaNum",
    "MutilMatchShowFileList",
};
const int         ref_support_language_cnt    = 3;
const std::string ref_support_language_name[] =
{
    "ez",
    "en",
    "zh",
};
bool writeVersionInfoToFile(void);
bool readVersionInfoFromFile(void);
#endif // SETTING_H

