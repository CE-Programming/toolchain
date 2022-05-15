#ifndef _WCHAR_H
#define _WCHAR_H

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif /* __cplusplus */
#endif /* _WCHAR_T_DEFINED */

#ifndef _WCHAR_LIMITS_DEFINED
#define _WCHAR_LIMITS_DEFINED
#define WCHAR_WIDTH __WCHAR_WIDTH__
#define WCHAR_MIN (~__WCHAR_MAX__)
#define WCHAR_MAX   __WCHAR_MAX__
#endif

#define WEOF -1

#endif /* _WCHAR_H */
