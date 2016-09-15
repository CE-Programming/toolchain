This file is not used on the Acclaim.
The file was created to resolve CR13000, moving errno from the startup script to
the runtime library, so as not to waste two bytes for users who don't need errno.  We decided to back this out on the Acclaim since the Acclaim has far more memory to waste than some of our other processors, and because we were uncertain
how the Acclaim's runtime libraries are organized.
/*************************************************
 *  Copyright (C) 2009 by  Zilog, Inc.
 *  All Rights Reserved
 *************************************************/

#include <errno.h>

/*************************************************
*
* errno - error indicator used by many standard library functions
*
*************************************************/
int errno;
