#ifndef LIB_WLC_VALUE_H
#define LIB_WLC_VALUE_H
#include <iostream>
#include <typeinfo>
#include "colorize.h"
#include "debug.h"

namespace libwlc
{
/////////////////////////////////////////////////
class Value
{
public:
    explicit Value(const bool v):m_data(v)
    {
        m_index = 0;
    }
	
    explicit Value(const char v):m_data(v)
    {
        m_index = 1;
    }
    explicit Value(const char *ptr):m_data(ptr)
    {
        m_index = 2;
    }
    explicit Value(const unsigned char v):m_data(v)
    {
        m_index = 3;
    }
    explicit Value(const unsigned char *ptr):m_data(ptr)
    {
        m_index = 4;
    }
	
    explicit Value(const short v):m_data(v)
    {
        m_index = 5;
    }
    explicit Value(const short *ptr):m_data(ptr)
    {
        m_index = 6;
    }
    explicit Value(const unsigned short v):m_data(v)
    {
        m_index = 7;
    }
    explicit Value(const unsigned short *ptr):m_data(ptr)
    {
        m_index = 8;
    }
	
    explicit Value(const int v):m_data(v)
    {
        m_index = 9;
    }
    explicit Value(const int *ptr):m_data(ptr)
    {
        m_index = 10;
    }
    explicit Value(const unsigned int v):m_data(v)
    {
        m_index = 11;
    }
    explicit Value(const unsigned int *ptr):m_data(ptr)
    {
        m_index = 12;
    }
	
    explicit Value(const long v):m_data(v)
    {
        m_index = 13;
    }
    explicit Value(const long *ptr):m_data(ptr)
    {
        m_index = 14;
    }
    explicit Value(const unsigned long v):m_data(v)
    {
        m_index = 15;
    }
    explicit Value(const unsigned long *ptr):m_data(ptr)
    {
        m_index = 16;
    }
	
    explicit Value(const float v):m_data(v)
    {
        m_index = 17;
    }
    explicit Value(const float *ptr):m_data(ptr)
    {
        m_index = 18;
    }
	
    explicit Value(const double v):m_data(v)
    {
        m_index = 19;
    }
    explicit Value(const double *ptr):m_data(ptr)
    {
        m_index = 20;
    }
	
    explicit Value(const std::string &v):m_data(&v)
    {
        m_index = 21;
    }
    explicit Value(const std::string *ptr):m_data(ptr)
    {
        m_index = 21;
    }
	
    explicit Value(const Value &v):m_data(&v)
    {
        m_index = 22;
    }
    explicit Value(const Value *ptr):m_data(ptr)
    {
        m_index = 22;
    }
    explicit Value(const ColorCode cc):m_data(cc)
    {
        m_index = 23;
    }
    ///////////////////////////////////////////////////////
    bool        asBool(void) const;
    std::string asString(void) const;
    short       asShort(void) const;
    int         asInt(void) const;
    long        asLong(void) const;
    float       asFloat(void) const;
    double      asDouble(void) const;
    ///////////////////////////////////////////////////////
private:
    static const unsigned int size = 256;
    ///////////////////////////////////////////////////////
    std::string get_cur_union_member_name(const unsigned char uc) const;
    std::string get_cur_union_member_type(const unsigned char uc) const;
    std::string get_cur_union_member_type_id(const unsigned char uc) const;
    void opps(void) const;
    void opps(std::string &msg) const;
    long convert_string_to_integer(const std::string *sp) const;
    double convert_string_to_float(const std::string *sp) const;
    ///////////////////////////////////////////////////////
    static std::string convert_value_to_string(const Value *vp);
    ///////////////////////////////////////////////////////
	union __libwlc_value_data__
    {
    public:
        /////////////////////////////////////////////
        __libwlc_value_data__(const bool v):m_bool(v) {}
        __libwlc_value_data__(const char v):m_char(v) {}
        __libwlc_value_data__(const char *ptr):m_char_ptr(ptr) {}
        __libwlc_value_data__(const unsigned char v):m_uchar(v) {}
        __libwlc_value_data__(const unsigned char *ptr):m_uchar_ptr(ptr) {}
        __libwlc_value_data__(const short v):m_short(v) {}
        __libwlc_value_data__(const short *ptr):m_short_ptr(ptr) {}
        __libwlc_value_data__(const unsigned short v):m_ushort(v) {}
        __libwlc_value_data__(const unsigned short *ptr):m_ushort_ptr(ptr) {}
        __libwlc_value_data__(const int v):m_int(v) {}
        __libwlc_value_data__(const int *ptr):m_int_ptr(ptr) {}
        __libwlc_value_data__(const unsigned int v):m_uint(v) {}
        __libwlc_value_data__(const unsigned int *ptr):m_uint_ptr(ptr) {}
        __libwlc_value_data__(const long v):m_long(v) {}
        __libwlc_value_data__(const long *ptr):m_long_ptr(ptr) {}
        __libwlc_value_data__(const unsigned long v):m_ulong(v) {}
        __libwlc_value_data__(const unsigned long *ptr):m_ulong_ptr(ptr) {}
        __libwlc_value_data__(const float v):m_float(v) {}
        __libwlc_value_data__(const float *ptr):m_float_ptr(ptr) {}
        __libwlc_value_data__(const double v):m_double(v) {}
        __libwlc_value_data__(const double *ptr):m_double_ptr(ptr) {}
        __libwlc_value_data__(const std::string *ptr):m_string_ptr(ptr) {}
        __libwlc_value_data__(const Value *ptr):m_value_ptr(ptr) {}
        __libwlc_value_data__(const ColorCode cc):m_color_code(cc) {}
        /////////////////////////////////////////////
        bool                    m_bool;         //0
        char                    m_char;         //1
        const char*             m_char_ptr;     //2
        unsigned char           m_uchar;	//3
        const unsigned char*    m_uchar_ptr;	//4
        short                   m_short;	//5
        const short*            m_short_ptr;	//6
        unsigned short          m_ushort;	//7
        const unsigned short*   m_ushort_ptr;	//8
        int                     m_int;          //9
        const int*              m_int_ptr;      //10
        unsigned int            m_uint;         //11
        const unsigned int*     m_uint_ptr;     //12
        long                    m_long;         //13
        const long*             m_long_ptr;     //14
        unsigned long           m_ulong;	//15
        const unsigned long*    m_ulong_ptr;	//16
        float                   m_float;	//17
        const float*            m_float_ptr;	//18
        double                  m_double;	//19
        const double*           m_double_ptr;	//20
        const std::string*      m_string_ptr;	//21
        const Value*            m_value_ptr;	//22
        const ColorCode         m_color_code;	//23
	};
    const union __libwlc_value_data__   m_data;
    unsigned char				        m_index;
};
/////////////////////////////////////////////////
}
#endif // LIB_WLC_VALUE_H
