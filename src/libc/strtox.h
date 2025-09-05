/*
 * Copyright (C) 2015-2025 CE Programming
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * MODIFICATIONS
 *      Made generic interface
 *      Add back in errno range handling
 *        
 */
/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/*      Copyright (c) 1995 NeXT Computer, Inc.  All rights reserved.
 *
 * strol.c - The functions strtol() & strtoul() are exported as public API
 *           via the header file ~driverkit/generalFuncs.h
 *
 * HISTORY
 * 25-Oct-1995    Dean Reece at NeXT
 *      Created based on BSD4.4's strtol.c & strtoul.c.
 *      Removed dependency on _ctype_ by static versions of isupper()...
 *      Added support for "0b101..." binary constants.
 *      Commented out references to errno.
 */

/*-
 * Copyright (c) 1990, 1993
 *    The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the University of
 *    California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifdef STRTOX_TYPE
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#if !STRTOX_SIGNED
unsigned
#endif
STRTOX_TYPE STRTOX_NAME(const char *nptr, char **endptr, int base)
{
    unsigned STRTOX_TYPE acc;
    unsigned STRTOX_TYPE cutoff;
    unsigned char cutlim;
    unsigned char c;
    unsigned char b;
    const char *s;
    bool neg;
    char any;

    if (base < 0 || base > 36)
    {
        if (endptr)
        {
            *endptr = (char *)nptr;
        }

        return 0;
    }

    b = base;
    s = nptr;
    neg = false;

    do
    {
        c = *s++;
    } while (isspace(c));

    if (c == '-')
    {
        neg = true;
        c = *s++;
    }
    else if (c == '+')
    {
        c = *s++;
    }

    if ((b == 0 || b == 16) && c == '0' && (*s == 'x' || *s == 'X'))
    {
        c = s[1];
        s += 2;
        b = 16;
    }
    else if ((b == 0 || b == 2) && c == '0' && (*s == 'b' || *s == 'B'))
    {
        c = s[1];
        s += 2;
        b = 2;
    }

    if (b == 0)
    {
        b = c == '0' ? 8 : 10;
    }

#if STRTOX_SIGNED
    cutoff = neg ? -(unsigned STRTOX_TYPE)(STRTOX_MIN) : STRTOX_MAX;
    cutlim = cutoff % b;
    cutoff /= b;
#else
    cutoff = STRTOX_MAX / b;
    cutlim = STRTOX_MAX % b;
#endif

    for (acc = 0, any = 0;; c = *s++)
    {
        if (isdigit(c))
        {
            c -= '0';
        }
        else if (isalpha(c))
        {
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        }
        else
        {
            break;
        }
        if (c >= b)
        {
            break;
        }

        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
        {
            any = -1;
        }
        else
        {
            any = 1;
            acc *= b;
            acc += c;
        }
    }

    if (any < 0)
    {
        acc = neg ? STRTOX_MIN : STRTOX_MAX;
        errno = ERANGE;
    }
    else if (neg)
    {
        acc = -acc;
    }

    if (endptr)
    {
        *endptr = (char *)(any ? s - 1 : nptr);
    }

    return acc;
}
#endif
