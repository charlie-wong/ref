#include <stdlib.h>
#include <string.h>
#include "value.h"
#include "linuxutility.h"

namespace libwlc
{
/////////////////////////////////////////////////
bool Value::asBool(void) const
{
    std::string id = get_cur_union_member_type_id(m_index);

    if(typeid(bool).name()==id)
    {//bool                    m_bool;          //0
        return m_data.m_bool;
    }
    else if(typeid(char).name()==id)
    {//char                    m_char;          //1
        if(m_data.m_char != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const char*).name()==id)
    {//const char*             m_char_ptr;      //2
        if(m_data.m_char_ptr != nullptr && *m_data.m_char_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(unsigned char).name()==id)
    {//unsigned char           m_uchar;         //3
        if(m_data.m_uchar != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const unsigned char*).name()==id)
    {//const unsigned char*    m_uchar_ptr;     //4
        if(m_data.m_uchar_ptr != nullptr && *m_data.m_uchar_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(short).name()==id)
    {//short                   m_short;         //5
        if(m_data.m_short != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const short*).name()==id)
    {//const short*            m_short_ptr;     //6
        if(m_data.m_short_ptr != nullptr && *m_data.m_short_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(unsigned short).name()==id)
    {//unsigned short          m_ushort;		//7
        if(m_data.m_ushort != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const unsigned short*).name()==id)
    {//const unsigned short*   m_ushort_ptr;	//8
        if(m_data.m_ushort_ptr != nullptr && *m_data.m_ushort_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(int).name()==id)
    {//int                     m_int;           //9
        if(m_data.m_int != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const int*).name()==id)
    {//const int*              m_int_ptr;       //10
        if(m_data.m_int_ptr != nullptr && *m_data.m_int_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(unsigned int).name()==id)
    {//unsigned int            m_uint;          //11
        if(m_data.m_uint != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const unsigned int*).name()==id)
    {//const unsigned int*     m_uint_ptr;      //12
        if(m_data.m_uint_ptr != nullptr && *m_data.m_uint_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(long).name()==id)
    {//long                    m_long;          //13
        if(m_data.m_long != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const long*).name()==id)
    {//const long*             m_long_ptr;      //14
        if(m_data.m_long_ptr != nullptr && *m_data.m_long_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(unsigned long).name()==id)
    {//unsigned long           m_ulong;         //15
        if(m_data.m_ulong != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const unsigned long*).name()==id)
    {//const unsigned long*    m_ulong_ptr;     //16
        if(m_data.m_ulong_ptr != nullptr && *m_data.m_ulong_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(float).name()==id)
    {//float                   m_float;         //17
        if(m_data.m_float != 0)
            return true;
        else
             return false;
    }
    else if(typeid(const float*).name()==id)
    {//const float*            m_float_ptr;     //18
        if(m_data.m_float_ptr != nullptr && *m_data.m_float_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(double).name()==id)
    {//double                  m_double;		//19
        if(m_data.m_double != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const double*).name()==id)
    {//const double*           m_double_ptr;	//20
        if(m_data.m_double_ptr != nullptr && *m_data.m_double_ptr != 0)
            return true;
        else
            return false;
    }
    else if(typeid(const std::string*).name()==id)
    {//const std::string*      m_string_ptr;	//21
        if(m_data.m_string_ptr != nullptr && !(*m_data.m_string_ptr).empty())
            return true;
        else
            return false;
    }
    else if(typeid(const Value*).name()==id)
    {//const Value*            m_value_ptr;     //22
        if(m_data.m_value_ptr != nullptr)
            return m_data.m_value_ptr->asBool();
        else
            opps();
    }
    else if(typeid(const ColorCode).name()==id)
    {//const ColorCode         m_color_code;	//23
        if(m_data.m_color_code != 0)
            return true;
        else
            return false;
    }
    else
    {
        opps();
    }
    return false;//消除编译返回值缺失警告
}
std::string Value::asString(void) const
{
    std::string id = get_cur_union_member_type_id(m_index);

    if(typeid(bool).name()==id)
    {//bool                    m_bool;          //0
        if(m_data.m_bool)
            return "true";
        else
            return "false";
    }
    else if(typeid(char).name()==id)
    {//char                    m_char;          //1
        char tmp[2];
        tmp[0] = m_data.m_char;
        tmp[1] = 0;
        return std::string(tmp);
    }
    else if(typeid(const char*).name()==id)
    {//const char*             m_char_ptr;      //2
        if(m_data.m_char_ptr != nullptr)
        {
            const char *ptr = m_data.m_char_ptr;
            char tmp[size];
            unsigned int cnt = 0;
            while(*ptr != '\0' && cnt < size)
            {
                tmp[cnt] = ptr[cnt];
                cnt++;
            }
            tmp[cnt] = 0;

            return std::string(tmp);
        }
        else
            opps();
    }
    else if(typeid(unsigned char).name()==id)
    {//unsigned char           m_uchar;         //3
        char tmp[2];
        tmp[0] = LinuxUtility::convertIntegerToDigitCharacter(m_data.m_uchar);
        tmp[1] = 0;
        return std::string(tmp);
    }
    else if(typeid(const unsigned char*).name()==id)
    {//const unsigned char*    m_uchar_ptr;     //4
        if(m_data.m_uchar_ptr != nullptr)
        {
            const unsigned char *ptr = m_data.m_uchar_ptr;
            char tmp[size];
            unsigned int cnt = 0;
            while(*ptr != '\0' && cnt < size)
            {
                tmp[cnt] = (char)ptr[cnt];
                cnt++;
            }
            tmp[cnt] = 0;

            return std::string(tmp);
        }
        else
            opps();
    }
    else if(typeid(short).name()==id)
    {//short                   m_short;         //5
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"%hd",m_data.m_short);
        return std::string(tmp);
    }
    else if(typeid(const short*).name()==id)
    {//const short*            m_short_ptr;     //6
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        if(m_data.m_short_ptr != nullptr)
            sprintf(tmp,"%hd",*m_data.m_short_ptr);
        else
            opps();
        return std::string(tmp);
    }
    else if(typeid(unsigned short).name()==id)
    {//unsigned short          m_ushort;		//7
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"%hu",m_data.m_ushort);
        return std::string(tmp);
    }
    else if(typeid(const unsigned short*).name()==id)
    {//const unsigned short*   m_ushort_ptr;	//8
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        if(m_data.m_ushort_ptr != nullptr)
            sprintf(tmp,"%hu",*m_data.m_ushort_ptr);
        else
            opps();
        return std::string(tmp);
    }
    else if(typeid(int).name()==id)
    {//int                     m_int;           //9
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"%d",m_data.m_int);
        return std::string(tmp);
    }
    else if(typeid(const int*).name()==id)
    {//const int*              m_int_ptr;       //10
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        if(m_data.m_int_ptr != nullptr)
            sprintf(tmp,"%d",*m_data.m_int_ptr);
        else
            opps();
        return std::string(tmp);
    }
    else if(typeid(unsigned int).name()==id)
    {//unsigned int            m_uint;          //11
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"%u",m_data.m_uint);
        return std::string(tmp);
    }
    else if(typeid(const unsigned int*).name()==id)
    {//const unsigned int*     m_uint_ptr;      //12
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        if(m_data.m_uint_ptr != nullptr)
            sprintf(tmp,"%u",*m_data.m_uint_ptr);
        else
            opps();
        return std::string(tmp);
    }
    else if(typeid(long).name()==id)
    {//long                    m_long;          //13
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"%ld",m_data.m_long);
        return std::string(tmp);
    }
    else if(typeid(const long*).name()==id)
    {//const long*             m_long_ptr;      //14
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        if(m_data.m_long_ptr != nullptr)
            sprintf(tmp,"%ld",*m_data.m_long_ptr);
        else
            opps();
        return std::string(tmp);
    }
    else if(typeid(unsigned long).name()==id)
    {//unsigned long           m_ulong;         //15
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"%lu",m_data.m_ulong);
        return std::string(tmp);
    }
    else if(typeid(const unsigned long*).name()==id)
    {//const unsigned long*    m_ulong_ptr;     //16
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        if(m_data.m_ulong_ptr != nullptr)
            sprintf(tmp,"%lu",*m_data.m_ulong_ptr);
        else
            opps();
        return std::string(tmp);
    }
    else if(typeid(float).name()==id)
    {//float                   m_float;         //17
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"%f",m_data.m_float);
        return std::string(tmp);
    }
    else if(typeid(const float*).name()==id)
    {//const float*            m_float_ptr;     //18
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        if(m_data.m_float_ptr != nullptr)
            sprintf(tmp,"%f",*m_data.m_float_ptr);
        else
            opps();
        return std::string(tmp);
    }
    else if(typeid(double).name()==id)
    {//double                  m_double;		//19
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp,"%lf",m_data.m_double);
        return std::string(tmp);
    }
    else if(typeid(const double*).name()==id)
    {//const double*           m_double_ptr;	//20
        char tmp[256];
        memset(tmp,0,sizeof(tmp));
        if(m_data.m_double_ptr != nullptr)
            sprintf(tmp,"%lf",*m_data.m_double_ptr);
        else
            opps();
        return std::string(tmp);
    }
    else if(typeid(const std::string*).name()==id)
    {//const std::string*      m_string_ptr;	//21
        if(m_data.m_string_ptr != nullptr)
            return *m_data.m_string_ptr;
        else
            opps();
    }
    else if(typeid(const Value*).name()==id)
    {//const Value*            m_value_ptr;     //22
        //return convert_value_to_string(m_data.m_value_ptr);
        if(m_data.m_value_ptr != nullptr)
            return m_data.m_value_ptr->asString();
        else
            opps();
    }
    else if(typeid(const ColorCode).name()==id)
    {//const ColorCode         m_color_code;	//23
    	std::string tmp;
    	tmp = "\e[" + Value((int)m_data.m_color_code).asString() + "m";
    	return tmp;
    }
    else
    {
        opps();
    }
    return "";//消除编译返回值缺失警告
}
short Value::asShort(void) const
{
    std::string id = get_cur_union_member_type_id(m_index);

    if(typeid(bool).name()==id)
    {//bool                    m_bool;          //0
        if(m_data.m_bool)
            return short(1);
        else
            return short(0);
    }
    else if(typeid(char).name()==id)
    {//char                    m_char;          //1
        return short(m_data.m_char);
    }
    else if(typeid(const char*).name()==id)
    {//const char*             m_char_ptr;      //2
        if(m_data.m_char_ptr != nullptr)
        {
            std::string tmp(m_data.m_char_ptr);
            return short(convert_string_to_integer(&tmp));
        }
        else
            opps();
    }
    else if(typeid(unsigned char).name()==id)
    {//unsigned char           m_uchar;         //3
        return short(m_data.m_uchar);
    }
    else if(typeid(const unsigned char*).name()==id)
    {//const unsigned char*    m_uchar_ptr;     //4
        if(m_data.m_uchar_ptr != nullptr)
            return short(*m_data.m_uchar_ptr);
        else
            opps();
    }
    else if(typeid(short).name()==id)
    {//short                   m_short;         //5
        return m_data.m_short;
    }
    else if(typeid(const short*).name()==id)
    {//const short*            m_short_ptr;     //6
        if(m_data.m_short_ptr != nullptr)
            return *m_data.m_short_ptr;
        else
            opps();
    }
    else if(typeid(unsigned short).name()==id)
    {//unsigned short          m_ushort;		//7
        return short(m_data.m_ushort);
    }
    else if(typeid(const unsigned short*).name()==id)
    {//const unsigned short*   m_ushort_ptr;	//8
        if(m_data.m_ushort_ptr != nullptr)
            return short(*m_data.m_ushort_ptr);
        else
            opps();
    }
    else if(typeid(int).name()==id)
    {//int                     m_int;           //9
        return short(m_data.m_int);
    }
    else if(typeid(const int*).name()==id)
    {//const int*              m_int_ptr;       //10
        if(m_data.m_int_ptr != nullptr)
            return short(*m_data.m_int_ptr);
        else
            opps();
    }
    else if(typeid(unsigned int).name()==id)
    {//unsigned int            m_uint;          //11
        return short(m_data.m_uint);
    }
    else if(typeid(const unsigned int*).name()==id)
    {//const unsigned int*     m_uint_ptr;      //12
        if(m_data.m_uint_ptr != nullptr)
            return short(*m_data.m_uint_ptr);
        else
            opps();
    }
    else if(typeid(long).name()==id)
    {//long                    m_long;          //13
        return short(m_data.m_long);
    }
    else if(typeid(const long*).name()==id)
    {//const long*             m_long_ptr;      //14
        if(m_data.m_long_ptr != nullptr)
            return short(*m_data.m_long_ptr);
        else
            opps();
    }
    else if(typeid(unsigned long).name()==id)
    {//unsigned long           m_ulong;         //15
        return short(m_data.m_ulong);
    }
    else if(typeid(const unsigned long*).name()==id)
    {//const unsigned long*    m_ulong_ptr;     //16
        if(m_data.m_ulong_ptr != nullptr)
            return short(*m_data.m_ulong_ptr);
        else
            opps();
    }
    else if(typeid(float).name()==id)
    {//float                   m_float;         //17
        return short(m_data.m_float);
    }
    else if(typeid(const float*).name()==id)
    {//const float*            m_float_ptr;     //18
        if(m_data.m_float_ptr != nullptr)
            return short(*m_data.m_float_ptr);
        else
            opps();
    }
    else if(typeid(double).name()==id)
    {//double                  m_double;		//19
        return short(m_data.m_double);
    }
    else if(typeid(const double*).name()==id)
    {//const double*           m_double_ptr;	//20
        if(m_data.m_double_ptr != nullptr)
            return short(*m_data.m_double_ptr);
        else
            opps();
    }
    else if(typeid(const std::string*).name()==id)
    {//const std::string*      m_string_ptr;	//21
        if(m_data.m_string_ptr != nullptr)
        {
            return short(convert_string_to_integer(m_data.m_string_ptr));
        }
        else
            opps();

    }
    else if(typeid(const Value*).name()==id)
    {//const Value*            m_value_ptr;     //22
        //return convert_value_to_string(m_data.m_value_ptr);

        if(m_data.m_value_ptr != nullptr)
            return m_data.m_value_ptr->asShort();
        else
            opps();
    }
    else if(typeid(const ColorCode).name()==id)
    {//const ColorCode         m_color_code;	//23
    	return (short)m_data.m_color_code;
    }
    else
    {
        opps();
    }
    return 0;//消除编译返回值缺失警告
}
int Value::asInt(void) const
{
    std::string id = get_cur_union_member_type_id(m_index);

    if(typeid(bool).name()==id)
    {//bool                    m_bool;          //0
        if(m_data.m_bool)
            return int(1);
        else
            return int(0);
    }
    else if(typeid(char).name()==id)
    {//char                    m_char;          //1
        return int(m_data.m_char);
    }
    else if(typeid(const char*).name()==id)
    {//const char*             m_char_ptr;      //2
        if(m_data.m_char_ptr != nullptr)
        {
            std::string tmp(m_data.m_char_ptr);
            return int(convert_string_to_integer(&tmp));
        }
        else
            opps();
    }
    else if(typeid(unsigned char).name()==id)
    {//unsigned char           m_uchar;         //3
        return int(m_data.m_uchar);
    }
    else if(typeid(const unsigned char*).name()==id)
    {//const unsigned char*    m_uchar_ptr;     //4
        if(m_data.m_uchar_ptr != nullptr)
            return int(*m_data.m_uchar_ptr);
        else
            opps();
    }
    else if(typeid(short).name()==id)
    {//short                   m_short;         //5
        return int(m_data.m_short);
    }
    else if(typeid(const short*).name()==id)
    {//const short*            m_short_ptr;     //6
        if(m_data.m_short_ptr != nullptr)
            return int(*m_data.m_short_ptr);
        else
            opps();
    }
    else if(typeid(unsigned short).name()==id)
    {//unsigned short          m_ushort;		//7
        return int(m_data.m_ushort);
    }
    else if(typeid(const unsigned short*).name()==id)
    {//const unsigned short*   m_ushort_ptr;	//8
        if(m_data.m_ushort_ptr != nullptr)
            return int(*m_data.m_ushort_ptr);
        else
            opps();
    }
    else if(typeid(int).name()==id)
    {//int                     m_int;           //9
        return int(m_data.m_int);
    }
    else if(typeid(const int*).name()==id)
    {//const int*              m_int_ptr;       //10
        if(m_data.m_int_ptr != nullptr)
            return int(*m_data.m_int_ptr);
        else
            opps();
    }
    else if(typeid(unsigned int).name()==id)
    {//unsigned int            m_uint;          //11
        return int(m_data.m_uint);
    }
    else if(typeid(const unsigned int*).name()==id)
    {//const unsigned int*     m_uint_ptr;      //12
        if(m_data.m_uint_ptr != nullptr)
            return int(*m_data.m_uint_ptr);
        else
            opps();
    }
    else if(typeid(long).name()==id)
    {//long                    m_long;          //13
        return int(m_data.m_long);
    }
    else if(typeid(const long*).name()==id)
    {//const long*             m_long_ptr;      //14
        if(m_data.m_long_ptr != nullptr)
            return int(*m_data.m_long_ptr);
        else
            opps();
    }
    else if(typeid(unsigned long).name()==id)
    {//unsigned long           m_ulong;         //15
        return int(m_data.m_ulong);
    }
    else if(typeid(const unsigned long*).name()==id)
    {//const unsigned long*    m_ulong_ptr;     //16
        if(m_data.m_ulong_ptr != nullptr)
            return int(*m_data.m_ulong_ptr);
        else
            opps();
    }
    else if(typeid(float).name()==id)
    {//float                   m_float;         //17
        return int(m_data.m_float);
    }
    else if(typeid(const float*).name()==id)
    {//const float*            m_float_ptr;     //18
        if(m_data.m_float_ptr != nullptr)
            return int(*m_data.m_float_ptr);
        else
            opps();
    }
    else if(typeid(double).name()==id)
    {//double                  m_double;		//19
        return int(m_data.m_double);
    }
    else if(typeid(const double*).name()==id)
    {//const double*           m_double_ptr;	//20
        if(m_data.m_double_ptr != nullptr)
            return int(*m_data.m_double_ptr);
        else
            opps();
    }
    else if(typeid(const std::string*).name()==id)
    {//const std::string*      m_string_ptr;	//21
        if(m_data.m_string_ptr != nullptr)
        {
            return int(convert_string_to_integer(m_data.m_string_ptr));
        }
        else
            opps();

    }
    else if(typeid(const Value*).name()==id)
    {//const Value*            m_value_ptr;     //22
        //return convert_value_to_string(m_data.m_value_ptr);

        if(m_data.m_value_ptr != nullptr)
            return m_data.m_value_ptr->asInt();
        else
            opps();
    }
    else if(typeid(const ColorCode).name()==id)
    {//const ColorCode         m_color_code;	//23
    	return (int)m_data.m_color_code;
    }
    else
    {
        opps();
    }
    return 0;//消除编译返回值缺失警告
}
long Value::asLong(void) const
{
    std::string id = get_cur_union_member_type_id(m_index);

    if(typeid(bool).name()==id)
    {//bool                    m_bool;          //0
        if(m_data.m_bool)
            return long(1);
        else
            return long(0);
    }
    else if(typeid(char).name()==id)
    {//char                    m_char;          //1
        return long(m_data.m_char);
    }
    else if(typeid(const char*).name()==id)
    {//const char*             m_char_ptr;      //2
        if(m_data.m_char_ptr != nullptr)
        {
            std::string tmp(m_data.m_char_ptr);
            return long(convert_string_to_integer(&tmp));
        }
        else
            opps();
    }
    else if(typeid(unsigned char).name()==id)
    {//unsigned char           m_uchar;         //3
        return long(m_data.m_uchar);
    }
    else if(typeid(const unsigned char*).name()==id)
    {//const unsigned char*    m_uchar_ptr;     //4
        if(m_data.m_uchar_ptr != nullptr)
            return long(*m_data.m_uchar_ptr);
        else
            opps();
    }
    else if(typeid(short).name()==id)
    {//short                   m_short;         //5
        return long(m_data.m_short);
    }
    else if(typeid(const short*).name()==id)
    {//const short*            m_short_ptr;     //6
        if(m_data.m_short_ptr != nullptr)
            return long(*m_data.m_short_ptr);
        else
            opps();
    }
    else if(typeid(unsigned short).name()==id)
    {//unsigned short          m_ushort;		//7
        return long(m_data.m_ushort);
    }
    else if(typeid(const unsigned short*).name()==id)
    {//const unsigned short*   m_ushort_ptr;	//8
        if(m_data.m_ushort_ptr != nullptr)
            return long(*m_data.m_ushort_ptr);
        else
            opps();
    }
    else if(typeid(int).name()==id)
    {//int                     m_int;           //9
        return long(m_data.m_int);
    }
    else if(typeid(const int*).name()==id)
    {//const int*              m_int_ptr;       //10
        if(m_data.m_int_ptr != nullptr)
            return long(*m_data.m_int_ptr);
        else
            opps();
    }
    else if(typeid(unsigned int).name()==id)
    {//unsigned int            m_uint;          //11
        return long(m_data.m_uint);
    }
    else if(typeid(const unsigned int*).name()==id)
    {//const unsigned int*     m_uint_ptr;      //12
        if(m_data.m_uint_ptr != nullptr)
            return long(*m_data.m_uint_ptr);
        else
            opps();
    }
    else if(typeid(long).name()==id)
    {//long                    m_long;          //13
        return long(m_data.m_long);
    }
    else if(typeid(const long*).name()==id)
    {//const long*             m_long_ptr;      //14
        if(m_data.m_long_ptr != nullptr)
            return long(*m_data.m_long_ptr);
        else
            opps();
    }
    else if(typeid(unsigned long).name()==id)
    {//unsigned long           m_ulong;         //15
        return long(m_data.m_ulong);
    }
    else if(typeid(const unsigned long*).name()==id)
    {//const unsigned long*    m_ulong_ptr;     //16
        if(m_data.m_ulong_ptr != nullptr)
            return long(*m_data.m_ulong_ptr);
        else
            opps();
    }
    else if(typeid(float).name()==id)
    {//float                   m_float;         //17
        return long(m_data.m_float);
    }
    else if(typeid(const float*).name()==id)
    {//const float*            m_float_ptr;     //18
        if(m_data.m_float_ptr != nullptr)
            return long(*m_data.m_float_ptr);
        else
            opps();
    }
    else if(typeid(double).name()==id)
    {//double                  m_double;		//19
        return long(m_data.m_double);
    }
    else if(typeid(const double*).name()==id)
    {//const double*           m_double_ptr;	//20
        if(m_data.m_double_ptr != nullptr)
            return long(*m_data.m_double_ptr);
        else
            opps();
    }
    else if(typeid(const std::string*).name()==id)
    {//const std::string*      m_string_ptr;	//21
        if(m_data.m_string_ptr != nullptr)
        {
            return long(convert_string_to_integer(m_data.m_string_ptr));
        }
        else
            opps();

    }
    else if(typeid(const Value*).name()==id)
    {//const Value*            m_value_ptr;     //22
        //return convert_value_to_string(m_data.m_value_ptr);

        if(m_data.m_value_ptr != nullptr)
            return m_data.m_value_ptr->asLong();
        else
            opps();
    }
    else if(typeid(const ColorCode).name()==id)
    {//const ColorCode         m_color_code;	//23
    	return (long)m_data.m_color_code;
    }
    else
    {
        opps();
    }
    return 0;//消除编译返回值缺失警告
}
float Value::asFloat(void) const
{
    std::string id = get_cur_union_member_type_id(m_index);

    if(typeid(bool).name()==id)
    {//bool                    m_bool;          //0
        if(m_data.m_bool)
            return float(1);
        else
            return float(0);
    }
    else if(typeid(char).name()==id)
    {//char                    m_char;          //1
        return float(m_data.m_char);
    }
    else if(typeid(const char*).name()==id)
    {//const char*             m_char_ptr;      //2
        if(m_data.m_char_ptr != nullptr)
        {
            std::string tmp(m_data.m_char_ptr);
            return float(convert_string_to_integer(&tmp));
        }
        else
            opps();
    }
    else if(typeid(unsigned char).name()==id)
    {//unsigned char           m_uchar;         //3
        return float(m_data.m_uchar);
    }
    else if(typeid(const unsigned char*).name()==id)
    {//const unsigned char*    m_uchar_ptr;     //4
        if(m_data.m_uchar_ptr != nullptr)
            return float(*m_data.m_uchar_ptr);
        else
            opps();
    }
    else if(typeid(short).name()==id)
    {//short                   m_short;         //5
        return float(m_data.m_short);
    }
    else if(typeid(const short*).name()==id)
    {//const short*            m_short_ptr;     //6
        if(m_data.m_short_ptr != nullptr)
            return float(*m_data.m_short_ptr);
        else
            opps();
    }
    else if(typeid(unsigned short).name()==id)
    {//unsigned short          m_ushort;		//7
        return float(m_data.m_ushort);
    }
    else if(typeid(const unsigned short*).name()==id)
    {//const unsigned short*   m_ushort_ptr;	//8
        if(m_data.m_ushort_ptr != nullptr)
            return float(*m_data.m_ushort_ptr);
        else
            opps();
    }
    else if(typeid(int).name()==id)
    {//int                     m_int;           //9
        return float(m_data.m_int);
    }
    else if(typeid(const int*).name()==id)
    {//const int*              m_int_ptr;       //10
        if(m_data.m_int_ptr != nullptr)
            return float(*m_data.m_int_ptr);
        else
            opps();
    }
    else if(typeid(unsigned int).name()==id)
    {//unsigned int            m_uint;          //11
        return float(m_data.m_uint);
    }
    else if(typeid(const unsigned int*).name()==id)
    {//const unsigned int*     m_uint_ptr;      //12
        if(m_data.m_uint_ptr != nullptr)
            return float(*m_data.m_uint_ptr);
        else
            opps();
    }
    else if(typeid(long).name()==id)
    {//long                    m_long;          //13
        return float(m_data.m_long);
    }
    else if(typeid(const long*).name()==id)
    {//const long*             m_long_ptr;      //14
        if(m_data.m_long_ptr != nullptr)
            return float(*m_data.m_long_ptr);
        else
            opps();
    }
    else if(typeid(unsigned long).name()==id)
    {//unsigned long           m_ulong;         //15
        return float(m_data.m_ulong);
    }
    else if(typeid(const unsigned long*).name()==id)
    {//const unsigned long*    m_ulong_ptr;     //16
        if(m_data.m_ulong_ptr != nullptr)
            return float(*m_data.m_ulong_ptr);
        else
            opps();
    }
    else if(typeid(float).name()==id)
    {//float                   m_float;         //17
        return float(m_data.m_float);
    }
    else if(typeid(const float*).name()==id)
    {//const float*            m_float_ptr;     //18
        if(m_data.m_float_ptr != nullptr)
            return float(*m_data.m_float_ptr);
        else
            opps();
    }
    else if(typeid(double).name()==id)
    {//double                  m_double;		//19
        return float(m_data.m_double);
    }
    else if(typeid(const double*).name()==id)
    {//const double*           m_double_ptr;	//20
        if(m_data.m_double_ptr != nullptr)
            return float(*m_data.m_double_ptr);
        else
            opps();
    }
    else if(typeid(const std::string*).name()==id)
    {//const std::string*      m_string_ptr;	//21
        if(m_data.m_string_ptr != nullptr)
        {
            return float(convert_string_to_integer(m_data.m_string_ptr));
        }
        else
            opps();

    }
    else if(typeid(const Value*).name()==id)
    {//const Value*            m_value_ptr;     //22
        //return convert_value_to_string(m_data.m_value_ptr);

        if(m_data.m_value_ptr != nullptr)
            return m_data.m_value_ptr->asFloat();
        else
            opps();
    }
    else if(typeid(const ColorCode).name()==id)
    {//const ColorCode         m_color_code;	//23
    	return (float)m_data.m_color_code;
    }
    else
    {
        opps();
    }
    return 0;//消除编译返回值缺失警告
}
double Value::asDouble(void) const
{
    std::string id = get_cur_union_member_type_id(m_index);

    if(typeid(bool).name()==id)
    {//bool                    m_bool;          //0
        if(m_data.m_bool)
            return double(1);
        else
            return double(0);
    }
    else if(typeid(char).name()==id)
    {//char                    m_char;          //1
        return double(m_data.m_char);
    }
    else if(typeid(const char*).name()==id)
    {//const char*             m_char_ptr;      //2
        if(m_data.m_char_ptr != nullptr)
        {
            std::string tmp(m_data.m_char_ptr);
            return double(convert_string_to_integer(&tmp));
        }
        else
            opps();
    }
    else if(typeid(unsigned char).name()==id)
    {//unsigned char           m_uchar;         //3
        return double(m_data.m_uchar);
    }
    else if(typeid(const unsigned char*).name()==id)
    {//const unsigned char*    m_uchar_ptr;     //4
        if(m_data.m_uchar_ptr != nullptr)
            return double(*m_data.m_uchar_ptr);
        else
            opps();
    }
    else if(typeid(short).name()==id)
    {//short                   m_short;         //5
        return double(m_data.m_short);
    }
    else if(typeid(const short*).name()==id)
    {//const short*            m_short_ptr;     //6
        if(m_data.m_short_ptr != nullptr)
            return double(*m_data.m_short_ptr);
        else
            opps();
    }
    else if(typeid(unsigned short).name()==id)
    {//unsigned short          m_ushort;		//7
        return double(m_data.m_ushort);
    }
    else if(typeid(const unsigned short*).name()==id)
    {//const unsigned short*   m_ushort_ptr;	//8
        if(m_data.m_ushort_ptr != nullptr)
            return double(*m_data.m_ushort_ptr);
        else
            opps();
    }
    else if(typeid(int).name()==id)
    {//int                     m_int;           //9
        return double(m_data.m_int);
    }
    else if(typeid(const int*).name()==id)
    {//const int*              m_int_ptr;       //10
        if(m_data.m_int_ptr != nullptr)
            return double(*m_data.m_int_ptr);
        else
            opps();
    }
    else if(typeid(unsigned int).name()==id)
    {//unsigned int            m_uint;          //11
        return double(m_data.m_uint);
    }
    else if(typeid(const unsigned int*).name()==id)
    {//const unsigned int*     m_uint_ptr;      //12
        if(m_data.m_uint_ptr != nullptr)
            return double(*m_data.m_uint_ptr);
        else
            opps();
    }
    else if(typeid(long).name()==id)
    {//long                    m_long;          //13
        return double(m_data.m_long);
    }
    else if(typeid(const long*).name()==id)
    {//const long*             m_long_ptr;      //14
        if(m_data.m_long_ptr != nullptr)
            return double(*m_data.m_long_ptr);
        else
            opps();
    }
    else if(typeid(unsigned long).name()==id)
    {//unsigned long           m_ulong;         //15
        return double(m_data.m_ulong);
    }
    else if(typeid(const unsigned long*).name()==id)
    {//const unsigned long*    m_ulong_ptr;     //16
        if(m_data.m_ulong_ptr != nullptr)
            return double(*m_data.m_ulong_ptr);
        else
            opps();
    }
    else if(typeid(float).name()==id)
    {//float                   m_float;         //17
        return double(m_data.m_float);
    }
    else if(typeid(const float*).name()==id)
    {//const float*            m_float_ptr;     //18
        if(m_data.m_float_ptr != nullptr)
            return double(*m_data.m_float_ptr);
        else
            opps();
    }
    else if(typeid(double).name()==id)
    {//double                  m_double;		//19
        return double(m_data.m_double);
    }
    else if(typeid(const double*).name()==id)
    {//const double*           m_double_ptr;	//20
        if(m_data.m_double_ptr != nullptr)
            return double(*m_data.m_double_ptr);
        else
            opps();
    }
    else if(typeid(const std::string*).name()==id)
    {//const std::string*      m_string_ptr;	//21
        if(m_data.m_string_ptr != nullptr)
        {
            return double(convert_string_to_integer(m_data.m_string_ptr));
        }
        else
            opps();

    }
    else if(typeid(const Value*).name()==id)
    {//const Value*            m_value_ptr;     //22
        //return convert_value_to_string(m_data.m_value_ptr);

        if(m_data.m_value_ptr != nullptr)
            return m_data.m_value_ptr->asDouble();
        else
            opps();
    }
    else if(typeid(const ColorCode).name()==id)
    {//const ColorCode         m_color_code;	//23
    	return (double)m_data.m_color_code;
    }
    else
    {
        opps();
    }
    return 0;//消除编译返回值缺失警告
}
std::string Value::get_cur_union_member_name(const unsigned char uc) const
{
    switch (uc)
    {
    case 0 : return "m_bool";         //0
    case 1 : return "m_char";         //1
    case 2 : return "m_char_ptr";     //2
    case 3 : return "m_uchar";		  //3
    case 4 : return "m_uchar_ptr";	  //4
    case 5 : return "m_short";		  //5
    case 6 : return "m_short_ptr";	  //6
    case 7 : return "m_ushort";		  //7
    case 8 : return "m_ushort_ptr";	  //8
    case 9 : return "m_int";          //9
    case 10: return "m_int_ptr";      //10
    case 11: return "m_uint";         //11
    case 12: return "m_uint_ptr";     //12
    case 13: return "m_long";         //13
    case 14: return "m_long_ptr";     //14
    case 15: return "m_ulong";		  //15
    case 16: return "m_ulong_ptr";	  //16
    case 17: return "m_float";		  //17
    case 18: return "m_float_ptr";	  //18
    case 19: return "m_double";		  //19
    case 20: return "m_double_ptr";	  //20
    case 21: return "m_string_ptr";	  //21
    case 22: return "m_value_ptr";	  //22
    case 23: return "m_color_code";	  //23
    }
    return "";//消除编译返回值缺失警告
}
std::string Value::get_cur_union_member_type(const unsigned char uc) const
{
    switch (uc)
    {
    case 0 : return "bool";                     //0
    case 1 : return "char";                     //1
    case 2 : return "const char*";              //2
    case 3 : return "unsigned char";            //3
    case 4 : return "const unsigned char*";     //4
    case 5 : return "short";                    //5
    case 6 : return "const short*";             //6
    case 7 : return "unsigned short";           //7
    case 8 : return "const unsigned short*";	//8
    case 9 : return "int";                      //9
    case 10: return "const int*";               //10
    case 11: return "unsigned int";             //11
    case 12: return "const unsigned int*";      //12
    case 13: return "long";                     //13
    case 14: return "const long*";              //14
    case 15: return "unsigned long";            //15
    case 16: return "const unsigned long*";     //16
    case 17: return "float";                    //17
    case 18: return "const float* ";            //18
    case 19: return "double";                   //19
    case 20: return "const double*";            //20
    case 21: return "const std::string*";       //21
    case 22: return "const Value*";             //22
    case 23: return "const ColorCode";          //23
    }
    return "";//消除编译返回值缺失警告
}
std::string Value::get_cur_union_member_type_id(const unsigned char uc) const
{
    switch (uc)
    {
    case 0 : return typeid(bool).name();                     //0
    case 1 : return typeid(char).name();                     //1
    case 2 : return typeid(const char*).name();              //2
    case 3 : return typeid(unsigned char).name();            //3
    case 4 : return typeid(const unsigned char*).name();     //4
    case 5 : return typeid(short).name();                    //5
    case 6 : return typeid(const short*).name();             //6
    case 7 : return typeid(unsigned short).name();           //7
    case 8 : return typeid(const unsigned short*).name();	 //8
    case 9 : return typeid(int).name();                      //9
    case 10: return typeid(const int*).name();               //10
    case 11: return typeid(unsigned int).name();             //11
    case 12: return typeid(const unsigned int*).name();      //12
    case 13: return typeid(long).name();                     //13
    case 14: return typeid(const long*).name();              //14
    case 15: return typeid(unsigned long).name();            //15
    case 16: return typeid(const unsigned long*).name();     //16
    case 17: return typeid(float).name();                    //17
    case 18: return typeid(const float*).name();             //18
    case 19: return typeid(double).name();                   //19
    case 20: return typeid(const double*).name();            //20
    case 21: return typeid(const std::string*).name();       //21
    case 22: return typeid(const Value*).name();             //22
    case 23: return typeid(const ColorCode).name();          //23
    }
    return "";//消除编译返回值缺失警告
}
void Value::opps(void) const
{
    std::cerr << "libwlc.so/libwlc.a: Value: Crashed. exit(1).\n";
    exit(1);
}
void Value::opps(std::string &msg) const
{
    std::cerr << "libwlc.so/libwlc.a: Value: "+msg << " exit(1).\n";
    exit(1);
}
std::string Value::convert_value_to_string(const Value *vp)
{
    return vp->asString();
}
long Value::convert_string_to_integer(const std::string *sp) const
{
    const std::string &str = *sp;
    bool flag;
    size_t str_beg;
    size_t str_end;//超尾
    //size_t str_len;
    switch(str[0])
    {
    case '-':
        flag = false;//代表负数
        str_beg = 1;
        break;
    case '+':
        flag = true;//代表正数
        str_beg = 1;
        break;
    default:
        flag = true;//代表正数
        str_beg = 0;
    }
    /////////////////////////////////////////////
    char perfix_1 = str[str_beg];
    char perfix_2 = str[str_beg+1];
    /////////////////////////////////////////////
    size_t str_dot = sp->find('.');
    if(str_dot == std::string::npos)
    {
        str_end = sp->length();
    }
    else
    {
        str_end = str_dot;
    }
    /////////////////////////////////////////////
    switch(perfix_1)
    {
        case '0':
        {
            if(perfix_2 == 'x' || perfix_2 == 'X')
            {// 十六进制
                str_beg = str_beg + 2;
                //str_len = str_end - str_beg;
                long num = 0;
                size_t p = 0;p--;
                for(size_t k=str_end-1,i=1; k<p&&k>=str_beg; k--)
                {
                    p = k;
                    char cur_char = str[k];
                    bool set_num = cur_char >= '0' && cur_char <= '9';
                    bool set_all = cur_char >= 'a' && cur_char <= 'f';
                    bool set_alu = cur_char >= 'A' && cur_char <= 'F';
                    if(set_num)
                    {
                        num += (cur_char - '0')*i;
                        i = i*16;
                    }
                    else if(set_all)
                    {
                        num += (cur_char - 'a' + 10)*i;
                        i = i*16;
                    }
                    else if(set_alu)
                    {
                        num += (cur_char - 'A' + 10)*i;
                        i = i*16;
                    }
                    else
                    {
                        std::string msg = "[" + str + "](16) can't convert to integer." ;
                        opps(msg);
                    }
                }
                if(!flag)
                {
                    num = -num;
                }
                return num;
            }
            else
            {// 八进制
                str_beg = str_beg + 1;
                //str_len = str_end - str_beg;
                long num = 0;
                size_t p = 0;p--;
                for(size_t k=str_end-1,i=1; k<p&&k>=str_beg; k--)
                {
                    p = k;
                    char cur_char = str[k];
                    if(cur_char >= '0' && cur_char <= '7')
                    {
                        num += (cur_char - '0')*i;
                        i = i*8;
                    }
                    else
                    {
                        std::string msg = "[" + str + "](8) can't convert to integer." ;
                        opps(msg);
                    }
                }
                if(!flag)
                {
                    num = -num;
                }
                return num;
            }
        }
        default:
        {// 十进制
            //str_len = str_end - str_beg;
            long num = 0;
            size_t p = 0;p--;
            for(size_t k=str_end-1,i=1; k<p&&k>=str_beg; k--)
            {
                p = k;
                char cur_char = str[k];
                if(cur_char >= '0' && cur_char <= '9')
                {
                    num += (cur_char - '0')*i;
                    i = i*10;
                }
                else
                {
                    std::string msg = "[" + str + "](10) can't convert to integer." ;
                    opps(msg);
                }
            }
            if(!flag)
            {
                num = -num;
            }
            return num;
        }
    }
}
double Value::convert_string_to_float(const std::string *sp) const
{
    size_t str_dot = sp->find('.');
    if(str_dot == std::string::npos)
    {
        return double(convert_string_to_integer(sp));
    }

    long integer_part_val = convert_string_to_integer(sp);//整数部分
    bool flag;
    if(integer_part_val >= 0)
    {
        flag = true;//正数
    }
    else
    {
        flag = false;//负数
    }

    const std::string &str = *sp;
    if(str[0] == '+' || str[0] == '-')
    {
        if(str[1] == '0')
        {
            if(str[2] == 'x' || str[2] == 'X')
            {// 十六进制
                goto label_1;
            }
            else
            {// 八进制
                goto label_2;
            }
        }
        else
        {// 十进制
            goto label_3;
        }
    }
    else
    {
        if(str[0] == '0')
        {
            if(str[1] == 'x' || str[1] == 'X')
            {// 十六进制
                label_1:
                double num = 0;
                double i = 0.0625;
                for(size_t k=str_dot+1; k<sp->length(); k++)
                {
                    char cur_char = str[k];
                    bool set_num = cur_char >= '0' && cur_char <= '9';
                    bool set_all = cur_char >= 'a' && cur_char <= 'f';
                    bool set_alu = cur_char >= 'A' && cur_char <= 'F';
                    if(set_num)
                    {
                        num += (cur_char - '0')*i;
                        i = i*0.0625;
                    }
                    else if(set_all)
                    {
                        num += (cur_char - 'a' + 10)*i;
                        i = i*0.0625;
                    }
                    else if(set_alu)
                    {
                        num += (cur_char - 'A' + 10)*i;
                        i = i*0.0625;
                    }
                    else
                    {
                        std::string msg = "[" + str + "](16) can't convert to floating-integer." ;
                        opps(msg);
                    }
                }
                if(!flag)
                {
                    num = -num;
                }
                #ifdef LIB_WLC_DEBUG_VALUE_INFO_SHOW
                std::cout << "整数部分" << integer_part_val << std::endl;
                std::cout << "小数部分" << num << std::endl;
                #endif
                return (num+integer_part_val);
            }
            else
            {// 八进制
                label_2:
                double num = 0;
                double i = 0.125;
                for(size_t k=str_dot+1; k<sp->length(); k++)
                {
                    char cur_char = str[k];
                    if(cur_char >= '0' && cur_char <= '7')
                    {
                        num += (cur_char - '0')*i;
                        i = i*0.125;
                    }
                    else
                    {
                        std::string msg = "[" + str + "](8) can't convert to floating-integer." ;
                        opps(msg);
                    }
                }
                if(!flag)
                {
                    num = -num;
                }
                #ifdef LIB_WLC_DEBUG_VALUE_INFO_SHOW
                std::cout << "整数部分" << integer_part_val << std::endl;
                std::cout << "小数部分" << num << std::endl;
                #endif
                return (num+integer_part_val);
            }
        }
        else
        {// 十进制
            label_3:
            double num = 0;
            double i = 0.1;
            for(size_t k=str_dot+1; k<sp->length(); k++)
            {
                char cur_char = str[k];
                if(cur_char >= '0' && cur_char <= '9')
                {
                    num += (cur_char - '0')*i;
                    i = i*0.1;
                }
                else
                {
                    std::string msg = "[" + str + "](10) can't convert to floating-integer." ;
                    opps(msg);
                }
            }
            if(!flag)
            {
                num = -num;
            }
            #ifdef LIB_WLC_DEBUG_VALUE_INFO_SHOW
            std::cout << "整数部分" << integer_part_val << std::endl;
            std::cout << "小数部分" << num << std::endl;
            #endif
            return (num+integer_part_val);
        }
    }
}
/////////////////////////////////////////////////
}
