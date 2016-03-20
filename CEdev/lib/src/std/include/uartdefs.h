/* uartdefs.h
 * eZ80 UART register bit definitions. 
 *
 *  This file contains ez80 UART register bit definitions required by UART driver
 *  implementations for eZ80 and eZ80 Acclaim! series of microprocessors
 *  and microcontrollers.
 *
 *  This source file uses Doxygen-style comments to generate documentation
 *  automatically.
 *
 *  Copyright (C) 1999-2004 by  ZiLOG, Inc.
 *  All Rights Reserved.
 */
#ifndef _UARTDEFS_H_
#define _UARTDEFS_H_


/*!
 * The following symbols are defined to maitain uniformity
 * of symbols across the eZ80 and eZ80 Acclaim! variants.
 */
#ifdef _EZ80190
#define UART0_BRG_L	BRG0_DLR_L
#define UART0_BRG_H	BRG0_DLR_H
#define UART1_BRG_L	BRG1_DLR_L
#define UART1_BRG_H	BRG1_DLR_H
#endif

#define UART_IIR_LINESTATUS				((unsigned char)0x06)		//!< Receive Line Status interrupt code in IIR.
#define UART_IIR_DATAREADY_TRIGLVL		((unsigned char)0x04)		//!< Receive Data Ready or Trigger Level indication in IIR.
#define UART_IIR_CHARTIMEOUT			((unsigned char)0x0C)		//!< Character Time-out interrupt code in IIR.
#define UART_IIR_TRANSCOMPLETE			((unsigned char)0x0A)		//!< Transmission Complete interrupt code in IIR.
#define UART_IIR_TRANSBUFFEREMPTY		((unsigned char)0x02)		//!< Transmit Buffer Empty interrupt code in IIR.
#define UART_IIR_MODEMSTAT				((unsigned char)0x00)		//!< Modem Status interrupt code in IIR.

#define UART_LSR_DATA_READY				((unsigned char)0x01)		//!< Data ready indication in LSR.
#define UART_LSR_OVERRRUNERR			((unsigned char)0x02)		//!< Overrun error indication in LSR.
#define UART_LSR_PARITYERR				((unsigned char)0x04)		//!< Parity error indication in LSR.
#define UART_LSR_FRAMINGERR				((unsigned char)0x08)		//!< Framing error indication in LSR.
#define UART_LSR_BREAKINDICATIONERR		((unsigned char)0x10)		//!< Framing error indication in LSR.
#define UART_LSR_THREMPTY				((unsigned char)0x20)		//!< Transmit Holding Register empty indication in LSR.
#define UART_LSR_TEMT					((unsigned char)0x40)		//!< Transmit is empty.
#define UART_LSR_FIFOERR				((unsigned char)0x80)		//!< Error in FIFO indication in LSR.

#define UART_IER_RECEIVEINT				((unsigned char)0x01)		//!< Receive Interrupt bit in IER.
#define UART_IER_TRANSMITINT			((unsigned char)0x02)		//!< Transmit Interrupt bit in IER.
#define UART_IER_LINESTATUSINT			((unsigned char)0x04)		//!< Line Status Interrupt bit in IER.
#define UART_IER_MODEMINT				((unsigned char)0x08)		//!< Modem Interrupt bit in IER.
#define UART_IER_TRANSCOMPLETEINT		((unsigned char)0x10)		//!< Transmission Complete Interrupt bit in IER.
#define UART_IER_ALLINTMASK				((unsigned char)0x1F)		//!< Mask for all the interrupts listed above for IER.

#ifdef _EZ80190
#define UZI_DEVICENONE					((unsigned char)0x00)		//!< Mask for disabling all devices in Universal ZiLOG Interface.
#define UZI_DEVICEUART					((unsigned char)0x01)		//!< Mask for enabling UART devices in Universal ZiLOG Interface.
#endif

/* The following definitions are from ez80190.h and/or ez80L92.h files
   moved here and redefined for supporting existing code
*/

/* UART_IER bits */
#define UART_IER_MIIE					UART_IER_MODEMINT
#define UART_IER_LSIE					UART_IER_LINESTATUSINT
#define UART_IER_TIE					UART_IER_TRANSMITINT
#define UART_IER_RIE					UART_IER_RECEIVEINT

/* UART_IIR bits */
#define UART_IIR_FIFOEN					((unsigned char)0xC0)
#define UART_IIR_ISCMASK				((unsigned char)0x0E)
#define UART_IIR_RLS					UART_IIR_LINESTATUS
#define UART_IIR_RDR					UART_IIR_DATAREADY_TRIGLVL
#define UART_IIR_CTO					UART_IIR_CHARTIMEOUT
#define UART_IIR_TBE					UART_IIR_TRANSBUFFEREMPTY
#define UART_IIR_MS						UART_IIR_MODEMSTAT
#define UART_IIR_INTBIT					((unsigned char)0x01)

/* UART_FCTL bits */
#define UART_FCTL_TRIGMASK				((unsigned char)0x00)
#define UART_FCTL_TRIG_1				((unsigned char)0x00)
#define UART_FCTL_TRIG_4				((unsigned char)0x40)
#define UART_FCTL_TRIG_8				((unsigned char)0x80)
#define UART_FCTL_TRIG_14				((unsigned char)0xC0)
#define UART_FCTL_CLRTxF				((unsigned char)0x04)
#define UART_FCTL_CLRRxF				((unsigned char)0x02)
#define UART_FCTL_FIFOEN				((unsigned char)0x01)

/* UART_LCTL bits */
#define UART_LCTL_DLAB					((unsigned char)0x80)		//!< DLAB bit in LCTL.
#define UART_LCTL_SB					((unsigned char)0x40)		//!< Send Break bit in LCTL.
#define UART_LCTL_FPE					((unsigned char)0x20)		//!< Force Parity Error bit in LCTL.
#define UART_LCTL_EPS					((unsigned char)0x10)		//!< Even Parity Select bit in LCTL.
#define UART_LCTL_PEN					((unsigned char)0x08)		//!< Parity Enable bit in LCTL.
#define UART_LCTL_2STOPBITS				((unsigned char)0x04)
#define UART_LCTL_5DATABITS				((unsigned char)0x00)
#define UART_LCTL_6DATABITS				((unsigned char)0x01)
#define UART_LCTL_7DATABITS				((unsigned char)0x02)
#define UART_LCTL_8DATABITS				((unsigned char)0x03)

/* UART_MCTL bits */
#define UART_MCTL_LOOP					((unsigned char)0x10)
#define UART_MCTL_OUT2					((unsigned char)0x08)
#define UART_MCTL_OUT1					((unsigned char)0x04)
#define UART_MCTL_RTS					((unsigned char)0x02)
#define UART_MCTL_DTR					((unsigned char)0x01)

/* UART_LSR bits */
#define UART_LSR_ERR					((unsigned char)0x80)
#define UART_LSR_TEMT					((unsigned char)0x40)
#define UART_LSR_THRE					UART_LSR_THREMPTY
#define UART_LSR_BI						UART_LSR_BREAKINDICATIONERR
#define UART_LSR_FE						UART_LSR_FRAMINGERR
#define UART_LSR_PE						UART_LSR_PARITYERR
#define UART_LSR_OE						UART_LSR_OVERRRUNERR
#define UART_LSR_DR						UART_LSR_DATA_READY

/* UART_MSR bits */
#define UART_MSR_DCD					((unsigned char)0x80)
#define UART_MSR_RI						((unsigned char)0x40)
#define UART_MSR_DSR					((unsigned char)0x20)
#define UART_MSR_CTS					((unsigned char)0x10)
#define UART_MSR_DDCD					((unsigned char)0x08)
#define UART_MSR_TERI					((unsigned char)0x04)
#define UART_MSR_DDSR					((unsigned char)0x02)
#define UART_MSR_DCTS					((unsigned char)0x01)

#endif