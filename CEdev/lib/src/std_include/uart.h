/*!\file uart.h
 * \brief Definition file for the eZ80 UART Devices.
 *
 *  This file contains header information required by UART driver
 *  implementations for eZ80 and eZ80 Acclaim! series of microprocessors
 *  and microcontrollers.
 *
 *  This source file uses Doxygen-style comments to generate documentation
 *  automatically.
 *
 *  Copyright (C) 1999-2004 by  ZiLOG, Inc.
 *  All Rights Reserved.
 */

#ifndef _UART_H_
#define _UART_H_

#include <defines.h>
#include <uartdefs.h>
#include <cio.h>

#define DEFAULT_UART0

/*!
 * Defined to include parameter checking logic in the code. This will validate
 * the parameters passed while initializing or configuring the device and return
 * appropriate error code, if any. By default the parameter checking is included
 * when DEBUG is defined.
 */
#ifdef DEBUG
/* #define PARAMETER_CHECKING */
#endif


#define UART0				0		            	//!< The UART device 0.
#define UART1				1		            	//!< The UART device 1.

#define INTERRUPT			1		    	        //!< The interrupt mode.
#define POLL                0		    	        //!< The poll mode.

#ifdef _EZ80190
#define MASTERCLOCK			50000000	            //!< The default system clock speed for eZ80190.
#if !defined(UART0_IVECT) /*If it already defined using ez80.h*/
#define UART0_IVECT			0x12		            //!< The UART0 interrupt vector.
#endif
#if !defined(UART1_IVECT) /*If it already defined using ez80.h*/
#define UART1_IVECT			0x14		            //!< The UART1 interrupt vector.
#endif
#endif								                
										            
#ifdef _EZ80L92						                
#define MASTERCLOCK			48000000	            //!< The default system clock speed for eZ80L92.
#if !defined(UART0_IVECT) /*If it already defined using ez80.h*/
#define UART0_IVECT			0x18		            //!< The UART0 interrupt vector.
#endif
#if !defined(UART1_IVECT) /*If it already defined using ez80.h*/
#define UART1_IVECT			0x1A		            //!< The UART1 interrupt vector.
#endif
#endif								                
										            
#ifdef _EZ80F91						                
#define MASTERCLOCK			50000000	            //!< The default system clock speed for eZ80F91.
#if !defined(UART0_IVECT) /*If it already defined using ez80.h*/
#define UART0_IVECT			0x70		            //!< The UART0 interrupt vector.
#endif
#if !defined(UART1_IVECT) /*If it already defined using ez80.h*/
#define UART1_IVECT			0x74		            //!< The UART1 interrupt vector.
#endif
#endif								                
										            
#ifdef _EZ80F92						                
#define MASTERCLOCK			20000000	            //!< The default system clock speed for eZ80F92.
#if !defined(UART0_IVECT) /*If it already defined using ez80.h*/
#define UART0_IVECT			0x18		            //!< The UART0 interrupt vector.
#endif
#if !defined(UART1_IVECT) /*If it already defined using ez80.h*/
#define UART1_IVECT			0x1A		            //!< The UART1 interrupt vector.
#endif
#endif

#ifdef _EZ80F93
#define MASTERCLOCK			20000000	            //!< The default system clock speed for eZ80F93.
#if !defined(UART0_IVECT) /*If it already defined using ez80.h*/
#define UART0_IVECT			0x18		            //!< The UART0 interrupt vector.
#endif
#if !defined(UART1_IVECT) /*If it already defined using ez80.h*/
#define UART1_IVECT			0x1A		            //!< The UART1 interrupt vector.
#endif
#endif								    									            

#define CLOCK_DIVISOR_16		16			        //!< The default clock divisor used in the driver.

#define BAUD_9600			9600	            	//!< Baud rate 9600.
#define BAUD_19200			19200	            	//!< Baud rate 19200.
#define BAUD_38400			38400	            	//!< Baud rate 38400.
#define BAUD_57600			57600	            	//!< Baud rate 57600.
#define BAUD_115200			115200	    	        //!< Baud rate 115200.

#define DATABITS_8				8					//!< The default number of bits per character used in the driver.
#define DATABITS_7				7
#define DATABITS_6				6
#define DATABITS_5				5

#define STOPBITS_1				1
#define STOPBITS_2				2					//!< The default number of stop bits used in the driver.

#define PAR_NOPARITY			0	    	        //!< No parity.
#define PAR_ODPARITY			1	    	        //!< Odd parity.
#define PAR_EVPARITY			3	    	        //!< Even parity.

#define FIFO_TRGLVL_1			1			        //!< FIFO trigger level 1.
#define FIFO_TRGLVL_4			4		            //!< FIFO trigger level 4.
#define FIFO_TRGLVL_8			8		            //!< FIFO trigger level 8.
#define FIFO_TRGLVL_14			14		            //!< FIFO trigger level 14.
#define FIFO_TRGLVL_NONE		0					//!< FIFO is disabled.

#define FLUSHFIFO_TX			1	    	        //!< Flush the software transmit FIFO.
#define FLUSHFIFO_RX			2		            //!< Flush the software receive FIFO.
#define FLUSHFIFO_ALL			3		            //!< Flush the software transmit FIFO.

#define ENABLE_HWFLOW_CONTROL			1			//!< The default hardware control setting (0=disable; 1=enable).
#define DISABLE_HWFLOW_CONTROL			0

#define ENABLE_SWFLOW_CONTROL			1			//!< The default software control setting (0=disable; 1=enable).
#define DISABLE_SWFLOW_CONTROL			0	

/*!
 * The error codes consists of both the errors reported by the UART device
 * (through status registers), and the errors that occur in the UART driver
 * software.
 */
#define	UART_ERR_NONE					((BYTE)0x00)		//!< The error code for success.
#define	UART_ERR_KBHIT					((BYTE)0x01)		//!< The error code for keyboard hit.			
#define	UART_ERR_FRAMINGERR				((BYTE)0x02)		//!< The error code returned when Framing error occurs in the character received.		
#define	UART_ERR_PARITYERR				((BYTE)0x03)		//!< The error code returned when Parity error occurs in the character received.			
#define	UART_ERR_OVERRUNERR				((BYTE)0x04)		//!< The error code returned when Overrun error occurs in the receive buffer register.		
#define	UART_ERR_BREAKINDICATIONERR		((BYTE)0x05)		//!< The error code returned when Break Indication Error occurs.		
#define	UART_ERR_CHARTIMEOUT			((BYTE)0x06)		//!< The error code returned when a character time-out occurs while receiving.			
#define	UART_ERR_INVBAUDRATE			((BYTE)0x07)		//!< The error code returned when baud rate specified is invalid.			
#define	UART_ERR_INVPARITY				((BYTE)0x08)		//!< The error code returned when parity option specified is invalid.			
#define	UART_ERR_INVSTOPBITS			((BYTE)0x09)		//!< The error code returned when stop bits specified is invalid.			
#define	UART_ERR_INVDATABITS			((BYTE)0x0A)		//!< The error code returned when data bits per character specified is invalid.			
#define	UART_ERR_INVTRIGGERLEVEL		((BYTE)0x0B)		//!< The error code returned when receive FIFO trigger level specified is invalid.			
#define	UART_ERR_FIFOBUFFERFULL			((BYTE)0x0C)		//!< The error code returned when the transmit FIFO buffer is full.		
#define	UART_ERR_FIFOBUFFEREMPTY		((BYTE)0x0D)		//!< The error code returned when the receive FIFO buffer is empty.			
#define	UART_ERR_RECEIVEFIFOFULL		((BYTE)0x0E)		//!< The error code returned when the software receive FIFO buffer is full.			
#define	UART_ERR_RECEIVEFIFOEMPTY		((BYTE)0x0F)		//!< The error code returned when the software receive FIFO buffer is empty.			
#define	UART_ERR_PEEKINPOLL				((BYTE)0x10)		//!< The error code returned when 'peek a character' is done in polling mode, which is invalid.		
#define	UART_ERR_USERBASE				((BYTE)0x11)		//!< The error code base value for user applications.

#define	UART_ERR_FAILURE				((BYTE)-1)			//!< The error code for failures.


//Used for enabling UART0 on mini modules.
#define	ENABLE_UART0()		(PB_DDR&=0xBF,PB_ALT1&=0xBF,PB_ALT2&=0xBF,PB_DR|=0x40)


/*!
 * \brief The settings required to configure the UART driver.
 *
 * This structure will contain all the information required to
 * configure the UART device. This structure is used for opening
 * (initializing) the UART device as well as for re-configuring
 * the UART device.
 */
typedef struct
{
   CHAR uartMode ;				//!< The mode in which uart operated (INTERRUPT or POLL).
   INT24 baudRate ;				//!< The baudrate to be used.
   BYTE dataBits ;				//!< The number of databits per character to be used.
   BYTE stopBits ;				//!< The number of stopbits to be used.
   BYTE parity ;				//!< The parity bit option to be used.
   UCHAR fifoTriggerLevel ;		//!< The receive FIFO interrupt trigger level to be used.
   UCHAR hwFlowControl ;		//!< The hardware flow control to be used.
   UCHAR swFlowControl ;		//!< The software flow control to be used (no plan to implement this in ZSL 1.0).

} UART ;


/*!
 * \brief The FIFO structure.
 *
 * This structure is used to hold information about the software
 * transmit/receive FIFO buffers implemented in interrupt mode.
 */
typedef struct
{
	UCHAR *pBuffer ;				//!< The FIFO buffer
	UINT16 next_in ;				//!< The in-pointer
	UINT16 next_out ;				//!< The out-pointer
	UINT16 size ;					//!< The FIFO buffer size

} FIFO ;



/*!
 * \brief Get a character.
 */
// INT getch( VOID ) ;	/* moved to <cio.h> */

/*!
 * \brief Put a character.
 */
// INT putch( INT ) ;	/* moved to <cio.h> */

/*!
 * \brief Detect any key strokes in the keyboard connected to the default UART device.
 */
UCHAR kbhit( VOID ) ;

/*!
 * \brief Peek a character in receive FIFO of the default UART device.
 */
INT24 peekc( VOID ) ;

/*!
 * \brief Initialize the UART0 device.
 */
UCHAR open_UART0( UART *pUART ) ;

/*!
 * \brief Configure the UART0 device.
 */
UCHAR control_UART0( UART *pUART ) ;

/*!
 * \brief Set baud rate for the UART0 device.
 */
UCHAR setbaud_UART0( INT24 baud ) ;

/*!
 * \brief Set parity bit option for the UART0 device.
 */
UCHAR setparity_UART0( UCHAR parity ) ;

/*!
 * \brief Set stop bits for the UART0 device.
 */
UCHAR setstopbits_UART0( UCHAR stopbits ) ;

/*!
 * \brief Set number of data bits per character for the UART0 device.
 */
UCHAR setdatabits_UART0( UCHAR databits ) ;

/*!
 * \brief Set receive FIFO trigger level for the UART0 device.
 */
UCHAR settriggerlevel_UART0( UCHAR level ) ;

/*!
 * \brief Enable parity bit check option for the UART0 device.
 */
VOID enableparity_UART0( VOID ) ;

/*!
 * \brief Disable parity bit check option for the UART0 device.
 */
VOID disableparity_UART0( VOID ) ;

/*!
 * \brief Enable or disable hardware flow control for the UART0 device.
 */
VOID HWflowcontrol_UART0( UCHAR hardwarefctl ) ;

/*!
 * \brief Enable or disable software flow control for the UART0 device.
 */
VOID SWflowcontrol_UART0( UCHAR softwarefctl ) ;

/*!
 * \brief Send break on the UART0 device.
 */
VOID sendbreak_UART0() ;

/*!
 * \brief Stop sending break on the UART0 device.
 */
VOID clearbreak_UART0() ;

/*!
 * \brief Flush the specified FIFO(s) for the UART0 device.
 */
VOID flush_UART0( UCHAR fifo ) ;

/*!
 * \brief Write data bytes to the UART0 device.
 */
UCHAR write_UART0( CHAR *pData, UINT24 nbytes ) ;

/*!
 * \brief Read data bytes from the UART0 device.
 */
UCHAR read_UART0( CHAR *pData, UINT24 *nbytes ) ;

/*!
 * \brief Close the UART0 device.
 */
VOID close_UART0( VOID ) ;


/*!
 * \brief Initialize the UART1 device.
 */
UCHAR open_UART1( UART *pUART ) ;

/*!
 * \brief Configure the UART1 device.
 */
UCHAR control_UART1( UART *pUART ) ;

/*!
 * \brief Set baud rate for the UART1 device.
 */
UCHAR setbaud_UART1( INT24 baud ) ;

/*!
 * \brief Set parity bit option for the UART1 device.
 */
UCHAR setparity_UART1( UCHAR parity ) ;

/*!
 * \brief Set stop bits for the UART1 device.
 */
UCHAR setstopbits_UART1( UCHAR stopbits ) ;

/*!
 * \brief Set number of data bits per character for the UART1 device.
 */
UCHAR setdatabits_UART1( UCHAR databits ) ;

/*!
 * \brief Set receive FIFO trigger level for the UART1 device.
 */
UCHAR settriggerlevel_UART1( UCHAR level ) ;

/*!
 * \brief Enable parity bit check option for the UART1 device.
 */
VOID enableparity_UART1( VOID ) ;

/*!
 * \brief Disable parity bit check option for the UART1 device.
 */
VOID disableparity_UART1( VOID ) ;

/*!
 * \brief Enable or disable hardware flow control for the UART1 device.
 */
VOID HWflowcontrol_UART1( UCHAR hardwarefctl ) ;

/*!
 * \brief Enable or disable software flow control for the UART1 device.
 */
VOID SWflowcontrol_UART1( UCHAR softwarefctl ) ;

/*!
 * \brief Send break on the UART1 device.
 */
VOID sendbreak_UART1() ;

/*!
 * \brief Stop sending break on the UART1 device.
 */
VOID clearbreak_UART1() ;

/*!
 * \brief Flush the specified FIFO(s) for the UART1 device.
 */
VOID flush_UART1( UCHAR fifo ) ;

/*!
 * \brief Write data bytes to the UART1 device.
 */
UCHAR write_UART1( CHAR *pData, UINT24 nbytes ) ;

/*!
 * \brief Read data bytes from the UART1 device.
 */
UCHAR read_UART1( CHAR *pData, UINT24 *nbytes ) ;

/*!
 * \brief Close the UART1 device.
 */
VOID close_UART1( VOID ) ;



#endif /*! _UART_H_ */

