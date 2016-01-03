#ifndef LIB_WLC_DEBUG_H
#define LIB_WLC_DEBUG_H
namespace libwlc
{
#ifdef __cplusplus
#define C_LANGUAGE_BEGIN extern "C" {
#define C_LANGUAGE_END  }
#else
#define C_LANGUAGE_BEGIN
#define C_LANGUAGE_END
#endif//__cplusplus
/////////////////////////////////////////////////
//#define LIB_WLC_DEBUG				/* 库 libwlc 调试总开关 */
/////////////////////////////////////////////////
#ifdef LIB_WLC_DEBUG
#define LIB_WLC_DEBUG_VALUE			/* 类 Value 调试总开关  */
#endif
/***********************************************/
#ifdef LIB_WLC_DEBUG_VALUE
#define LIB_WLC_DEBUG_VALUE_INFO_SHOW
#endif
/***********************************************/
}
#endif // LIB_WLC_DEBUG_H
