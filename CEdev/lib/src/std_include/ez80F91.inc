;************************************************************************
;*    eZ80F91.inc
;*
;*		eZ80F91 Registers
;*
;************************************************************************
;*
;* Start EZ80F91.inc 
;*

;*  PRODUCT_ID 

ZDI_ID_L:	.equ	%00
ZDI_ID_H:	.equ	%01
ZDI_ID_REV:	.equ	%02

;*  INTERRUPT 

INT_P0:	.equ	%10
INT_P1:	.equ	%11
INT_P2:	.equ	%12
INT_P3:	.equ	%13
INT_P4:	.equ	%14
INT_P5:	.equ	%15

;*  EMACC 

EMAC_TEST:	.equ	%20
EMAC_CFG1:	.equ	%21
EMAC_CFG2:	.equ	%22
EMAC_CFG3:	.equ	%23
EMAC_CFG4:	.equ	%24
EMAC_STAD_0:	.equ	%25
EMAC_STAD_1:	.equ	%26
EMAC_STAD_2:	.equ	%27
EMAC_STAD_3:	.equ	%28
EMAC_STAD_4:	.equ	%29
EMAC_STAD_5:	.equ	%2A
EMAC_TPTV_L:	.equ	%2B
EMAC_TPTV_H:	.equ	%2C
EMAC_IPGT:	.equ	%2D
EMAC_IPGR1:	.equ	%2E
EMAC_IPGR2:	.equ	%2F
EMAC_MAXF_L:	.equ	%30
EMAC_MAXF_H:	.equ	%31
EMAC_AFR:	.equ	%32
EMAC_HTBL_0:	.equ	%33
EMAC_HTBL_1:	.equ	%34
EMAC_HTBL_2:	.equ	%35
EMAC_HTBL_3:	.equ	%36
EMAC_HTBL_4:	.equ	%37
EMAC_HTBL_5:	.equ	%38
EMAC_HTBL_6:	.equ	%39
EMAC_HTBL_7:	.equ	%3A
EMAC_MIIMGT:	.equ	%3B
EMAC_CTLD_L:	.equ	%3C
EMAC_CTLD_H:	.equ	%3D
EMAC_RGAD:	.equ	%3E
EMAC_FIAD:	.equ	%3F
EMAC_PTMR:	.equ	%40
EMAC_RST:	.equ	%41
EMAC_TLBP_L:	.equ	%42
EMAC_TLBP_H:	.equ	%43
EMAC_BP_L:	.equ	%44
EMAC_BP_H:	.equ	%45
EMAC_BP_U:	.equ	%46
EMAC_RHBP_L:	.equ	%47
EMAC_RHBP_H:	.equ	%48
EMAC_RRP_L:	.equ	%49
EMAC_RRP_H:	.equ	%4A
EMAC_BUFSZ:	.equ	%4B
EMAC_IEN:	.equ	%4C
EMAC_ISTAT:	.equ	%4D
EMAC_PRSD_L:	.equ	%4E
EMAC_PRSD_H:	.equ	%4F
EMAC_MIISTAT:	.equ	%50
EMAC_RWP_L:	.equ	%51
EMAC_RWP_H:	.equ	%52
EMAC_TRP_L:	.equ	%53
EMAC_TRP_H:	.equ	%54
EMAC_BLKSLFT_L:	.equ	%55
EMAC_BLKSLFT_H:	.equ	%56
EMAC_FDATA_L:	.equ	%57
EMAC_FDATA_H:	.equ	%58
EMAC_FFLAGS:	.equ	%59
EMAC_FLAGS:	.equ	%59

;*  PLL 

PLL_DIV_L:	.equ	%5C
PLL_DIV_H:	.equ	%5D
PLL_CTL0:	.equ	%5E
PLL_CTL1:	.equ	%5F

;*  TIMER 

TMR0_CTL:	.equ	%60
TMR0_IER:	.equ	%61
TMR0_IIR:	.equ	%62
TMR0_DR_L:	.equ	%63
TMR0_RR_L:	.equ	%63
TMR0_DR_H:	.equ	%64
TMR0_RR_H:	.equ	%64
TMR1_CTL:	.equ	%65
TMR1_IER:	.equ	%66
TMR1_IIR:	.equ	%67
TMR1_DR_L:	.equ	%68
TMR1_RR_L:	.equ	%68
TMR1_DR_H:	.equ	%69
TMR1_RR_H:	.equ	%69
TMR1_CAP_CTL:	.equ	%6A
TMR1_CAPA_L:	.equ	%6B
TMR1_CAPA_H:	.equ	%6C
TMR1_CAPB_L:	.equ	%6D
TMR1_CAPB_H:	.equ	%6E
TMR2_CTL:	.equ	%6F
TMR2_IER:	.equ	%70
TMR2_IIR:	.equ	%71
TMR2_DR_L:	.equ	%72
TMR2_RR_L:	.equ	%72
TMR2_DR_H:	.equ	%73
TMR2_RR_H:	.equ	%73
TMR3_CTL:	.equ	%74
TMR3_IER:	.equ	%75
TMR3_IIR:	.equ	%76
TMR3_DR_L:	.equ	%77
TMR3_RR_L:	.equ	%77
TMR3_DR_H:	.equ	%78
TMR3_RR_H:	.equ	%78
TMR3_CAP_CTL:	.equ	%7B
TMR3_CAPA_L:	.equ	%7C
TMR3_CAPA_H:	.equ	%7D
TMR3_CAPB_L:	.equ	%7E
TMR3_CAPB_H:	.equ	%7F
TMR3_OC_CTL1:	.equ	%80
TMR3_OC_CTL2:	.equ	%81
TMR3_OC0_L:	.equ	%82
TMR3_OC0_H:	.equ	%83
TMR3_OC1_L:	.equ	%84
TMR3_OC1_H:	.equ	%85
TMR3_OC2_L:	.equ	%86
TMR3_OC2_H:	.equ	%87
TMR3_OC3_L:	.equ	%88
TMR3_OC3_H:	.equ	%89

;*  PWM 

PWM_CTL1:	.equ	%79
PWM_CTL2:	.equ	%7A
PWM_CTL3:	.equ	%7B
PWM0R_L:	.equ	%7C
PWM0R_H:	.equ	%7D
PWM1R_L:	.equ	%7E
PWM1R_H:	.equ	%7F
PWM2R_L:	.equ	%80
PWM2R_H:	.equ	%81
PWM3R_L:	.equ	%82
PWM3R_H:	.equ	%83
PWM0F_L:	.equ	%84
PWM0F_H:	.equ	%85
PWM1F_L:	.equ	%86
PWM1F_H:	.equ	%87
PWM2F_L:	.equ	%88
PWM2F_H:	.equ	%89
PWM3F_L:	.equ	%8A
PWM3F_H:	.equ	%8B

;*  WDT 

WDT_CTL:	.equ	%93
WDT_RR:		.equ	%94

;*  PORT 

PA_DR:		.equ	%96
PA_DDR:		.equ	%97
PA_ALT0:	.equ	%A6
PA_ALT1:	.equ	%98
PA_ALT2:	.equ	%99
PB_DR:		.equ	%9A
PB_DDR:		.equ	%9B
PB_ALT0:	.equ	%A7
PB_ALT1:	.equ	%9C
PB_ALT2:	.equ	%9D
PC_DR:		.equ	%9E
PC_DDR:		.equ	%9F
PC_ALT0:	.equ	%CE
PC_ALT1:	.equ	%A0
PC_ALT2:	.equ	%A1
PD_DR:		.equ	%A2
PD_DDR:		.equ	%A3
PD_ALT0:	.equ	%CF
PD_ALT1:	.equ	%A4
PD_ALT2:	.equ	%A5

;*  CS 

CS0_LBR:	.equ	%A8
CS0_UBR:	.equ	%A9
CS0_CTL:	.equ	%AA
CS1_LBR:	.equ	%AB
CS1_UBR:	.equ	%AC
CS1_CTL:	.equ	%AD
CS2_LBR:	.equ	%AE
CS2_UBR:	.equ	%AF
CS2_CTL:	.equ	%B0
CS3_LBR:	.equ	%B1
CS3_UBR:	.equ	%B2
CS3_CTL:	.equ	%B3

;*  RAMCTL 

RAM_CTL:	.equ	%B4
RAM_CTL0:	.equ	%B4
RAM_ADDR_U:	.equ	%B5
MBIST_GPR:	.equ	%B6
MBIST_EMR:	.equ	%B7

;*  SPI 

SPI_BRG_L:	.equ	%B8
SPI_BRG_H:	.equ	%B9
SPI_CTL:	.equ	%BA
SPI_SR:		.equ	%BB
SPI_RBR:	.equ	%BC
SPI_TSR:	.equ	%BC

;*  UART0 

UART0_RBR:	.equ	%C0
UART0_THR:	.equ	%C0
UART0_BRG_L:	.equ	%C0
UART0_IER:	.equ	%C1
UART0_BRG_H:	.equ	%C1
UART0_IIR:	.equ	%C2
UART0_FCTL:	.equ	%C2
UART0_LCTL:	.equ	%C3
UART0_MCTL:	.equ	%C4
UART0_LSR:	.equ	%C5
UART0_MSR:	.equ	%C6
UART0_SPR:	.equ	%C7

;*  I2C 
I2C_SAR:	.equ	%C8
I2C_XSAR:	.equ	%C9
I2C_DR:		.equ	%CA
I2C_CTL:	.equ	%CB
I2C_SR:		.equ	%CC
I2C_CCR:	.equ	%CC
I2C_SRR:	.equ	%CD

;*  UART1 

UART1_RBR:	.equ	%D0
UART1_THR:	.equ	%D0
UART1_BRG_L:	.equ	%D0
UART1_IER:	.equ	%D1
UART1_BRG_H:	.equ	%D1
UART1_IIR:	.equ	%D2
UART1_FCTL:	.equ	%D2
UART1_LCTL:	.equ	%D3
UART1_MCTL:	.equ	%D4
UART1_LSR:	.equ	%D5
UART1_MSR:	.equ	%D6
UART1_SPR:	.equ	%D7

;*  IR 

IR_CTL:	.equ	%BF

;*  CLK 

CLK_PPD1:	.equ	%DB
CLK_PPD2:	.equ	%DC

;*  RTC 

RTC_SEC:	.equ	%E0
RTC_MIN:	.equ	%E1
RTC_HRS:	.equ	%E2
RTC_DOW:	.equ	%E3
RTC_DOM:	.equ	%E4
RTC_MON:	.equ	%E5
RTC_YR:		.equ	%E6
RTC_CEN:	.equ	%E7
RTC_ASEC:	.equ	%E8
RTC_AMIN:	.equ	%E9
RTC_AHRS:	.equ	%EA
RTC_ADOW:	.equ	%EB
RTC_ACTRL:	.equ	%EC
RTC_CTRL:	.equ	%ED

;*  CSBMC 

CS0_BMC:	.equ	%F0
CS1_BMC:	.equ	%F1
CS2_BMC:	.equ	%F2
CS3_BMC:	.equ	%F3

;*  FLASH 

FLASH_KEY:	.equ	%F5
FLASH_DATA:	.equ	%F6
FLASH_ADDR_U:	.equ	%F7
FLASH_CTRL:	.equ	%F8
FLASH_FDIV:	.equ	%F9
FLASH_PROT:	.equ	%FA
FLASH_IRQ:	.equ	%FB
FLASH_PAGE:	.equ	%FC
FLASH_ROW:	.equ	%FD
FLASH_COL:	.equ	%FE
FLASH_PGCTL:	.equ	%FF

;* End  EZ80F91.inc
