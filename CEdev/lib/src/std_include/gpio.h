/*!\file gpio.h
 * \brief Definition file for the eZ80 GPIO Ports.
 *
 *  This file contains header information required by GPIO Port
 *  driver implementations for eZ80 and eZ80 Acclaim! series of
 *  microprocessors and microcontrollers.
 *
 *  This source file uses Doxygen-style comments to generate documentation
 *  automatically.
 *
 *  Copyright (C) 1999-2004 by  ZiLOG, Inc.
 *  All Rights Reserved.
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include <defines.h>
#include <ez80.h>

#ifdef _EZ80190
#define PA0_IVECT			0x16			//!< The interrupt vector for Port A bit 0 for eZ80190.
#define PA1_IVECT			0x18			//!< The interrupt vector for Port A bit 1 for eZ80190.
#define PA2_IVECT			0x1A			//!< The interrupt vector for Port A bit 2 for eZ80190.
#define PA3_IVECT			0x1C			//!< The interrupt vector for Port A bit 3 for eZ80190.
#define PA4_IVECT			0x1E			//!< The interrupt vector for Port A bit 4 for eZ80190.
#define PA5_IVECT			0x20			//!< The interrupt vector for Port A bit 5 for eZ80190.
#define PA6_IVECT			0x22			//!< The interrupt vector for Port A bit 6 for eZ80190.
#define PA7_IVECT			0x24			//!< The interrupt vector for Port A bit 7 for eZ80190.

#define PB0_IVECT			0x26			//!< The interrupt vector for Port B bit 0 for eZ80190.
#define PB1_IVECT			0x28			//!< The interrupt vector for Port B bit 1 for eZ80190.
#define PB2_IVECT			0x2A			//!< The interrupt vector for Port B bit 2 for eZ80190.
#define PB3_IVECT			0x2C			//!< The interrupt vector for Port B bit 3 for eZ80190.
#define PB4_IVECT			0x2E			//!< The interrupt vector for Port B bit 4 for eZ80190.
#define PB5_IVECT			0x30			//!< The interrupt vector for Port B bit 5 for eZ80190.
#define PB6_IVECT			0x32			//!< The interrupt vector for Port B bit 6 for eZ80190.
#define PB7_IVECT			0x34			//!< The interrupt vector for Port B bit 7 for eZ80190.

#define PC0_IVECT			0x36			//!< The interrupt vector for Port C bit 0 for eZ80190.
#define PC1_IVECT			0x38			//!< The interrupt vector for Port C bit 1 for eZ80190.
#define PC2_IVECT			0x3A			//!< The interrupt vector for Port C bit 2 for eZ80190.
#define PC3_IVECT			0x3C			//!< The interrupt vector for Port C bit 3 for eZ80190.
#define PC4_IVECT			0x3E			//!< The interrupt vector for Port C bit 4 for eZ80190.
#define PC5_IVECT			0x40			//!< The interrupt vector for Port C bit 5 for eZ80190.
#define PC6_IVECT			0x42			//!< The interrupt vector for Port C bit 6 for eZ80190.
#define PC7_IVECT			0x44			//!< The interrupt vector for Port C bit 7 for eZ80190.

#define PD0_IVECT			0x46			//!< The interrupt vector for Port D bit 0 for eZ80190.
#define PD1_IVECT			0x48			//!< The interrupt vector for Port D bit 1 for eZ80190.
#define PD2_IVECT			0x4A			//!< The interrupt vector for Port D bit 2 for eZ80190.
#define PD3_IVECT			0x4C			//!< The interrupt vector for Port D bit 3 for eZ80190.
#define PD4_IVECT			0x4E			//!< The interrupt vector for Port D bit 4 for eZ80190.
#define PD5_IVECT			0x50			//!< The interrupt vector for Port D bit 5 for eZ80190.
#define PD6_IVECT			0x52			//!< The interrupt vector for Port D bit 6 for eZ80190.
#define PD7_IVECT			0x54			//!< The interrupt vector for Port D bit 7 for eZ80190.
#endif	//! _EZ80190

#ifdef _EZ80F91
#define PA0_IVECT			0x80			//!< The interrupt vector for Port A bit 0 for eZ80F91.
#define PA1_IVECT			0x84			//!< The interrupt vector for Port A bit 1 for eZ80F91.
#define PA2_IVECT			0x88			//!< The interrupt vector for Port A bit 2 for eZ80F91.
#define PA3_IVECT			0x8C			//!< The interrupt vector for Port A bit 3 for eZ80F91.
#define PA4_IVECT			0x90			//!< The interrupt vector for Port A bit 4 for eZ80F91.
#define PA5_IVECT			0x94			//!< The interrupt vector for Port A bit 5 for eZ80F91.
#define PA6_IVECT			0x98			//!< The interrupt vector for Port A bit 6 for eZ80F91.
#define PA7_IVECT			0x9C			//!< The interrupt vector for Port A bit 7 for eZ80F91.

#define PB0_IVECT			0xA0			//!< The interrupt vector for Port B bit 0 for eZ80F91.
#define PB1_IVECT			0xA4			//!< The interrupt vector for Port B bit 1 for eZ80F91.
#define PB2_IVECT			0xA8			//!< The interrupt vector for Port B bit 2 for eZ80F91.
#define PB3_IVECT			0xAC			//!< The interrupt vector for Port B bit 3 for eZ80F91.
#define PB4_IVECT			0xB0			//!< The interrupt vector for Port B bit 4 for eZ80F91.
#define PB5_IVECT			0xB4			//!< The interrupt vector for Port B bit 5 for eZ80F91.
#define PB6_IVECT			0xB8			//!< The interrupt vector for Port B bit 6 for eZ80F91.
#define PB7_IVECT			0xBC			//!< The interrupt vector for Port B bit 7 for eZ80F91.

#define PC0_IVECT			0xC0			//!< The interrupt vector for Port C bit 0 for eZ80F91.
#define PC1_IVECT			0xC4			//!< The interrupt vector for Port C bit 1 for eZ80F91.
#define PC2_IVECT			0xC8			//!< The interrupt vector for Port C bit 2 for eZ80F91.
#define PC3_IVECT			0xCC			//!< The interrupt vector for Port C bit 3 for eZ80F91.
#define PC4_IVECT			0xD0			//!< The interrupt vector for Port C bit 4 for eZ80F91.
#define PC5_IVECT			0xD4			//!< The interrupt vector for Port C bit 5 for eZ80F91.
#define PC6_IVECT			0xD8			//!< The interrupt vector for Port C bit 6 for eZ80F91.
#define PC7_IVECT			0xDC			//!< The interrupt vector for Port C bit 7 for eZ80F91.

#define PD0_IVECT			0xE0			//!< The interrupt vector for Port D bit 0 for eZ80F91.
#define PD1_IVECT			0xE4			//!< The interrupt vector for Port D bit 1 for eZ80F91.
#define PD2_IVECT			0xE8			//!< The interrupt vector for Port D bit 2 for eZ80F91.
#define PD3_IVECT			0xEC			//!< The interrupt vector for Port D bit 3 for eZ80F91.
#define PD4_IVECT			0xF0			//!< The interrupt vector for Port D bit 4 for eZ80F91.
#define PD5_IVECT			0xF4			//!< The interrupt vector for Port D bit 5 for eZ80F91.
#define PD6_IVECT			0xF8			//!< The interrupt vector for Port D bit 6 for eZ80F91.
#define PD7_IVECT			0xFC			//!< The interrupt vector for Port D bit 7 for eZ80F91.
#endif	//! _EZ80F91

#ifdef _EZ80L92
#define PORTSBCD_IVECTORS
#endif

#ifdef _EZ80F92
#define PORTSBCD_IVECTORS
#endif

#ifdef _EZ80F93
#define PORTSBCD_IVECTORS
#endif

#ifdef PORTSBCD_IVECTORS
#define PB0_IVECT			0x30			//!< The interrupt vector for Port B bit 0 for eZ80L92/F92/F93.
#define PB1_IVECT			0x32			//!< The interrupt vector for Port B bit 1 for eZ80L92/F92/F93.
#define PB2_IVECT			0x34			//!< The interrupt vector for Port B bit 2 for eZ80L92/F92/F93.
#define PB3_IVECT			0x36			//!< The interrupt vector for Port B bit 3 for eZ80L92/F92/F93.
#define PB4_IVECT			0x38			//!< The interrupt vector for Port B bit 4 for eZ80L92/F92/F93.
#define PB5_IVECT			0x3A			//!< The interrupt vector for Port B bit 5 for eZ80L92/F92/F93.
#define PB6_IVECT			0x3C			//!< The interrupt vector for Port B bit 6 for eZ80L92/F92/F93.
#define PB7_IVECT			0x3E			//!< The interrupt vector for Port B bit 7 for eZ80L92/F92/F93.

#define PC0_IVECT			0x40			//!< The interrupt vector for Port C bit 0 for eZ80L92/F92/F93.
#define PC1_IVECT			0x42			//!< The interrupt vector for Port C bit 1 for eZ80L92/F92/F93.
#define PC2_IVECT			0x44			//!< The interrupt vector for Port C bit 2 for eZ80L92/F92/F93.
#define PC3_IVECT			0x46			//!< The interrupt vector for Port C bit 3 for eZ80L92/F92/F93.
#define PC4_IVECT			0x48			//!< The interrupt vector for Port C bit 4 for eZ80L92/F92/F93.
#define PC5_IVECT			0x4A			//!< The interrupt vector for Port C bit 5 for eZ80L92/F92/F93.
#define PC6_IVECT			0x4C			//!< The interrupt vector for Port C bit 6 for eZ80L92/F92/F93.
#define PC7_IVECT			0x4E			//!< The interrupt vector for Port C bit 7 for eZ80L92/F92/F93.

#define PD0_IVECT			0x50			//!< The interrupt vector for Port D bit 0 for eZ80L92/F92/F93.
#define PD1_IVECT			0x52			//!< The interrupt vector for Port D bit 1 for eZ80L92/F92/F93.
#define PD2_IVECT			0x54			//!< The interrupt vector for Port D bit 2 for eZ80L92/F92/F93.
#define PD3_IVECT			0x56			//!< The interrupt vector for Port D bit 3 for eZ80L92/F92/F93.
#define PD4_IVECT			0x58			//!< The interrupt vector for Port D bit 4 for eZ80L92/F92/F93.
#define PD5_IVECT			0x5A			//!< The interrupt vector for Port D bit 5 for eZ80L92/F92/F93.
#define PD6_IVECT			0x5C			//!< The interrupt vector for Port D bit 6 for eZ80L92/F92/F93.
#define PD7_IVECT			0x5E			//!< The interrupt vector for Port D bit 7 for eZ80L92/F92/F93.
#endif	//! PORTSBCD_IVECTORS



#ifdef _EZ80F91
#define INCLUDEPORTA
#endif

#ifdef _EZ80190
#define INCLUDEPORTA
#endif

#ifdef INCLUDEPORTA
#define PORTA_DRVAL_DEF   	0xFF			//!< The default value for Port A data register (set for Mode 2).
#define PORTA_DDRVAL_DEF  	0xFF			//!< The default value for Port A data direction register (set for Mode 2).
#define PORTA_ALT0VAL_DEF 	0xFF			//!< The default value for Port A alternate register-0 (clear interrupts).
#define PORTA_ALT1VAL_DEF 	0x00			//!< The default value for Port A alternate register-1 (set for Mode 2).
#define PORTA_ALT2VAL_DEF 	0x00			//!< The default value for Port A alternate register-2 (set for Mode 2).
#endif //! INCLUDEPORTA

#define PORTB_DRVAL_DEF  	0xFF			//!< The default value for Port B data register (set for Mode 2).
#define PORTB_DDRVAL_DEF  	0xFF			//!< The default value for Port B data direction register (set for Mode 2).
#define PORTB_ALT0VAL_DEF 	0xFF			//!< The default value for Port B alternate register-0 (clear interrupts).
#define PORTB_ALT1VAL_DEF 	0x00			//!< The default value for Port B alternate register-1 (set for Mode 2).
#define PORTB_ALT2VAL_DEF 	0x00			//!< The default value for Port B alternate register-2 (set for Mode 2).

#define PORTC_DRVAL_DEF   	0xFF			//!< The default value for Port C data register (set for Mode 2).
#define PORTC_DDRVAL_DEF  	0xFF			//!< The default value for Port C data direction register (set for Mode 2).
#define PORTC_ALT0VAL_DEF 	0xFF			//!< The default value for Port C alternate register-0 (clear interrupts).
#define PORTC_ALT1VAL_DEF 	0x00			//!< The default value for Port C alternate register-1 (set for Mode 2).
#define PORTC_ALT2VAL_DEF 	0x00			//!< The default value for Port C alternate register-2 (set for Mode 2).

#define PORTD_DRVAL_DEF   	0xFF			//!< The default value for Port D data register (set for Mode 2).
#define PORTD_DDRVAL_DEF  	0xFF			//!< The default value for Port D data direction register (set for Mode 2).
#define PORTD_ALT0VAL_DEF 	0xFF			//!< The default value for Port D alternate register-0 (clear interrupts).
#define PORTD_ALT1VAL_DEF 	0x00			//!< The default value for Port D alternate register-1 (set for Mode 2).
#define PORTD_ALT2VAL_DEF 	0x00			//!< The default value for Port D alternate register-2 (set for Mode 2).


#define PORTPIN_ZERO		0x01			//!< The bit mask for Port bit 0.
#define PORTPIN_ONE			0x02			//!< The bit mask for Port bit 1.
#define PORTPIN_TWO			0x04			//!< The bit mask for Port bit 2.
#define PORTPIN_THREE		0x08			//!< The bit mask for Port bit 3.
#define PORTPIN_FOUR		0x10			//!< The bit mask for Port bit 4.
#define PORTPIN_FIVE 		0x20			//!< The bit mask for Port bit 5.
#define PORTPIN_SIX			0x40			//!< The bit mask for Port bit 6.
#define PORTPIN_SEVEN		0x80			//!< The bit mask for Port bit 7.
#define PORTPIN_FOURBITS_L	0x0F			//!< The bit mask for lower four Port bits.
#define PORTPIN_FOURBITS_U	0xF0			//!< The bit mask for upper four Port bits.
#define PORTPIN_PATTERN_AA	0xAA			//!< The bit mask for alternate bits (odd numbered pins).
#define PORTPIN_PATTERN_55	0x55			//!< The bit mask for alternate bits (even numbered pins).
#define PORTPIN_ALL			0xFF			//!< The bit mask for all Port bits.


#define GPIOERR_SUCCESS		0				//!< The error code for success returned by GPIO APIs.
#define GPIOERR_FAILURE		(-1)			//!< The error code for failure returned by GPIO APIs.


/*!
 * Resets all those bits in \a x as specified by the bit pattern in \a y.
 */
#define	RESETREG( x, y )	( (x) &= (0xFF ^ (y)) )

/*!
 * Sets all those bits in \a x as specified by the bit pattern in \a y.
 */
#define SETREG( x, y )		( (x) |= (y) )

/**
 * \ingroup GPIO
 */
//! @{
//! Macro definitions.
#ifdef INCLUDEPORTA
#define SETDR_PORTA( x )	( PA_DR = (x) )		//!< Set Port A Data Register with the value specified by argument \a x.
#define SETDDR_PORTA( x )	( PA_DDR = (x) )	//!< Set Port A Data Direction Register with the value specified by argument \a x.
#ifdef _EZ80F91
#define SETALT0_PORTA( x )	( PA_ALT0 = (x) )	//!< Set Port A Alternate Register-0 with the value specified by argument \a x.
#endif
#define SETALT1_PORTA( x )	( PA_ALT1 = (x) )	//!< Set Port A Alternate Register-1 with the value specified by argument \a x.
#define SETALT2_PORTA( x )	( PA_ALT2 = (x) )	//!< Set Port A Alternate Register-2 with the value specified by argument \a x.

#define GETDR_PORTA( x )	( (x) = PA_DR )		//!< Read Port A Data Register into argument \a x.
#define GETDDR_PORTA( x )	( (x) = PA_DDR )	//!< Read Port A Data Direction Register into argument \a x.
#define GETALT1_PORTA( x )	( (x) = PA_ALT1 )	//!< Read Port A Alternate Register-1 into argument \a x.
#define GETALT2_PORTA( x )	( (x) = PA_ALT2 )	//!< Read Port A Alternate Register-2 into argument \a x.
#endif //! INCLUDEPORTA

#define SETDR_PORTB( x )	( PB_DR = (x) )		//!< Set Port B Data Register with the value specified by argument \a x.
#define SETDDR_PORTB( x )	( PB_DDR = (x) )	//!< Set Port B Data Direction Register with the value specified by argument \a x.
#ifdef _EZ80F91
#define SETALT0_PORTB( x )	( PB_ALT0 = (x) )	//!< Set Port B Alternate Register-0 with the value specified by argument \a x.
#endif
#define SETALT1_PORTB( x )	( PB_ALT1 = (x) )	//!< Set Port B Alternate Register-1 with the value specified by argument \a x.
#define SETALT2_PORTB( x )	( PB_ALT2 = (x) )	//!< Set Port B Alternate Register-2 with the value specified by argument \a x.

#define GETDR_PORTB( x )	( (x) = PB_DR )		//!< Read Port B Data Register into argument \a x.
#define GETDDR_PORTB( x )	( (x) = PB_DDR )	//!< Read Port B Data Direction Register into argument \a x.
#define GETALT1_PORTB( x )	( (x) = PB_ALT1 )	//!< Read Port B Alternate Register-1 into argument \a x.
#define GETALT2_PORTB( x )	( (x) = PB_ALT2 )	//!< Read Port B Alternate Register-2 into argument \a x.

#define SETDR_PORTC( x )	( PC_DR = (x) )		//!< Set Port C Data Register with the value specified by argument \a x.
#define SETDDR_PORTC( x )	( PC_DDR = (x) )	//!< Set Port C Data Direction Register with the value specified by argument \a x.
#ifdef _EZ80F91
#define SETALT0_PORTC( x )	( PC_ALT0 = (x) )	//!< Set Port C Alternate Register-0 with the value specified by argument \a x.
#endif
#define SETALT1_PORTC( x )	( PC_ALT1 = (x) )	//!< Set Port C Alternate Register-1 with the value specified by argument \a x.
#define SETALT2_PORTC( x )	( PC_ALT2 = (x) )	//!< Set Port C Alternate Register-2 with the value specified by argument \a x.

#define GETDR_PORTC( x )	( (x) = PC_DR )		//!< Read Port C Data Register into argument \a x.
#define GETDDR_PORTC( x )	( (x) = PC_DDR )	//!< Read Port C Data Direction Register into argument \a x.
#define GETALT1_PORTC( x )	( (x) = PC_ALT1 )	//!< Read Port C Alternate Register-1 into argument \a x.
#define GETALT2_PORTC( x )	( (x) = PC_ALT2 )	//!< Read Port C Alternate Register-2 into argument \a x.

#define SETDR_PORTD( x )	( PD_DR = (x) )		//!< Set Port D Data Register with the value specified by argument \a x.
#define SETDDR_PORTD( x )	( PD_DDR = (x) )	//!< Set Port D Data Direction Register with the value specified by argument \a x.
#ifdef _EZ80F91
#define SETALT0_PORTD( x )	( PD_ALT0 = (x) )	//!< Set Port D Alternate Register-0 with the value specified by argument \a x.
#endif
#define SETALT1_PORTD( x )	( PD_ALT1 = (x) )	//!< Set Port D Alternate Register-1 with the value specified by argument \a x.
#define SETALT2_PORTD( x )	( PD_ALT2 = (x) )	//!< Set Port D Alternate Register-2 with the value specified by argument \a x.

#define GETDR_PORTD( x )	( (x) = PD_DR )		//!< Read Port D Data Register into argument \a x.
#define GETDDR_PORTD( x )	( (x) = PD_DDR )	//!< Read Port D Data Direction Register into argument \a x.
#define GETALT1_PORTD( x )	( (x) = PD_ALT1 )	//!< Read Port D Alternate Register-1 into argument \a x.
#define GETALT2_PORTD( x )	( (x) = PD_ALT2 )	//!< Read Port D Alternate Register-2 into argument \a x.

//!@}
/*!
 * \brief The settings required to configure the GPIO Port.
 */
typedef struct
{
	BYTE dr ;							//!< The data register value to be used.
	BYTE ddr ;							//!< The data direction register value to be used.
	BYTE alt1 ;							//!< The alternate register-1 value to be used.
	BYTE alt2 ;							//!< The alternate register-2 value to be used.
#ifdef _EZ80F91
	BYTE alt0 ;							//!< The alternate register-0 value to be used.
#endif

} PORT ;


/*!
 * \brief The GPIO Modes.
 *
 * The enumeration of GPIO modes used for configuring Port bits.
 */
typedef enum
{
	GPIOMODE_OUTPUT = 1,				//!< The GPIO Output mode.
	GPIOMODE_INPUT,						//!< The GPIO Input mode.
	GPIOMODE_OPENDRAINIO,				//!< The GPIO Open Drain IO mode.
	GPIOMODE_OPENSOURCEIO,				//!< The GPIO Open Source IO mode.
	GPIOMODE_INTERRUPTDUALEDGE,			//!< The GPIO Interrupt with dual-edge triggered mode.
	GPIOMODE_ALTFUNC,					//!< The GPIO Alternate function mode.
	GPIOMODE_INTERRUPTACTVLOW,			//!< The GPIO Interrupt with active low-level triggered mode.
	GPIOMODE_INTERRUPTACTVHIGH,			//!< The GPIO Interrupt with active high-level triggered mode.
	GPIOMODE_INTERRUPTFALLEDGE,			//!< The GPIO Interrupt with falling edge triggered mode.
	GPIOMODE_INTERRUPTRISEEDGE			//!< The GPIO Interrupt with rising edge triggered mode.

} GPIOMODES ;



#ifdef INCLUDEPORTA
/*!
 * \brief Initialize the Port A.
 */
VOID open_PortA( PORT *port ) ;

/*!
 * \brief Configure the Port A.
 */
VOID control_PortA( PORT *port ) ;

/*!
 * \brief Set mode for the Port A bits.
 */
UCHAR setmode_PortA( BYTE bitpattern, GPIOMODES mode ) ;

/*!
 * \brief Get Port A Settings.
 */
VOID getsettings_PortA( PORT *pPort ) ;

/*!
 * \brief Close the Port A.
 */
VOID close_PortA( VOID ) ;

#endif	//! INCLUDEPORTA


/*!
 * \brief Initialize the Port B.
 */
VOID open_PortB( PORT *port ) ;

/*!
 * \brief Configure the Port B.
 */
VOID control_PortB( PORT *port ) ;

/*!
 * \brief Set mode for the Port B bits.
 */
UCHAR setmode_PortB( BYTE bitpattern, GPIOMODES mode ) ;

/*!
 * \brief Get Port B Settings.
 */
VOID getsettings_PortB( PORT *pPort ) ;

/*!
 * \brief Close the Port B.
 */
VOID close_PortB( VOID ) ;



/*!
 * \brief Initialize the Port C.
 */
VOID open_PortC( PORT *port ) ;

/*!
 * \brief Configure the Port C.
 */
VOID control_PortC( PORT *port ) ;

/*!
 * \brief Set mode for the Port C bits.
 */
UCHAR setmode_PortC( BYTE bitpattern, GPIOMODES mode ) ;

/*!
 * \brief Get Port C Settings.
 */
VOID getsettings_PortC( PORT *pPort ) ;

/*!
 * \brief Close the Port C.
 */
VOID close_PortC( VOID ) ;



/*!
 * \brief Initialize the Port D.
 */
VOID open_PortD( PORT *port ) ;

/*!
 * \brief Configure the Port D.
 */
VOID control_PortD( PORT *port ) ;

/*!
 * \brief Set mode for the Port D bits.
 */
UCHAR setmode_PortD( BYTE bitpattern, GPIOMODES mode ) ;

/*!
 * \brief Get Port D Settings.
 */
VOID getsettings_PortD( PORT *pPort ) ;

/*!
 * \brief Close the Port D.
 */
VOID close_PortD( VOID ) ;


#endif /*! _GPIO_H_ */

