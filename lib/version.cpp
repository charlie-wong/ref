#include "version.h"
#include "value.h"
#include "linuxutility.h"
#include <string.h>
namespace libwlc
{
/////////////////////////////////////////////////
bool Version::major_flag = false;// false，major 无关；true，需比较 major
bool Version::minor_flag = false;// false，minor 无关，true，需比较 major, minor
bool Version::patch_flag = false;// false，patch 无关，true，需比较 major, minor, patch
bool Version::vname_flag = false;
bool Version::hosid_flag = false;
/////////////////////////////////////////////
bool  Version::ccid_flag = false;
bool Version::ccmaj_flag = false;// false，ccmaj 无关；true，需比较 ccmaj
bool Version::ccmin_flag = false;// false，ccmin 无关，true，需比较 ccmaj, ccmin
bool Version::ccpat_flag = false;// false，ccpat 无关，true，需比较 ccmaj, ccmin, ccpat
/////////////////////////////////////////////
bool Version::build_flag = false;// false，build 无效，true，build 有效
/////////////////////////////////////////////
std::string Version::getVersionInfo(const Version &v)
{
    std::string tmp = "";
    if(major_flag)
    {
        tmp = Value(v.getMaj()).asString();
        if(minor_flag)
        {
            tmp += "." + Value(v.getMin()).asString();
        }

        if(patch_flag)
        {
            tmp += "." + Value(v.getPat()).asString();
        }


        if(vname_flag)
        {
            tmp += "(" + v.getVName() + ")";
        }

        if(hosid_flag)
        {
            tmp += " " + map_id_to_HostOSName(v.getHosID());
            tmp += "(" + map_id_to_HostOSBits(v.getHosID()) + ")";
        }

        if(ccid_flag)
        {
            tmp += " " + map_id_to_CCName(v.getCCid());
            if(ccmaj_flag)
            {
                tmp += "(" + Value(v.getCCMaj()).asString();
                if(ccmin_flag)
                {
                    tmp += "." + Value(v.getCCMin()).asString();
                }
                if(ccpat_flag)
                {
                    tmp += "." + Value(v.getCCPat()).asString();
                }
                tmp += ")";
            }
        }

        if(build_flag)
        {
            tmp += " " + showBuild(v.getBuild());
        }
        return tmp;
    }

    return "Unknown";
}
//显示: 主·次·补(昵称) OS 编译器(主·次·补) Y/M/D H:M:S
/////////////////////////////////////////////
int  Version::cp(const Version &v1, const Version &v2)//比较
{
    // 小于  -1
    // 等于   0
    // 大于   1
    if(major_flag && minor_flag && patch_flag)
    {
        if(v1.getMaj() < v2.getMaj())
            return -1;
        if(v1.getMaj() == v2.getMaj() && v1.getMin() < v2.getMin())
            return -1;
        if(v1.getMaj() == v2.getMaj() && v1.getMin() == v2.getMin() && v1.getPat() < v2.getPat())
            return -1;
        ////////////////////////////////////////////////////////////
        if(v1.getMaj() == v2.getMaj() && v1.getMin() == v2.getMin() && v1.getPat() == v2.getPat())
            return 0;
        ////////////////////////////////////////////////////////////
        if(v1.getMaj() > v2.getMaj())
            return 1;
        if(v1.getMaj() == v2.getMaj() && v1.getMin() > v2.getMin())
            return 1;
        if(v1.getMaj() == v2.getMaj() && v1.getMin() == v2.getMin() && v1.getPat() > v2.getPat())
            return 1;
    }
    else if(major_flag && minor_flag)
    {
        if(v1.getMaj() < v2.getMaj())
            return -1;
        if(v1.getMaj() == v2.getMaj() && v1.getMin() < v2.getMin())
            return -1;
        ////////////////////////////////////////////////////////////
        if(v1.getMaj() == v2.getMaj() && v1.getMin() == v2.getMin())
            return 0;
        ////////////////////////////////////////////////////////////
        if(v1.getMaj() > v2.getMaj())
            return 1;
        if(v1.getMaj() == v2.getMaj() && v1.getMin() > v2.getMin())
            return 1;
    }
    else if(major_flag)
    {
        if(v1.getMaj() < v2.getMaj())
            return -1;
        ////////////////////////////////////////////////////////////
        if(v1.getMaj() == v2.getMaj())
            return 0;
        ////////////////////////////////////////////////////////////
        if(v1.getMaj() > v2.getMaj())
            return 1;
    }
    else
    {
        // 版本号均不可用
        std::cerr << "libwlc.so/libwlc.a: Version: Invalid Version Infomation. exit(1).\n";
        exit(1);
    }
}
bool Version::eq(const Version &v1, const Version &v2)// 等于
{
    if(cp(v1,v2) == 0) return true;
    return false;
}
bool Version::ne(const Version &v1, const Version &v2)// 不等
{
    if(cp(v1,v2) != 0) return true;
    return false;
}
bool Version::gt(const Version &v1, const Version &v2)// 大于
{
    if(cp(v1,v2) == 1) return true;
    return false;
}
bool Version::ge(const Version &v1, const Version &v2)// 大于等于
{
    int cp_status = cp(v1,v2);
    if( cp_status == 0 || cp_status == 1) return true;
    return false;
}
bool Version::lt(const Version &v1, const Version &v2)// 小于
{
    if(cp(v1,v2) == -1) return true;
    return false;
}
bool Version::le(const Version &v1, const Version &v2)// 小于等于
{
    int cp_status = cp(v1,v2);
    if( cp_status == 0 || cp_status == -1) return true;
    return false;
}
/////////////////////////////////////////////
int  Version::cpcc(const Version &v1, const Version &v2)//比较
{
    // 小于  -1
    // 等于   0
    // 大于   1
    if(ccmaj_flag && ccmin_flag && ccpat_flag)
    {
        if(v1.getCCMaj() < v2.getCCMaj())
            return -1;
        if(v1.getCCMaj() == v2.getCCMaj() && v1.getCCMin() < v2.getCCMin())
            return -1;
        if(v1.getCCMaj() == v2.getCCMaj() && v1.getCCMin() == v2.getCCMin() && v1.getCCPat() < v2.getCCPat())
            return -1;
        ////////////////////////////////////////////////////////////
        if(v1.getCCMaj() == v2.getCCMaj() && v1.getCCMin() == v2.getCCMin() && v1.getCCPat() == v2.getCCPat())
            return 0;
        ////////////////////////////////////////////////////////////
        if(v1.getCCMaj() > v2.getCCMaj())
            return 1;
        if(v1.getCCMaj() == v2.getCCMaj() && v1.getCCMin() > v2.getCCMin())
            return 1;
        if(v1.getCCMaj() == v2.getCCMaj() && v1.getCCMin() == v2.getCCMin() && v1.getCCPat() > v2.getCCPat())
            return 1;
    }
    else if(ccmaj_flag && ccmin_flag)
    {
        if(v1.getCCMaj() < v2.getCCMaj())
            return -1;
        if(v1.getCCMaj() == v2.getCCMaj() && v1.getCCMin() < v2.getCCMin())
            return -1;
        ////////////////////////////////////////////////////////////
        if(v1.getCCMaj() == v2.getCCMaj() && v1.getCCMin() == v2.getCCMin())
            return 0;
        ////////////////////////////////////////////////////////////
        if(v1.getCCMaj() > v2.getCCMaj())
            return 1;
        if(v1.getCCMaj() == v2.getCCMaj() && v1.getCCMin() > v2.getCCMin())
            return 1;
    }
    else if(ccmaj_flag)
    {
        if(v1.getCCMaj() < v2.getCCMaj())
            return -1;
        ////////////////////////////////////////////////////////////
        if(v1.getCCMaj() == v2.getCCMaj())
            return 0;
        ////////////////////////////////////////////////////////////
        if(v1.getCCMaj() > v2.getCCMaj())
            return 1;
    }
    else
    {
        // 版本号均不可用
        std::cerr << "libwlc.so/libwlc.a: Version: Invalid Complier Version Infomation. exit(1).\n";
        exit(1);
    }
}
bool Version::eqcc(const Version &v1, const Version &v2)// 等于
{
    if(cpcc(v1,v2) == 0) return true;
    return false;
}
bool Version::necc(const Version &v1, const Version &v2)// 不等
{
    if(cpcc(v1,v2) != 0) return true;
    return false;
}
bool Version::gtcc(const Version &v1, const Version &v2)// 大于
{
    if(cpcc(v1,v2) == 1) return true;
    return false;
}
bool Version::gecc(const Version &v1, const Version &v2)// 大于等于
{
    int cpcc_status = cpcc(v1,v2);
    if(cpcc_status == 0 || cpcc_status == 1) return true;
    return false;
}
bool Version::ltcc(const Version &v1, const Version &v2)// 小于
{
    if(cpcc(v1,v2) == -1) return true;
    return false;
}
bool Version::lecc(const Version &v1, const Version &v2)// 小于等于
{
    int cpcc_status = cpcc(v1,v2);
    if(cpcc_status == 0 || cpcc_status == -1) return true;
    return false;
}
/////////////////////////////////////////////
std::string  Version::showBuild(const VersionBits &vbs)
{
    const unsigned char *db = vbs.build;
    return showBuild(db);
}
std::string  Version::showBuild(const unsigned char *bd)
{
    std::string tmp = "";
    for(int i=0; i<7; i++)
    {
        char hig = ((0xF0&bd[i]) >> 4);
        char low = (0x0F&bd[i]);
        tmp += LinuxUtility::convertIntegerToDigitCharacter(hig);
        tmp += LinuxUtility::convertIntegerToDigitCharacter(low);

        if     (i==1)  tmp += "/";
        else if(i==2)  tmp += "/";
        else if(i==3)  tmp += " ";
        else if(i==4)  tmp += ":";
        else if(i==5)  tmp += ":";
    }
    return tmp;
}
std::string  Version::showBuild(const Version &v)
{
    const unsigned char *db = v.getBuild();
    return showBuild(db);
}
void Version::updateBuild(VersionBits &vbs)
{
    libwlc::LinuxUtility::getDateTime(vbs.build);
    build_flag = true;
    return;
}
void Version::updateBuild(unsigned char *bd)
{
    libwlc::LinuxUtility::getDateTime(bd);
    build_flag = true;
    return;
}
void Version::updateBuild(Version &v)
{
    v.setBuild();
    build_flag = true;
    return;
}
/////////////////////////////////////////////
void Version::setAllFlag(void)
{
    major_flag = true;// false，major 无关；true，需比较 major
    minor_flag = true;// false，minor 无关，true，需比较 major, minor
    patch_flag = true;// false，patch 无关，true，需比较 major, minor, patch
    vname_flag = true;
    hosid_flag = true;
    /////////////////////////////////////////////
     ccid_flag = true;
    ccmaj_flag = true;// false，ccmaj 无关；true，需比较 ccmaj
    ccmin_flag = true;// false，ccmin 无关，true，需比较 ccmaj, ccmin
    ccpat_flag = true;// false，ccpat 无关，true，需比较 ccmaj, ccmin, ccpat
    /////////////////////////////////////////////
    build_flag = true;// false，build 无效，true，build 有效
}
void Version::clsAllFlag(void)
{
    major_flag = false;// false，major 无关；true，需比较 major
    minor_flag = false;// false，minor 无关，true，需比较 major, minor
    patch_flag = false;// false，patch 无关，true，需比较 major, minor, patch
    vname_flag = false;
    hosid_flag = false;
    /////////////////////////////////////////////
     ccid_flag = false;
    ccmaj_flag = false;// false，ccmaj 无关；true，需比较 ccmaj
    ccmin_flag = false;// false，ccmin 无关，true，需比较 ccmaj, ccmin
    ccpat_flag = false;// false，ccpat 无关，true，需比较 ccmaj, ccmin, ccpat
    /////////////////////////////////////////////
    build_flag = false;// false，build 无效，true，build 有效
}
/////////////////////////////////////////////
Version::Version(void)
{
    major_flag = true;
    minor_flag = true;
    patch_flag = true;
}
Version::Version(const Version &v)
{
    Version(*v.getVersionBits());
}
Version::Version(const VersionBits &v)
{
    if(build_flag)
    {
        m_ver.build[0] = v.build[0];
        m_ver.build[1] = v.build[1];
        m_ver.build[2] = v.build[2];
        m_ver.build[3] = v.build[3];
        m_ver.build[4] = v.build[4];
        m_ver.build[5] = v.build[5];
        m_ver.build[6] = v.build[6];
    }
    else
    {
        memset(m_ver.build,0,sizeof(m_ver.build));
    }

    if(ccid_flag)   m_ver.ccid  = v.ccid;
    else            m_ver.ccid  = 0;

    if(ccmaj_flag)  m_ver.ccmaj = v.ccmaj;
    else            m_ver.ccmaj = 0;

    if(ccmin_flag)  m_ver.ccmin = v.ccmin;
    else            m_ver.ccmin = 0;

    if(ccpat_flag)  m_ver.ccpat = v.ccpat;
    else            m_ver.ccpat = 0;

    if(hosid_flag)  m_ver.hosid = v.hosid;
    else            m_ver.hosid = 0;

    if(major_flag)  m_ver.major = v.major;
    else            m_ver.major = 0;

    if(minor_flag)  m_ver.minor = v.minor;
    else            m_ver.minor = 0;

    if(patch_flag)  m_ver.patch = v.patch;
    else            m_ver.patch = 0;

    if(vname_flag)
    {
        size_t i;
        size_t cnt = 0;
        for(i=0; v.vname[i]!='\0'; i++)
        {
            cnt++;
            m_ver.vname[i] = v.vname[i];
            if(cnt > 256)
            {
                std::cerr << "libwlc.so/libwlc.a: Version: Name [";
                std::cerr << v.vname;
                std::cerr << "] too long. exit(1).\n";
                exit(1);
            }
        }
        m_ver.vname[i] = '\0';
    }
    else
    {
        memset(m_ver.vname,0,sizeof(m_ver.vname));
    }
}
Version::Version(unsigned char mj, unsigned char mi, unsigned char ph, char *vn)
{
    m_ver.major = mj;
    m_ver.minor = mi;
    m_ver.patch = ph;

    major_flag = true;
    minor_flag = true;
    patch_flag = true;

    if(vn) setVName(vn);

}
Version::Version(int mj, int mi, int ph, char *vn)
{
    m_ver.major = (unsigned char)mj;
    m_ver.minor = (unsigned char)mi;
    m_ver.patch = (unsigned char)ph;

    major_flag = true;
    minor_flag = true;
    patch_flag = true;

    if(vn) setVName(vn);

    /////////////////////////////////////////////
    // 关于主机的信息收集
    bool hosid_flag_backup = hosid_flag;
    hosid_flag = false;
    std::string    info = "";
    std::string cc_vion = "";
    std::string os_name = "";
    std::string os_arch = "";

    info = getGCCInfo();
    if(hosid_flag && !info.empty())
    {
        size_t ix = info.find(' ');
        if(ix != std::string::npos)
        {
            os_name = info.substr(ix+1);//操作系统
            cc_vion = info.substr(0,ix);//GCC版本号
        }
    }
    info = getHostOSInfo();
    if(!info.empty())
    {
        size_t ix = info.find(' ');
        if(ix != std::string::npos)
        {
            os_arch = info.substr(ix+1);//CPU体系结构
            if(os_name.empty()) os_name = info.substr(0,ix);//操作系统
        }
    }

    if(!os_name.empty() && !os_arch.empty())
    {
        unsigned char os_name_id = map_HostOSName_to_id(os_name);
        unsigned char os_arch_id = map_HostOSBits_to_id(os_arch);
        if(os_arch_id == 0xFF)
        {
            std::cerr << "libwlc.so/libwlc.a: Version: Unknown Architectural. set to x86.\n";
            os_arch_id = 0x00;
        }

        setHosID((os_arch_id|os_name_id));
        hosid_flag = true;
    }
    else
    {
        hosid_flag = hosid_flag_backup;
    }

    if(!cc_vion.empty())
    {
        unsigned char majx = libwlc::LinuxUtility::convertDigitCharacterToInteger(cc_vion[0]);
        unsigned char minx = libwlc::LinuxUtility::convertDigitCharacterToInteger(cc_vion[2]);
        unsigned char patx = libwlc::LinuxUtility::convertDigitCharacterToInteger(cc_vion[4]);
        setCCid(map_CCName_to_id("GCC"));
        setCCMaj(majx);
        setCCMin(minx);
        setCCPat(patx);
         ccid_flag = true;
        ccmaj_flag = true;
        ccmin_flag = true;
        ccpat_flag = true;
    }

    setBuild();
    build_flag = true;
}
bool Version::readFromFile(const std::string path, const std::string file)
{
    std::string pn = path + file;

    FILE *fp = fopen(pn.c_str(),"rb");
    size_t rcnt = fread(&m_ver,1,sizeof(m_ver),fp);
    fclose(fp);

    if(rcnt == sizeof(m_ver))
    {
        setAllFlag();
        return true;
    }
    else
        return false;
}
bool Version::writeToFile(const std::string path, const std::string file)
{
    std::string pn = path + file;

    FILE *fp = fopen(pn.c_str(),"w+");//读写方式方式创建新的文本文件
    size_t wcnt = fwrite(&m_ver,1,sizeof(m_ver),fp);
    fclose(fp);

    if(wcnt == sizeof(m_ver))
        return true;
    else
        return false;
}
/////////////////////////////////////////////
void Version::setMaj(const unsigned char maj)
{
    m_ver.major = maj;
    major_flag = true;
    return;
}
void Version::setMin(const unsigned char min)
{
    m_ver.minor = min;
    minor_flag = true;
    return;
}
void Version::setPat(const unsigned char pat)
{
    m_ver.patch = pat;
    patch_flag = true;
    return;
}
unsigned char Version::getMaj(void) const
{
    return m_ver.major;
}
unsigned char Version::getMin(void) const
{
    return m_ver.minor;
}
unsigned char Version::getPat(void) const
{
    return m_ver.patch;
}
/////////////////////////////////////////////
void Version::setVName(const std::string &vn)
{
    size_t len = vn.length();
    if(len > 256)
    {
        std::cerr << "libwlc.so/libwlc.a: Version: Name ["+ vn << "] too long. exit(1).\n";
        exit(1);
    }
    m_ver.vname[len] = '\0';
    for(size_t i=0; i<len; i++)
    {
        m_ver.vname[i] = vn[i];
    }
    vname_flag = true;
    return;
}
void Version::setVName(const char *vn)
{
    size_t len = 0;
    const char *cur = vn;
    while(*cur++ != '\0') len++;

    if(len > 256)
    {
        std::cerr << "libwlc.so/libwlc.a: Version: Name [";
        std::cerr << vn;
        std::cerr << "] too long. exit(1).\n";
        exit(1);
    }
    m_ver.vname[len] = '\0';
    for(size_t i=0; i<len; i++)
    {
        m_ver.vname[i] = vn[i];
    }
    vname_flag = true;
    return;
}
std::string Version::getVName(void) const
{
    return std::string(m_ver.vname);
}
/////////////////////////////////////////////
void Version::setHosID(const unsigned char id)
{
    m_ver.hosid = id;
    hosid_flag = true;
    return;
}
unsigned char Version::getHosID(void) const
{
    return m_ver.hosid;
}
/////////////////////////////////////////////
void Version::setCCid(const unsigned char ccid)
{
    m_ver.ccid = ccid;
     ccid_flag = true;
    return;
}
void Version::setCCMaj(const unsigned char maj)
{
    m_ver.ccmaj = maj;
    ccmaj_flag = true;
    return;
}
void Version::setCCMin(const unsigned char min)
{
    m_ver.ccmin = min;
    ccmin_flag = true;
    return;
}
void Version::setCCPat(const unsigned char pat)
{
    m_ver.ccpat = pat;
    ccpat_flag = true;
    return;
}
unsigned char Version::getCCid(void) const
{
    return m_ver.ccid;
}
unsigned char Version::getCCMaj(void) const
{
    return m_ver.ccmaj;
}
unsigned char Version::getCCMin(void) const
{
    return m_ver.ccmin;
}
unsigned char Version::getCCPat(void) const
{
    return m_ver.ccpat;
}
/////////////////////////////////////////////
void Version::setBuild(void)
{
    libwlc::LinuxUtility::getDateTime(m_ver.build);
    build_flag = true;
    return;
}
const unsigned char *Version::getBuild(void) const
{
    return m_ver.build;
}
/////////////////////////////////////////////
void Version::setAllZero(void)
{
    memset(&m_ver,0,sizeof(m_ver));
    clsAllFlag();
}
const VersionBits *Version::getVersionBits(void) const
{
    return &m_ver;
}
/////////////////////////////////////////////
std::string Version::getGCCInfo(void)
{
    char buffer[256];
    memset(buffer,0,sizeof(buffer));

    FILE *fp = popen("gcc --version","r");
    if(!fp)
    {
        std::cerr << "libwlc.so/libwlc.a: Version: Did you install GCC, and make it in the PATH?\n";
        return "";
    }
    fgets(buffer,sizeof(buffer),fp);
    pclose(fp);

    if(buffer[0] == 'g' && buffer[1] == 'c' && buffer[2] == 'c')
    {
        std::string wlc = "";
        std::string tmp(buffer);
        size_t ubi = tmp.find("Ubuntu");
        if(ubi == std::string::npos)
            ubi = tmp.find("ubuntu");
        if(ubi != std::string::npos)
        {
            hosid_flag = true;
            wlc = tmp.substr(ubi,6);
        }

        size_t len = tmp.length();
        buffer[0] = tmp[len-6];
        buffer[1] = tmp[len-5];
        buffer[2] = tmp[len-4];
        buffer[3] = tmp[len-3];
        buffer[4] = tmp[len-2];
        buffer[5] = 0;

        if(!wlc.empty())
            wlc = std::string(buffer) + " " + wlc;
        else
            wlc = std::string(buffer);

        return wlc;
    }
    return "";
}
std::string Version::getHostOSInfo(void)
{
    char buffer[256];
    memset(buffer,0,sizeof(buffer));

    FILE *fp = popen("uname -p","r");
    if(!fp)
    {
        std::cerr << "libwlc.so/libwlc.a: Version: Can't get Processor Type\n";
        return "";
    }
    fgets(buffer,sizeof(buffer),fp);
    pclose(fp);
    char *pb = buffer;
    while(*pb !='\n') pb++;
    *pb = 0;
    std::string cpu_arch(buffer);


    fp = popen("uname -o","r");
    if(!fp)
    {
        std::cerr << "libwlc.so/libwlc.a: Version: Can't get Processor Type\n";
        return "";
    }
    fgets(buffer,sizeof(buffer),fp);
    pclose(fp);
    pb = buffer;
    while(*pb !='\n') pb++;
    *pb = 0;
    std::string os(buffer);
    std::string wlc = os + " " + cpu_arch;
    return wlc;
}
std::string   Version::map_id_to_HostOSName(const unsigned char hid)
{
    switch(hid)
    {
    case 0:   return "Unknown-Host-OS";//32位
    case 1:   return "Ubuntu";
    case 2:   return "GNU/Linux";
    //////////////////////////////////////////////////
    case 128: return "Unknown-Host-OS";//64位
    case 129: return "Ubuntu";
    case 130: return "GNU/Linux";
    ///////////////////////////////////////////////////
    default:  return "Unknown-Host-OS";
    }
}
std::string   Version::map_id_to_HostOSBits(const unsigned char hid)
{
    unsigned char seven_bit = (hid & 0x80);
    if     (seven_bit == 0x00) return "x86";
    else if(seven_bit == 0x80) return "x86_64";
    else                       return "?";
}
std::string   Version::map_id_to_CCName(const unsigned char ccid)
{
    switch(ccid)
    {
    case   0: return "Unknow-Compiler";
    case   1: return "GCC";
    default:  return "Unknow-Compiler";
    }
}
unsigned char Version::map_HostOSName_to_id(const std::string &osn)
{
    if(osn == "Ubuntu" || osn == "ubuntu")
        return 0x01;
    else if(osn == "GNU/Linux")
        return 0x02;
    else
        return 0x00;

}
unsigned char Version::map_HostOSBits_to_id(const std::string &osb)
{
/* 你妹的空字符！！！
 *
 *  bool x_86;
    bool x_64;
    size_t len = osb.length();
    char b_0 = osb[0];
    char b_1 = osb[1];
    char b_2 = osb[2];
    char b_3 = osb[3];
    char b_4 = osb[4];
    char b_5 = osb[5];
    char b_6 = osb[7];
    if(len == 3)
    {

        if(osb[0]=='x' || osb[0]=='X')
        {
            if(osb[1]=='8' && osb[2]=='6')
                x_86 = true;
            if(osb[1]=='6' && osb[2]=='4')
                x_64 = true;
        }
    }
    else if(len == 5)
    {
        if(osb[0]=='x' || osb[0]=='X')
        {
            if(osb[1]=='8' && osb[2]=='6' && osb[3]=='6' && osb[4]=='4')
                x_64 = true;
        }
        if(osb[0]=='a' || osb[0]=='A')
        {
            if(osb[1]=='m' || osb[1]=='M')
            {
                if(osb[2]=='d' || osb[2]=='D')
                {
                    if(osb[3]=='6' || osb[4]=='4')
                    {
                        x_64 = true;
                    }
                }
            }
        }
    }
    else if(len == 6)
    {
        if(osb[0]=='x' || osb[0]=='X')
        {
            if(osb[1]=='8' && osb[2]=='6' && osb[3]=='_' &&
               osb[4]=='6' && osb[5]=='4')
                x_64 = true;
        }
    }
    else
    {
        x_86 = false;
        x_64 = false;
    }*/
    /////////////////////////////////////////
    if(osb=="x86" || osb=="X86")
        return (unsigned char)0x00;
    else if(osb=="x86_64" || osb=="X86_64" || osb=="ADM64" ||
            osb=="x64" || osb=="X64" || osb=="adm64")
        return (unsigned char)0x80;
    else
    {
        std::cerr << "libwlc.so/libwlc.a: Version: Unknown Processor Type.\n";
        return 0xFF;
    }
}
unsigned char Version::map_CCName_to_id(const std::string &ccn)
{
    if(ccn == "gcc" || ccn == "GCC" || ccn == "g++" || ccn == "G++")
        return 0x01;
    else
        return 0x00;
}
/////////////////////////////////////////////////
}
