/*************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/
#ifndef ERRNO_H
#define ERRNO_H

#define ERR_NOR 	1	/* read not allowed for file */
#define ERR_NOW 	2	/* write not allowed for file */
#define ERR_IO		3	/* io error */
#define EDOM		4	/* domain error */
#define ERANGE		5	/* range error */
extern int errno;
#endif
