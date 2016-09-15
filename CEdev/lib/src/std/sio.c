/*======================================================================
		     Copyright (C) 1987-2008 by			       
		            Zilog, Inc.           	               
			All Rights Reserved			       
							 	       
		        San Jose, California     		       
========================================================================
eZ80 sio.c - Contains runtime routines for the eZ80 UART.

Define SIMULATE to allow these to run on the simulator
=======================================================================*/
#include <eZ80.h>
#include <stdio.h>


#define UART                 0
#define UART_BPS             57600
#define UART_DATA_BITS       8
#define UART_PARITY          0
#define UART_STOP_BITS       1

#ifdef _EZ80190
#define UZI_MODE_UART        (unsigned char)0x01
#endif

#if (UART == 0)
#ifdef _EZ80190
#define UZI_CTL              UZI0_CTL
#define UART0_BRG_L          BRG0_DLR_L
#define UART0_BRG_H          BRG0_DLR_H
#endif
#define UART_RBR             UART0_RBR
#define UART_THR             UART0_THR
#define UART_BRG_L           UART0_BRG_L
#define UART_BRG_H           UART0_BRG_H
#define UART_LCTL            UART0_LCTL
#define UART_LSR             UART0_LSR
#else
#ifdef _EZ80190
#define UZI_CTL              UZI1_CTL
#define UART1_BRG_L          BRG1_DLR_L
#define UART1_BRG_H          BRG1_DLR_H
#endif
#define UART_RBR             UART1_RBR
#define UART_THR             UART1_THR
#define UART_BRG_L           UART1_BRG_L
#define UART_BRG_H           UART1_BRG_H
#define UART_LCTL            UART1_LCTL
#define UART_LSR             UART1_LSR
#endif

#define LCTL_DLAB            (unsigned char)0x80
#define LSR_THRE             (unsigned char)0x20
#define LSR_DR               (unsigned char)0x01

#define SetLCTL(d, p, s)     UART_LCTL = ((d-5)&3) | (((s-1)&1)<<2) | (p&3)

#define LF                   '\n'
#define CR                   '\r'


extern long SysClkFreq;


void uart_init(void) 
{ 
    #ifndef SIMULATE
    unsigned short brg;

    brg = SysClkFreq / (16 * UART_BPS);

    #if (UART==1)
    PC_ALT2 = 0x03;
    PC_ALT1 = 0x00;
    PC_DDR = 0xEB;
    PC_DR = 0x00;
    #else
    PD_ALT2 = 0x03;
    PD_ALT1 = 0x00;
    PD_DDR = 0xEB;
    PD_DR = 0x00;

    PB_DR = 0x40;
    PB_ALT2 = 0x00;
    PB_ALT1 = 0x00;
    PB_DDR = 0xBF;
    #endif

    #ifdef _EZ80190
    UZI_CTL = UZI_MODE_UART;
    #endif

    UART_LCTL |= LCTL_DLAB;
    UART_BRG_L = brg;
    UART_BRG_H = brg >> (unsigned short)8;
    UART_LCTL &= ~LCTL_DLAB;

    SetLCTL(UART_DATA_BITS, UART_PARITY, UART_STOP_BITS);
    #endif
} 


#ifdef SIMULATE
int putch(int ch)
{
    UART_THR = ch;

    return (ch);
}
#else
int putch(int ch)
{
    while ((UART_LSR & LSR_THRE) == (unsigned char)0);

    UART_THR = ch;

    if (ch == LF)
    {
        while ((UART_LSR & LSR_THRE) == (unsigned char)0);
        UART_THR = CR;
    }

    return (ch);
}
#endif


int kbhit(void)
{
	while ((UART_LSR & LSR_DR) == (unsigned char)0);
}


int getch(void)
{
    while ((UART_LSR & LSR_DR) == (unsigned char)0);
    return (UART_RBR);
}


int getche(void)
{
    while ((UART_LSR & LSR_DR) == (unsigned char)0);
    return (putch(UART_RBR));
}
