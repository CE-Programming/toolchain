/*****************************************************************************
 *  Copyright (C) 1999-2008 by  Zilog, Inc.
 *  All Rights Reserved
 *****************************************************************************/
#ifndef __eZ80F91_included
#define __eZ80F91_included


/* Product ID */
#define ZDI_ID_L        (*(volatile unsigned char __INTIO *)0x00)
#define ZDI_ID_H        (*(volatile unsigned char __INTIO *)0x01)
#define ZDI_ID_REV      (*(volatile unsigned char __INTIO *)0x02)

/* Interrupt Priority */
#define INT_P0          (*(volatile unsigned char __INTIO *)0x10)
#define INT_P1          (*(volatile unsigned char __INTIO *)0x11)
#define INT_P2          (*(volatile unsigned char __INTIO *)0x12)
#define INT_P3          (*(volatile unsigned char __INTIO *)0x13)
#define INT_P4          (*(volatile unsigned char __INTIO *)0x14)
#define INT_P5          (*(volatile unsigned char __INTIO *)0x15)

/* Ethernet Media Access Controller */
#define EMAC_TEST       (*(volatile unsigned char __INTIO *)0x20)
#define EMAC_CFG1       (*(volatile unsigned char __INTIO *)0x21)
#define EMAC_CFG2       (*(volatile unsigned char __INTIO *)0x22)
#define EMAC_CFG3       (*(volatile unsigned char __INTIO *)0x23)
#define EMAC_CFG4       (*(volatile unsigned char __INTIO *)0x24)
#define EMAC_STAD_0     (*(volatile unsigned char __INTIO *)0x25)
#define EMAC_STAD_1     (*(volatile unsigned char __INTIO *)0x26)
#define EMAC_STAD_2     (*(volatile unsigned char __INTIO *)0x27)
#define EMAC_STAD_3     (*(volatile unsigned char __INTIO *)0x28)
#define EMAC_STAD_4     (*(volatile unsigned char __INTIO *)0x29)
#define EMAC_STAD_5     (*(volatile unsigned char __INTIO *)0x2A)
#define EMAC_TPTV_L     (*(volatile unsigned char __INTIO *)0x2B)
#define EMAC_TPTV_H     (*(volatile unsigned char __INTIO *)0x2C)
#define EMAC_IPGT       (*(volatile unsigned char __INTIO *)0x2D)
#define EMAC_IPGR1      (*(volatile unsigned char __INTIO *)0x2E)
#define EMAC_IPGR2      (*(volatile unsigned char __INTIO *)0x2F)
#define EMAC_MAXF_L     (*(volatile unsigned char __INTIO *)0x30)
#define EMAC_MAXF_H     (*(volatile unsigned char __INTIO *)0x31)
#define EMAC_AFR        (*(volatile unsigned char __INTIO *)0x32)
#define EMAC_HTBL_0     (*(volatile unsigned char __INTIO *)0x33)
#define EMAC_HTBL_1     (*(volatile unsigned char __INTIO *)0x34)
#define EMAC_HTBL_2     (*(volatile unsigned char __INTIO *)0x35)
#define EMAC_HTBL_3     (*(volatile unsigned char __INTIO *)0x36)
#define EMAC_HTBL_4     (*(volatile unsigned char __INTIO *)0x37)
#define EMAC_HTBL_5     (*(volatile unsigned char __INTIO *)0x38)
#define EMAC_HTBL_6     (*(volatile unsigned char __INTIO *)0x39)
#define EMAC_HTBL_7     (*(volatile unsigned char __INTIO *)0x3A)
#define EMAC_MIIMGT     (*(volatile unsigned char __INTIO *)0x3B)
#define EMAC_CTLD_L     (*(volatile unsigned char __INTIO *)0x3C)
#define EMAC_CTLD_H     (*(volatile unsigned char __INTIO *)0x3D)
#define EMAC_RGAD       (*(volatile unsigned char __INTIO *)0x3E)
#define EMAC_FIAD       (*(volatile unsigned char __INTIO *)0x3F)
#define EMAC_PTMR       (*(volatile unsigned char __INTIO *)0x40)
#define EMAC_RST        (*(volatile unsigned char __INTIO *)0x41)
#define EMAC_TLBP_L     (*(volatile unsigned char __INTIO *)0x42)
#define EMAC_TLBP_H     (*(volatile unsigned char __INTIO *)0x43)
#define EMAC_BP_L       (*(volatile unsigned char __INTIO *)0x44)
#define EMAC_BP_H       (*(volatile unsigned char __INTIO *)0x45)
#define EMAC_BP_U       (*(volatile unsigned char __INTIO *)0x46)
#define EMAC_RHBP_L     (*(volatile unsigned char __INTIO *)0x47)
#define EMAC_RHBP_H     (*(volatile unsigned char __INTIO *)0x48)
#define EMAC_RRP_L      (*(volatile unsigned char __INTIO *)0x49)
#define EMAC_RRP_H      (*(volatile unsigned char __INTIO *)0x4A)
#define EMAC_BUFSZ      (*(volatile unsigned char __INTIO *)0x4B)
#define EMAC_IEN        (*(volatile unsigned char __INTIO *)0x4C)
#define EMAC_ISTAT      (*(volatile unsigned char __INTIO *)0x4D)
#define EMAC_PRSD_L     (*(volatile unsigned char __INTIO *)0x4E)
#define EMAC_PRSD_H     (*(volatile unsigned char __INTIO *)0x4F)
#define EMAC_MIISTAT    (*(volatile unsigned char __INTIO *)0x50)
#define EMAC_RWP_L      (*(volatile unsigned char __INTIO *)0x51)
#define EMAC_RWP_H      (*(volatile unsigned char __INTIO *)0x52)
#define EMAC_TRP_L      (*(volatile unsigned char __INTIO *)0x53)
#define EMAC_TRP_H      (*(volatile unsigned char __INTIO *)0x54)
#define EMAC_BLKSLFT_L  (*(volatile unsigned char __INTIO *)0x55)
#define EMAC_BLKSLFT_H  (*(volatile unsigned char __INTIO *)0x56)
#define EMAC_FDATA_L    (*(volatile unsigned char __INTIO *)0x57)
#define EMAC_FDATA_H    (*(volatile unsigned char __INTIO *)0x58)
#define EMAC_FFLAGS     (*(volatile unsigned char __INTIO *)0x59)

/* Phase-Locked Loop */
#define PLL_DIV_L       (*(volatile unsigned char __INTIO *)0x5C)
#define PLL_DIV_H       (*(volatile unsigned char __INTIO *)0x5D)
#define PLL_CTL0        (*(volatile unsigned char __INTIO *)0x5E)
#define PLL_CTL1        (*(volatile unsigned char __INTIO *)0x5F)

/* Timers and Pulse-Width Modulation */
#define TMR0_CTL        (*(volatile unsigned char __INTIO *)0x60)
#define TMR0_IER        (*(volatile unsigned char __INTIO *)0x61)
#define TMR0_IIR        (*(volatile unsigned char __INTIO *)0x62)
#define TMR0_DR_L       (*(volatile unsigned char __INTIO *)0x63)
#define TMR0_RR_L       (*(volatile unsigned char __INTIO *)0x63)
#define TMR0_DR_H       (*(volatile unsigned char __INTIO *)0x64)
#define TMR0_RR_H       (*(volatile unsigned char __INTIO *)0x64)
#define TMR1_CTL        (*(volatile unsigned char __INTIO *)0x65)
#define TMR1_IER        (*(volatile unsigned char __INTIO *)0x66)
#define TMR1_IIR        (*(volatile unsigned char __INTIO *)0x67)
#define TMR1_DR_L       (*(volatile unsigned char __INTIO *)0x68)
#define TMR1_RR_L       (*(volatile unsigned char __INTIO *)0x68)
#define TMR1_DR_H       (*(volatile unsigned char __INTIO *)0x69)
#define TMR1_RR_H       (*(volatile unsigned char __INTIO *)0x69)
#define TMR1_CAP_CTL    (*(volatile unsigned char __INTIO *)0x6A)
#define TMR1_CAPA_L     (*(volatile unsigned char __INTIO *)0x6B)
#define TMR1_CAPA_H     (*(volatile unsigned char __INTIO *)0x6C)
#define TMR1_CAPB_L     (*(volatile unsigned char __INTIO *)0x6D)
#define TMR1_CAPB_H     (*(volatile unsigned char __INTIO *)0x6E)
#define TMR2_CTL        (*(volatile unsigned char __INTIO *)0x6F)
#define TMR2_IER        (*(volatile unsigned char __INTIO *)0x70)
#define TMR2_IIR        (*(volatile unsigned char __INTIO *)0x71)
#define TMR2_DR_L       (*(volatile unsigned char __INTIO *)0x72)
#define TMR2_RR_L       (*(volatile unsigned char __INTIO *)0x72)
#define TMR2_DR_H       (*(volatile unsigned char __INTIO *)0x73)
#define TMR2_RR_H       (*(volatile unsigned char __INTIO *)0x73)
#define TMR3_CTL        (*(volatile unsigned char __INTIO *)0x74)
#define TMR3_IER        (*(volatile unsigned char __INTIO *)0x75)
#define TMR3_IIR        (*(volatile unsigned char __INTIO *)0x76)
#define TMR3_DR_L       (*(volatile unsigned char __INTIO *)0x77)
#define TMR3_RR_L       (*(volatile unsigned char __INTIO *)0x77)
#define TMR3_DR_H       (*(volatile unsigned char __INTIO *)0x78)
#define TMR3_RR_H       (*(volatile unsigned char __INTIO *)0x78)
#define PWM_CTL1        (*(volatile unsigned char __INTIO *)0x79)
#define PWM_CTL2        (*(volatile unsigned char __INTIO *)0x7A)
#define PWM_CTL3        (*(volatile unsigned char __INTIO *)0x7B)
#define TMR3_CAP_CTL    (*(volatile unsigned char __INTIO *)0x7B)
#define PWM0R_L         (*(volatile unsigned char __INTIO *)0x7C)
#define TMR3_CAPA_L     (*(volatile unsigned char __INTIO *)0x7C)
#define PWM0R_H         (*(volatile unsigned char __INTIO *)0x7D)
#define TMR3_CAPA_H     (*(volatile unsigned char __INTIO *)0x7D)
#define PWM1R_L         (*(volatile unsigned char __INTIO *)0x7E)
#define TMR3_CAPB_L     (*(volatile unsigned char __INTIO *)0x7E)
#define PWM1R_H         (*(volatile unsigned char __INTIO *)0x7F)
#define TMR3_CAPB_H     (*(volatile unsigned char __INTIO *)0x7F)
#define PWM2R_L         (*(volatile unsigned char __INTIO *)0x80)
#define TMR3_OC_CTL1    (*(volatile unsigned char __INTIO *)0x80)
#define PWM2R_H         (*(volatile unsigned char __INTIO *)0x81)
#define TMR3_OC_CTL2    (*(volatile unsigned char __INTIO *)0x81)
#define PWM3R_L         (*(volatile unsigned char __INTIO *)0x82)
#define TMR3_OC0_L      (*(volatile unsigned char __INTIO *)0x82)
#define PWM3R_H         (*(volatile unsigned char __INTIO *)0x83)
#define TMR3_OC0_H      (*(volatile unsigned char __INTIO *)0x83)
#define PWM0F_L         (*(volatile unsigned char __INTIO *)0x84)
#define TMR3_OC1_L      (*(volatile unsigned char __INTIO *)0x84)
#define PWM0F_H         (*(volatile unsigned char __INTIO *)0x85)
#define TMR3_OC1_H      (*(volatile unsigned char __INTIO *)0x85)
#define PWM1F_L         (*(volatile unsigned char __INTIO *)0x86)
#define TMR3_OC2_L      (*(volatile unsigned char __INTIO *)0x86)
#define PWM1F_H         (*(volatile unsigned char __INTIO *)0x87)
#define TMR3_OC2_H      (*(volatile unsigned char __INTIO *)0x87)
#define PWM2F_L         (*(volatile unsigned char __INTIO *)0x88)
#define TMR3_OC3_L      (*(volatile unsigned char __INTIO *)0x88)
#define PWM2F_H         (*(volatile unsigned char __INTIO *)0x89)
#define TMR3_OC3_H      (*(volatile unsigned char __INTIO *)0x89)
#define PWM3F_L         (*(volatile unsigned char __INTIO *)0x8A)
#define PWM3F_H         (*(volatile unsigned char __INTIO *)0x8B)

/* Watch-Dog Timer */
#define WDT_CTL         (*(volatile unsigned char __INTIO *)0x93)
#define WDT_RR          (*(volatile unsigned char __INTIO *)0x94)

/* General-Purpose Input/Output Ports */
#define PA_DR           (*(volatile unsigned char __INTIO *)0x96)
#define PA_DDR          (*(volatile unsigned char __INTIO *)0x97)
#define PA_ALT0         (*(volatile unsigned char __INTIO *)0xA6)
#define PA_ALT1         (*(volatile unsigned char __INTIO *)0x98)
#define PA_ALT2         (*(volatile unsigned char __INTIO *)0x99)
#define PB_DR           (*(volatile unsigned char __INTIO *)0x9A)
#define PB_DDR          (*(volatile unsigned char __INTIO *)0x9B)
#define PB_ALT0         (*(volatile unsigned char __INTIO *)0xA7)
#define PB_ALT1         (*(volatile unsigned char __INTIO *)0x9C)
#define PB_ALT2         (*(volatile unsigned char __INTIO *)0x9D)
#define PC_DR           (*(volatile unsigned char __INTIO *)0x9E)
#define PC_DDR          (*(volatile unsigned char __INTIO *)0x9F)
#define PC_ALT0         (*(volatile unsigned char __INTIO *)0xCE)
#define PC_ALT1         (*(volatile unsigned char __INTIO *)0xA0)
#define PC_ALT2         (*(volatile unsigned char __INTIO *)0xA1)
#define PD_DR           (*(volatile unsigned char __INTIO *)0xA2)
#define PD_DDR          (*(volatile unsigned char __INTIO *)0xA3)
#define PD_ALT0         (*(volatile unsigned char __INTIO *)0xCF)
#define PD_ALT1         (*(volatile unsigned char __INTIO *)0xA4)
#define PD_ALT2         (*(volatile unsigned char __INTIO *)0xA5)

/* Chip Select/Wait State Generator */
#define CS0_LBR         (*(volatile unsigned char __INTIO *)0xA8)
#define CS0_UBR         (*(volatile unsigned char __INTIO *)0xA9)
#define CS0_CTL         (*(volatile unsigned char __INTIO *)0xAA)
#define CS1_LBR         (*(volatile unsigned char __INTIO *)0xAB)
#define CS1_UBR         (*(volatile unsigned char __INTIO *)0xAC)
#define CS1_CTL         (*(volatile unsigned char __INTIO *)0xAD)
#define CS2_LBR         (*(volatile unsigned char __INTIO *)0xAE)
#define CS2_UBR         (*(volatile unsigned char __INTIO *)0xAF)
#define CS2_CTL         (*(volatile unsigned char __INTIO *)0xB0)
#define CS3_LBR         (*(volatile unsigned char __INTIO *)0xB1)
#define CS3_UBR         (*(volatile unsigned char __INTIO *)0xB2)
#define CS3_CTL         (*(volatile unsigned char __INTIO *)0xB3)

/* On-Chip Random Access Memory Control */
#define RAM_CTL         (*(volatile unsigned char __INTIO *)0xB4)
#define RAM_ADDR_U      (*(volatile unsigned char __INTIO *)0xB5)
#define MBIST_GPR       (*(volatile unsigned char __INTIO *)0xB6)
#define MBIST_EMR       (*(volatile unsigned char __INTIO *)0xB7)

/* Serial Peripheral Interface */
#define SPI_BRG_L       (*(volatile unsigned char __INTIO *)0xB8)
#define SPI_BRG_H       (*(volatile unsigned char __INTIO *)0xB9)
#define SPI_CTL         (*(volatile unsigned char __INTIO *)0xBA)
#define SPI_SR          (*(volatile unsigned char __INTIO *)0xBB)
#define SPI_TSR         (*(volatile unsigned char __INTIO *)0xBC)
#define SPI_RBR         (*(volatile unsigned char __INTIO *)0xBC)

/* Infrared Encoder/Decoder */
#define IR_CTL          (*(volatile unsigned char __INTIO *)0xBF)

/* Universal Asynchronous Receiver/Transmitter 0 (UART0) */
#define UART0_RBR       (*(volatile unsigned char __INTIO *)0xC0)
#define UART0_THR       (*(volatile unsigned char __INTIO *)0xC0)
#define UART0_BRG_L     (*(volatile unsigned char __INTIO *)0xC0)
#define UART0_IER       (*(volatile unsigned char __INTIO *)0xC1)
#define UART0_BRG_H     (*(volatile unsigned char __INTIO *)0xC1)
#define UART0_IIR       (*(volatile unsigned char __INTIO *)0xC2)
#define UART0_FCTL      (*(volatile unsigned char __INTIO *)0xC2)
#define UART0_LCTL      (*(volatile unsigned char __INTIO *)0xC3)
#define UART0_MCTL      (*(volatile unsigned char __INTIO *)0xC4)
#define UART0_LSR       (*(volatile unsigned char __INTIO *)0xC5)
#define UART0_MSR       (*(volatile unsigned char __INTIO *)0xC6)
#define UART0_SPR       (*(volatile unsigned char __INTIO *)0xC7)

/* Inter-Integrated Circuit Bus Control (I2C) */
#define I2C_SAR         (*(volatile unsigned char __INTIO *)0xC8)
#define I2C_XSAR        (*(volatile unsigned char __INTIO *)0xC9)
#define I2C_DR          (*(volatile unsigned char __INTIO *)0xCA)
#define I2C_CTL         (*(volatile unsigned char __INTIO *)0xCB)
#define I2C_SR          (*(volatile unsigned char __INTIO *)0xCC)
#define I2C_CCR         (*(volatile unsigned char __INTIO *)0xCC)
#define I2C_SRR         (*(volatile unsigned char __INTIO *)0xCD)

/* Universal Asynchronous Receiver/Transmitter 1 (UART1) */
#define UART1_RBR       (*(volatile unsigned char __INTIO *)0xD0)
#define UART1_THR       (*(volatile unsigned char __INTIO *)0xD0)
#define UART1_BRG_L     (*(volatile unsigned char __INTIO *)0xD0)
#define UART1_IER       (*(volatile unsigned char __INTIO *)0xD1)
#define UART1_BRG_H     (*(volatile unsigned char __INTIO *)0xD1)
#define UART1_IIR       (*(volatile unsigned char __INTIO *)0xD2)
#define UART1_FCTL      (*(volatile unsigned char __INTIO *)0xD2)
#define UART1_LCTL      (*(volatile unsigned char __INTIO *)0xD3)
#define UART1_MCTL      (*(volatile unsigned char __INTIO *)0xD4)
#define UART1_LSR       (*(volatile unsigned char __INTIO *)0xD5)
#define UART1_MSR       (*(volatile unsigned char __INTIO *)0xD6)
#define UART1_SPR       (*(volatile unsigned char __INTIO *)0xD7)

/* Low-Power Control */
#define CLK_PPD1        (*(volatile unsigned char __INTIO *)0xDB)
#define CLK_PPD2        (*(volatile unsigned char __INTIO *)0xDC)

/* Real-Time Clock */
#define RTC_SEC         (*(volatile unsigned char __INTIO *)0xE0)
#define RTC_MIN         (*(volatile unsigned char __INTIO *)0xE1)
#define RTC_HRS         (*(volatile unsigned char __INTIO *)0xE2)
#define RTC_DOW         (*(volatile unsigned char __INTIO *)0xE3)
#define RTC_DOM         (*(volatile unsigned char __INTIO *)0xE4)
#define RTC_MON         (*(volatile unsigned char __INTIO *)0xE5)
#define RTC_YR          (*(volatile unsigned char __INTIO *)0xE6)
#define RTC_CEN         (*(volatile unsigned char __INTIO *)0xE7)
#define RTC_ASEC        (*(volatile unsigned char __INTIO *)0xE8)
#define RTC_AMIN        (*(volatile unsigned char __INTIO *)0xE9)
#define RTC_AHRS        (*(volatile unsigned char __INTIO *)0xEA)
#define RTC_ADOW        (*(volatile unsigned char __INTIO *)0xEB)
#define RTC_ACTRL       (*(volatile unsigned char __INTIO *)0xEC)
#define RTC_CTRL        (*(volatile unsigned char __INTIO *)0xED)

/* Chip Select Bus Mode Control */
#define CS0_BMC         (*(volatile unsigned char __INTIO *)0xF0)
#define CS1_BMC         (*(volatile unsigned char __INTIO *)0xF1)
#define CS2_BMC         (*(volatile unsigned char __INTIO *)0xF2)
#define CS3_BMC         (*(volatile unsigned char __INTIO *)0xF3)

/* On-Chip Flash Memory Control */
#define FLASH_KEY       (*(volatile unsigned char __INTIO *)0xF5)
#define FLASH_DATA      (*(volatile unsigned char __INTIO *)0xF6)
#define FLASH_ADDR_U    (*(volatile unsigned char __INTIO *)0xF7)
#define FLASH_CTL       (*(volatile unsigned char __INTIO *)0xF8)
#define FLASH_FDIV      (*(volatile unsigned char __INTIO *)0xF9)
#define FLASH_PROT      (*(volatile unsigned char __INTIO *)0xFA)
#define FLASH_IRQ       (*(volatile unsigned char __INTIO *)0xFB)
#define FLASH_PAGE      (*(volatile unsigned char __INTIO *)0xFC)
#define FLASH_ROW       (*(volatile unsigned char __INTIO *)0xFD)
#define FLASH_COL       (*(volatile unsigned char __INTIO *)0xFE)
#define FLASH_PGCTL     (*(volatile unsigned char __INTIO *)0xFF)


/* Unspecified register definitions, retained for compatibility */
#define RAM_CTL0        RAM_CTL
#define FLASH_CTRL      FLASH_CTL
#define RTC_ACTL        RTC_ACTRL
#define RTC_CTL         RTC_CTRL


typedef volatile unsigned char __INTIO *ISFR;
typedef volatile unsigned char __EXTIO *XSFR;


/* Initializes the vector table with the default handler */
void _init_default_vectors(void);

/* Assigns a service routine to an interrupt vector */
void *_set_vector(unsigned int, void (*)(void));

/************************************************************************/
/* Interrupt vector offsets for set_vector                              */
/************************************************************************/
#define EMACRX_IVECT			0x40
#define EMACTX_IVECT			0x44
#define EMACSYS_IVECT			0x48
#define PLL_IVECT				0x4C
#define FLASH_IVECT				0x50

#define TIMER0_IVECT			0x54
#define TIMER1_IVECT			0x58
#define TIMER2_IVECT			0x5C
#define TIMER3_IVECT			0x60

#define RTC_IVECT				0x6C

#if !defined(UART0_IVECT) /*If it already defined using uart.h*/
#define UART0_IVECT				0x70
#endif
#if !defined(UART1_IVECT) /*If it already defined using uart.h*/
#define UART1_IVECT				0x74
#endif

#define I2C_IVECT				0x78
#define SPI_IVECT				0x7C

#define PORTA0_IVECT			0x80
#define PORTA1_IVECT			0x84
#define PORTA2_IVECT			0x88
#define PORTA3_IVECT			0x8C
#define PORTA4_IVECT			0x90
#define PORTA5_IVECT			0x94
#define PORTA6_IVECT			0x98
#define PORTA7_IVECT			0x9C

#define PORTB0_IVECT			0xA0
#define PORTB1_IVECT			0xA4
#define PORTB2_IVECT			0xA8
#define PORTB3_IVECT			0xAC
#define PORTB4_IVECT			0xB0
#define PORTB5_IVECT			0xB4
#define PORTB6_IVECT			0xB8
#define PORTB7_IVECT			0xBC

#define PORTC0_IVECT			0xC0
#define PORTC1_IVECT			0xC4
#define PORTC2_IVECT			0xC8
#define PORTC3_IVECT			0xCC
#define PORTC4_IVECT			0xD0
#define PORTC5_IVECT			0xD4
#define PORTC6_IVECT			0xD8
#define PORTC7_IVECT			0xDC

#define PORTD0_IVECT			0xE0
#define PORTD1_IVECT			0xE4
#define PORTD2_IVECT			0xE8
#define PORTD3_IVECT			0xEC
#define PORTD4_IVECT			0xF0
#define PORTD5_IVECT			0xF4
#define PORTD6_IVECT			0xF8
#define PORTD7_IVECT			0xFC

#endif  /* __eZ80F91_included */
