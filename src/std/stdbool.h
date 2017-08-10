/*
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *  Modified by Matt "MateoConLechuga" Waltz for TI84+CE platform
 */
#ifndef STDBOOL_H
#define STDBOOL_H

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined

#ifndef __cplusplus

typedef unsigned char bool;

#define _Bool   bool
#define false   0
#define true    1

#endif

#endif
#endif
