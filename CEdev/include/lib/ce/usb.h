/**
 * @file    USB CE C Functions
 * @version 1
 *
 * @section LICENSE
 *
 * Copyright (c) 2017
 * Matthew "MateoConLechuga" Waltz
 * Jacob "jacobly" Young
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @section DESCRIPTION
 *
 * This library implements embedded usb functions present in the bootcode and OS
 */

#ifndef H_USB
#define H_USB

#include <stdint.h>
#include <stdbool.h>

/**
 * Returns true if the usb bus line is powered, i.e. connected to a another calc
 */
bool usb_BusPowered(void);

/**
 * Returns true if the usb is self powered
 */
bool usb_SelfPowered(void);

/**
 * Resets the usb controller chip
 */
void usb_ResetChip(void);

/**
 * Disables the usb timer interrupt (timer 3)
 */
void usb_DisableTimers(void);

/**
 * Enables the usb timer interrupt (timer 3)
 */
void usb_EnableTimers(void);

/**
 * Resets the usb timer interrupt (timer 3)
 */
void usb_ResetTimers(void);

#endif
