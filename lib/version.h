#ifndef LIB_WLC_VERSION_H
#define LIB_WLC_VERSION_H
#include <iostream>
namespace libwlc
{
/////////////////////////////////////////////////
typedef struct __VersionBits__
{
    unsigned char major;//主版本号
    unsigned char minor;//次版本号
    unsigned char patch;//补丁包号
        char vname[256];//版本昵称

    unsigned char hosid;//构建主机操作系统ID
    // 0        -> 未知
    //32位系统可用 ID 范围 [  1,127]
    //        1 -> Ubuntu(X86)
    //64位系统可用 ID 范围 [128,255]
    //      128 -> Ubuntu(ADM64)
    unsigned char  ccid;//构建编译器ID
    //      0   -> 未知
    //      1   -> GCC
    unsigned char ccmaj;//构建编译器主版本号
    unsigned char ccmin;//构建编译器次版本号
    unsigned char ccpat;//构建编译器补丁包号

    unsigned char build[7];//构建年月日时分秒
}VersionBits;
class Version
{
public:
    //显示: 主·次·补(昵称) OS 编译器(主·次·补) Y/M/D H:M:S
    static std::string getVersionInfo(const Version &v);
private:
    static std::string   getGCCInfo(void);
    static std::string   getHostOSInfo(void);
    static std::string   map_id_to_HostOSName(const unsigned char hid);
    static std::string   map_id_to_HostOSBits(const unsigned char hid);
    static unsigned char map_HostOSName_to_id(const std::string &osn);
    static unsigned char map_HostOSBits_to_id(const std::string &osb);
    static std::string   map_id_to_CCName(const unsigned char ccid);
    static unsigned char map_CCName_to_id(const std::string &ccn);
    static int  cp(const Version &v1, const Version &v2);//比较
public:
    static bool eq(const Version &v1, const Version &v2);// 等于
    static bool ne(const Version &v1, const Version &v2);// 不等
    static bool gt(const Version &v1, const Version &v2);// 大于
    static bool ge(const Version &v1, const Version &v2);// 大于等于
    static bool lt(const Version &v1, const Version &v2);// 小于
    static bool le(const Version &v1, const Version &v2);// 小于等于
    /////////////////////////////////////////////
private:
    static int  cpcc(const Version &v1, const Version &v2);//比较
public:
    static bool eqcc(const Version &v1, const Version &v2);// 等于
    static bool necc(const Version &v1, const Version &v2);// 不等
    static bool gtcc(const Version &v1, const Version &v2);// 大于
    static bool gecc(const Version &v1, const Version &v2);// 大于等于
    static bool ltcc(const Version &v1, const Version &v2);// 小于
    static bool lecc(const Version &v1, const Version &v2);// 小于等于
    /////////////////////////////////////////////
    static std::string  showBuild(const VersionBits &vbs);
    static std::string  showBuild(const unsigned char *bd);
    static std::string  showBuild(const Version &v);
    static void updateBuild(VersionBits &vbs);
    static void updateBuild(unsigned char *bd);
    static void updateBuild(Version &v);
    /////////////////////////////////////////////
    static void setAllFlag(void);
    static void clsAllFlag(void);
    /////////////////////////////////////////////
    static bool major_flag;// false，major 无关；true，需比较 major
    static bool minor_flag;// false，minor 无关，true，需比较 major, minor
    static bool patch_flag;// false，patch 无关，true，需比较 major, minor, patch
    static bool vname_flag;
    static bool hosid_flag;
    /////////////////////////////////////////////
    static bool  ccid_flag;
    static bool ccmaj_flag;// false，ccmaj 无关；true，需比较 ccmaj
    static bool ccmin_flag;// false，ccmin 无关，true，需比较 ccmaj, ccmin
    static bool ccpat_flag;// false，ccpat 无关，true，需比较 ccmaj, ccmin, ccpat
    /////////////////////////////////////////////
    static bool build_flag;// false，build 无效，true，build 有效
public:
    explicit Version(void);
    explicit Version(const Version &v);
    explicit Version(const VersionBits &v);
    explicit Version(unsigned char mj, unsigned char mi, unsigned char ph, char *vn=nullptr);
    explicit Version(int mj, int mi, int ph, char *vn=nullptr);
    bool readFromFile(const std::string path, const std::string file);
    bool writeToFile(const std::string path, const std::string file);
    /////////////////////////////////////////////
    void setMaj(const unsigned char maj);
    void setMin(const unsigned char min);
    void setPat(const unsigned char pat);
    unsigned char getMaj(void) const;
    unsigned char getMin(void) const;
    unsigned char getPat(void) const;
    /////////////////////////////////////////////
    void setVName(const std::string &vn);
    void setVName(const char *vn);
    std::string getVName(void) const;
    /////////////////////////////////////////////
    void setHosID(const unsigned char id);
    unsigned char getHosID(void) const;
    /////////////////////////////////////////////
    void setCCid(const unsigned char ccid);
    void setCCMaj(const unsigned char maj);
    void setCCMin(const unsigned char min);
    void setCCPat(const unsigned char pat);
    unsigned char getCCid(void) const;
    unsigned char getCCMaj(void) const;
    unsigned char getCCMin(void) const;
    unsigned char getCCPat(void) const;
    /////////////////////////////////////////////
    void setBuild(void);
    const unsigned char *getBuild(void) const;
    /////////////////////////////////////////////
    void setAllZero(void);
    const VersionBits *getVersionBits(void) const;
private:
    VersionBits m_ver;
};
/////////////////////////////////////////////////
}
#endif // LIB_WLC_VERSION_H
