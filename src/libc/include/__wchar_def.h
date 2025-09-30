#ifndef _WCHAR_DEF_H
#define _WCHAR_DEF_H

#include <cdefs.h>

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif /* __cplusplus */
#endif /* _WCHAR_T_DEFINED */

#ifndef _WINT_T_DEFINED
#define _WINT_T_DEFINED
typedef __WINT_TYPE__ wint_t;
#endif /* _WINT_T_DEFINED */

#ifndef _WCHAR_LIMITS_DEFINED
#define _WCHAR_LIMITS_DEFINED
#define           WCHAR_MIN                      (~__WCHAR_MAX__)
#define           WCHAR_MAX                        __WCHAR_MAX__
#define           WCHAR_WIDTH                      __WCHAR_WIDTH__
#endif /* _WCHAR_LIMITS_DEFINED */

#ifndef _WINT_LIMITS_DEFINED
#define _WINT_LIMITS_DEFINED
#define            WINT_MIN                       (~__WINT_MAX__)
#define            WINT_MAX                         __WINT_MAX__
#define            WINT_WIDTH                       __WINT_WIDTH__
#endif /* _WINT_LIMITS_DEFINED */

#ifndef WEOF
#define WEOF -1
#endif

#endif /* _WCHAR_DEF_H */
