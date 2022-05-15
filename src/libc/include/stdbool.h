#ifndef _STDBOOL_H
#define _STDBOOL_H

#ifndef __cplusplus

#define bool  _Bool
#define false 0
#define true  1

#else /* __cplusplus */

#define _Bool bool

#endif /* __cplusplus */

#define __bool_true_false_are_defined 1

#endif /* _STDBOOL_H */
