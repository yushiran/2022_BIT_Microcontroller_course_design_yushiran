/*--------------------------------------------------------------------------
HC89F0541.H

Header file for generic HC89F0541 series microcontroller.
Copyright (c) 2009-2017 Shanghai Holychip Electronic Technology Co., Ltd.
All rights reserved11.
--------------------------------------------------------------------------*/
#ifndef __HC89F0541_H__
#define __HC89F0541_H__

#include "HC_DEFINE.H"

/* ------------------- BYTE Register-------------------- */
/* CPU */
sfr PSW        = 0xD0;            
sfr ACC        = 0xE0;
sfr B 	       = 0xF0;
sfr SP         = 0x81;
sfr DPL        = 0x82;
sfr DPH        = 0x83;
sfr INSCON     = 0xA2;
sfr16 DPTR     = 0x82;

/* SYS CLOCK  */
sfr CLKSWR     = 0x8E;
sfr CLKCON     = 0x8F;

/* power  */
sfr PCON       = 0x87;

/* FLASH */
sfr IAP_ADDRL  = 0xF9;
sfr IAP_ADDRH  = 0xFA;
sfr IAP_DATA   = 0xFB;
sfr IAP_CMDL   = 0xFC;
sfr IAP_CMDH   = 0xFD; 
  
sfr16 IAP_ADDR = 0xF9;
sfr16 IAP_CMD  = 0xFC;

/* REST */
sfr RSTFR      = 0xF8;

/* WDT  */
sfr WDTC       = 0xBD;

/* INTERRUPT */
sfr IE         = 0xA8;
sfr IE1        = 0xB8;
sfr IE2        = 0xD8;
sfr IP0        = 0xA9;
sfr IP1        = 0xAA;
sfr IP2        = 0xB9;
sfr IP3        = 0xBA;


sfr PINTF0     = 0x96;
sfr PINTF1     = 0x97;
sfr PINTF2     = 0x9F;
                  
/* PORT */
sfr P0 	       = 0x80;       
sfr P1 	       = 0x90;            
sfr P2 	       = 0xA0;            
sfr P3 	       = 0xB0;  

/* TIMER */
sfr TCON       = 0x88;
sfr TMOD       = 0x89;
sfr TL0        = 0x8A;
sfr TL1        = 0x8B;
sfr TH0        = 0x8C;
sfr TH1        = 0x8D;

sfr T3CON      = 0xC9;
sfr TL3        = 0xCA;
sfr TH3        = 0xCB;
sfr16 T3       = 0xCA;

sfr T4CON      = 0xCC;
sfr TL4        = 0xCD;
sfr TH4        = 0xCE;
sfr16 T4       = 0xCD;

sfr T5CON      = 0xC1;
sfr TL5        = 0xC2;
sfr TH5        = 0xC3;
sfr RCAP5L     = 0xC4;
sfr RCAP5H     = 0xC5;
sfr16 T5       = 0xC2;
sfr16 RCAP5    = 0xC4;

/* UART */
sfr SCON       = 0x98;
sfr SBUF       = 0x99;
sfr SADDR      = 0x9A;
sfr SADEN      = 0x9B;
sfr SCON2      = 0x9E;

/* SPI */
sfr SPDAT      = 0xAB;
sfr SPCTL      = 0xAC;
sfr SPSTAT     = 0xAD;

/* IIC */
sfr IICCON     = 0xA6;
sfr IICSTA     = 0xA7;
sfr IICDAT     = 0xAE;
sfr IICADR     = 0xAF;

/* ADC */
sfr ADCC0      = 0xB4;
sfr ADCC1      = 0xB5;
sfr ADCRL      = 0xB6;
sfr ADCRH      = 0xB7;
sfr16 ADCR     = 0xB6;

/* LCD */
sfr LCDCON     = 0xD1;

/* CRC */
sfr CRCL       = 0xBE;
sfr CRCH       = 0xBF;
sfr16 CRCR     = 0xBE;

/* PWM */
sfr PWM0C      = 0xDA;
sfr PWM1C      = 0xDB;
sfr PWM2C      = 0xDC;
sfr PWM3C      = 0xDD;
sfr PWM3P      = 0xDE;
sfr PWM3D      = 0xDF;
sfr PWMEN      = 0xE1;
sfr PWM0PL     = 0xE2;
sfr PWM0PH     = 0xE3;
sfr PWM0DL     = 0xE4;
sfr PWM0DH     = 0xE5;
sfr PWM0DTL    = 0xE6;
sfr PWM0DTH    = 0xE7;
sfr FLTMODE    = 0xE9;
sfr PWM1PL     = 0xEA;
sfr PWM1PH     = 0xEB;
sfr PWM1DL     = 0xEC;
sfr PWM1DH     = 0xED;
sfr PWM1DTL    = 0xEE;
sfr PWM1DTH    = 0xEF;
sfr PWMM       = 0xF1;
sfr PWM2PL     = 0xF2;
sfr PWM2PH     = 0xF3;
sfr PWM2DL     = 0xF4;
sfr PWM2DH     = 0xF5;
sfr PWM2DTL    = 0xF6;
sfr PWM2DTH    = 0xF7;

sfr16 PWM0P    = 0xE2;
sfr16 PWM0D    = 0xE4;
sfr16 PWM0DT   = 0xE6;
sfr16 PWM1P    = 0xEA;
sfr16 PWM1D    = 0xEC;
sfr16 PWM1DT   = 0xEE;
sfr16 PWM2P    = 0xF2;
sfr16 PWM2D    = 0xF4;
sfr16 PWM2DT   = 0xF6;

/* LVD */
sfr LVDC       = 0xBB;

/*--------------------------  BIT Register -------------------- */
/*  PSW   */
sbit CY        = PSW^7;
sbit AC        = PSW^6;
sbit F0        = PSW^5;
sbit RS1       = PSW^4;
sbit RS0       = PSW^3;
sbit OV        = PSW^2;
sbit F1        = PSW^1;
sbit P         = PSW^0;

/*  IE   */ 
sbit EA        = IE^7;
sbit ES2       = IE^6;
sbit EWDT      = IE^5;
sbit ES1       = IE^4;
sbit ET1       = IE^3;
sbit EX1       = IE^2;
sbit ET0       = IE^1;
sbit EX0       = IE^0;

/*  IE1   */ 
sbit EX2_7     = IE1^7;
sbit EADC      = IE1^6;
sbit ET5       = IE1^4;
sbit ET4       = IE1^3;
sbit ET3       = IE1^2;
sbit EIIC      = IE1^1;
sbit ESPI      = IE1^0;

/*  IE2   */ 
sbit EXP2      = IE2^1;
sbit EX8_17    = IE2^0;

/*  RSTFR   */ 
sbit PORF      = RSTFR^7;
sbit EXRSTF    = RSTFR^6;
sbit BORF      = RSTFR^5;
sbit WDTRF     = RSTFR^4;
sbit SWRF      = RSTFR^3;
sbit SPOVF     = RSTFR^1;
sbit PLVRSTF   = RSTFR^0;

/*  SCON  */
sbit FE      = SCON^7;
sbit RXOV    = SCON^6;
sbit TXCOL   = SCON^5;
sbit REN     = SCON^4;
sbit TB8     = SCON^3;
sbit RB8     = SCON^2;
sbit TI      = SCON^1;
sbit RI      = SCON^0;

/*  TCON  */
sbit TF1       = TCON^7;
sbit TR1       = TCON^6;
sbit TF0       = TCON^5;
sbit TR0       = TCON^4;

/* P0 */
sbit P0_0      = P0^0;
sbit P0_1      = P0^1;
sbit P0_2      = P0^2;
sbit P0_3      = P0^3;
sbit P0_4      = P0^4;
sbit P0_5      = P0^5;
sbit P0_6      = P0^6;
sbit P0_7      = P0^7;

/* P1 */
sbit P1_0      = P1^0;
sbit P1_1      = P1^1;
sbit P1_2      = P1^2;
sbit P1_3      = P1^3;
sbit P1_4      = P1^4;
sbit P1_5      = P1^5;
sbit P1_6      = P1^6;
sbit P1_7      = P1^7;

/* P2 */
sbit P2_0      = P2^0;
sbit P2_1      = P2^1;
sbit P2_2      = P2^2;
sbit P2_3      = P2^3;
sbit P2_4      = P2^4;
sbit P2_5      = P2^5;
sbit P2_6      = P2^6;
sbit P2_7      = P2^7;

/* P3 */
sbit P3_0      = P3^0;
sbit P3_1      = P3^1;
sbit P3_2      = P3^2;
sbit P3_3      = P3^3;
sbit P3_4      = P3^4;
sbit P3_5      = P3^5;


#ifdef ALLOCATE_EXTERN
#define EXTERN
#define _AT_ _at_
#else
#define EXTERN extern
#define _AT_ ;/ ## /
#endif

 /* XSFR_TIMER */ 
EXTERN xdata volatile BYTE TCON1              _AT_ 0xFE80;  // 

 /* XSFR_PCA */ 
EXTERN xdata volatile BYTE T5CON1             _AT_ 0xFE85;  //

 /* XSFR_UART2 */ 
EXTERN xdata volatile BYTE S2CON              _AT_ 0xFE88;  // 
EXTERN xdata volatile BYTE S2CON2             _AT_ 0xFE89;  //
EXTERN xdata volatile BYTE S2BUF              _AT_ 0xFE8A;  //

 /* XSFR_SYSCLK */ 
EXTERN xdata volatile BYTE CLKDIV             _AT_ 0xFE91;  // 
EXTERN xdata volatile BYTE FREQ_CLK           _AT_ 0xFE92;  // 
EXTERN xdata volatile BYTE CLKOUT             _AT_ 0xFE93;  // 
EXTERN xdata volatile BYTE XTALCFG            _AT_ 0xFE94;  // 
EXTERN xdata volatile BYTE SPOV_RSTEN         _AT_ 0xFE95;  // 

 /* XSFR_ADC */ 
EXTERN xdata volatile BYTE ADCC2              _AT_ 0xFE9B;  //

 /* XSFR_WDT */ 
EXTERN xdata volatile BYTE WDTCCR             _AT_ 0xFEA0;  // 

 /* XSFR_CRC */ 
EXTERN xdata volatile BYTE CRCC               _AT_ 0xFEA2;  // 

 /* XSFR_BOR */ 
EXTERN xdata volatile BYTE BORC               _AT_ 0xFEA4;  // 
EXTERN xdata volatile BYTE BORDBC             _AT_ 0xFEA5;  // 


 /* XSFR_LVD */ 
EXTERN xdata volatile BYTE LVDDBC             _AT_ 0xFEA7;  // 

 /* XSFR_RST */ 
EXTERN xdata volatile BYTE RSTDBC             _AT_ 0xFEAA;  // 

 /* XSFR_PITS */ 
EXTERN xdata volatile BYTE PITS0              _AT_ 0xFEB0;  // 
EXTERN xdata volatile BYTE PITS1              _AT_ 0xFEB1;  // 
EXTERN xdata volatile BYTE PITS2              _AT_ 0xFEB2;  // 
EXTERN xdata volatile BYTE PITS3              _AT_ 0xFEB3;  //
EXTERN xdata volatile BYTE PITS4              _AT_ 0xFEB4;  //

EXTERN xdata volatile BYTE PINTE0             _AT_ 0xFEB8;  //
EXTERN xdata volatile BYTE PINTE1             _AT_ 0xFEB9;  //
EXTERN xdata volatile BYTE PINTE2             _AT_ 0xFEBA;  //

EXTERN xdata volatile BYTE P2INTE             _AT_ 0xFEBC;  //

EXTERN xdata volatile BYTE TRMEN              _AT_ 0xFEBD;  //

EXTERN xdata volatile BYTE TRMV               _AT_ 0xFEBE;  //

 /* XSFR_PITS */ 
EXTERN xdata volatile BYTE SCANCON            _AT_ 0xFEC0;  //
EXTERN xdata volatile BYTE SCCH0              _AT_ 0xFED0;  //
EXTERN xdata volatile BYTE SCCH1              _AT_ 0xFED1;  //
EXTERN xdata volatile BYTE SCCH2              _AT_ 0xFED2;  //
EXTERN xdata volatile BYTE SCCH3              _AT_ 0xFED3;  //

EXTERN xdata volatile u16  SCR0               _AT_ 0xFEE0;
EXTERN xdata volatile u16  SCR1               _AT_ 0xFEE2;
EXTERN xdata volatile u16  SCR2               _AT_ 0xFEE4;
EXTERN xdata volatile u16  SCR3               _AT_ 0xFEE6;
EXTERN xdata volatile u16  SCR4               _AT_ 0xFEE8;
EXTERN xdata volatile u16  SCR5               _AT_ 0xFEEA;
EXTERN xdata volatile u16  SCR6               _AT_ 0xFEEC;
EXTERN xdata volatile u16  SCR7               _AT_ 0xFEEE;

 /* XSFR_PORT */ 
EXTERN xdata volatile BYTE P0M0               _AT_ 0xFF00;  //P0[0] mode set
EXTERN xdata volatile BYTE P0M1               _AT_ 0xFF01;  //P0[1] mode set 
EXTERN xdata volatile BYTE P0M2               _AT_ 0xFF02;  //P0[2] mode set 
EXTERN xdata volatile BYTE P0M3               _AT_ 0xFF03;  //P0[3] mode set 
EXTERN xdata volatile BYTE P0M4               _AT_ 0xFF04;  //P0[4] mode set
EXTERN xdata volatile BYTE P0M5               _AT_ 0xFF05;  //P0[5] mode set 
EXTERN xdata volatile BYTE P0M6               _AT_ 0xFF06;  //P0[6] mode set 
EXTERN xdata volatile BYTE P0M7               _AT_ 0xFF07;  //P0[7] mode set 

EXTERN xdata volatile BYTE P1M0               _AT_ 0xFF08;  //P1[0] mode set
EXTERN xdata volatile BYTE P1M1               _AT_ 0xFF09;  //P1[1] mode set 
EXTERN xdata volatile BYTE P1M2               _AT_ 0xFF0A;  //P1[2] mode set 
EXTERN xdata volatile BYTE P1M3               _AT_ 0xFF0B;  //P1[3] mode set 
EXTERN xdata volatile BYTE P1M4               _AT_ 0xFF0C;  //P1[4] mode set
EXTERN xdata volatile BYTE P1M5               _AT_ 0xFF0D;  //P1[5] mode set 
EXTERN xdata volatile BYTE P1M6               _AT_ 0xFF0E;  //P1[6] mode set 
EXTERN xdata volatile BYTE P1M7               _AT_ 0xFF0F;  //P1[7] mode set 

EXTERN xdata volatile BYTE P2M0               _AT_ 0xFF10;  //P2[0] mode set
EXTERN xdata volatile BYTE P2M1               _AT_ 0xFF11;  //P2[1] mode set 
EXTERN xdata volatile BYTE P2M2               _AT_ 0xFF12;  //P2[2] mode set 
EXTERN xdata volatile BYTE P2M3               _AT_ 0xFF13;  //P2[3] mode set 
EXTERN xdata volatile BYTE P2M4               _AT_ 0xFF14;  //P2[4] mode set
EXTERN xdata volatile BYTE P2M5               _AT_ 0xFF15;  //P2[5] mode set 
EXTERN xdata volatile BYTE P2M6               _AT_ 0xFF16;  //P2[6] mode set 
EXTERN xdata volatile BYTE P2M7               _AT_ 0xFF17;  //P2[7] mode set 

EXTERN xdata volatile BYTE P3M0               _AT_ 0xFF18;  //P3[0] mode set
EXTERN xdata volatile BYTE P3M1               _AT_ 0xFF19;  //P3[1] mode set 
EXTERN xdata volatile BYTE P3M2               _AT_ 0xFF1A;  //P3[2] mode set
EXTERN xdata volatile BYTE P3M3               _AT_ 0xFF1B;  //P3[3] mode set 
EXTERN xdata volatile BYTE P3M4               _AT_ 0xFF1C;  //P3[4] mode set
EXTERN xdata volatile BYTE P3M5               _AT_ 0xFF1D;  //P3[5] mode set 
 
 /* XSFR_MAP */ 
EXTERN xdata volatile BYTE P00DBC             _AT_ 0xFF40;  //  
EXTERN xdata volatile BYTE P01DBC             _AT_ 0xFF41;  //  
EXTERN xdata volatile BYTE P02DBC             _AT_ 0xFF42;  //  

EXTERN xdata volatile BYTE COMP3EN            _AT_ 0xFF60;  //  
EXTERN xdata volatile BYTE COMP2EN            _AT_ 0xFF61;  // 
EXTERN xdata volatile BYTE COMP1EN            _AT_ 0xFF62;  // 
EXTERN xdata volatile BYTE COMP0EN            _AT_ 0xFF63;  // 

EXTERN xdata volatile BYTE SEGP3EN            _AT_ 0xFF68;  //  
EXTERN xdata volatile BYTE SEGP2EN            _AT_ 0xFF69;  // 
EXTERN xdata volatile BYTE SEGP1EN            _AT_ 0xFF6A;  // 
EXTERN xdata volatile BYTE SEGP0EN            _AT_ 0xFF6B;  //  

 /* XSFR_MAP */ 
EXTERN xdata volatile BYTE T0_MAP             _AT_ 0xFF80;  //  
EXTERN xdata volatile BYTE T1_MAP             _AT_ 0xFF81;  // 
EXTERN xdata volatile BYTE T3_MAP             _AT_ 0xFF83;  //
EXTERN xdata volatile BYTE T4_MAP             _AT_ 0xFF84;  // 
EXTERN xdata volatile BYTE T5_MAP             _AT_ 0xFF85;  // 
EXTERN xdata volatile BYTE CLKO_MAP           _AT_ 0xFF8F;  //

EXTERN xdata volatile BYTE PWM0_MAP           _AT_ 0xFF90;  // 
EXTERN xdata volatile BYTE PWM01_MAP          _AT_ 0xFF91;  // 
 
EXTERN xdata volatile BYTE PWM1_MAP           _AT_ 0xFF94;  // 
EXTERN xdata volatile BYTE PWM11_MAP          _AT_ 0xFF95;  // 

EXTERN xdata volatile BYTE PWM2_MAP           _AT_ 0xFF98;  //
EXTERN xdata volatile BYTE PWM21_MAP          _AT_ 0xFF99;  //

EXTERN xdata volatile BYTE PWM3_MAP           _AT_ 0xFF9C;  //

EXTERN xdata volatile BYTE TXD_MAP            _AT_ 0xFFA0;  //
EXTERN xdata volatile BYTE RXD_MAP            _AT_ 0xFFA1;  //
EXTERN xdata volatile BYTE SCL_MAP            _AT_ 0xFFA2;  //
EXTERN xdata volatile BYTE SDA_MAP            _AT_ 0xFFA3;  //
EXTERN xdata volatile BYTE SS_MAP             _AT_ 0xFFA4;  //
EXTERN xdata volatile BYTE SCK_MAP            _AT_ 0xFFA5;  //
EXTERN xdata volatile BYTE MOSI_MAP           _AT_ 0xFFA6;  //
EXTERN xdata volatile BYTE MISO_MAP           _AT_ 0xFFA7;  //
EXTERN xdata volatile BYTE TXD2_MAP           _AT_ 0xFFA8;  // 
EXTERN xdata volatile BYTE RXD2_MAP           _AT_ 0xFFA9;  //

 /* XSFR */ 

#undef EXTERN
#undef _AT_

#define bmBIT0   0x01
#define bmBIT1   0x02
#define bmBIT2   0x04
#define bmBIT3   0x08
#define bmBIT4   0x10
#define bmBIT5   0x20
#define bmBIT6   0x40
#define bmBIT7   0x80
 
 /* CLKCON Bit Masks */  
#define bmHXTALRDY           bmBIT7
#define bmLXTALRDY           bmBIT6
#define bmHSRCRDY            bmBIT5
#define bmLSRCRDY            bmBIT4
#define bmXTALEN             bmBIT2
#define bmHSRCEN             bmBIT1

 /* CLKSWR Bit Masks */
#define bmCLKSTA            (bmBIT7 | bmBIT6)
#define bmCLKSEL            (bmBIT5 | bmBIT4)
#define bmRC32M_DIV         (bmBIT1 | bmBIT0)

 /* PCON Bit Masks */
#define bmGF1                bmBIT3
#define bmGF0                bmBIT2
#define bmPD                 bmBIT1
#define bmIDL                bmBIT0

 /* BORC Bit Masks */
#define bmBOREN              bmBIT7
#define bmBOR_DBC_EN         bmBIT6
#define bmBORVS             (bmBIT2 | bmBIT1 | bmBIT0)

 /* PINTE0 Bit Masks */
#define bmEINT7              bmBIT7
#define bmEINT6              bmBIT6
#define bmEINT5              bmBIT5
#define bmEINT4              bmBIT4
#define bmEINT3              bmBIT3
#define bmEINT2              bmBIT2

 /* PINTE1 Bit Masks */
#define bmEINT15             bmBIT7
#define bmEINT14             bmBIT6
#define bmEINT13             bmBIT5
#define bmEINT12             bmBIT4
#define bmEINT11             bmBIT3
#define bmEINT10             bmBIT2
#define bmEINT9              bmBIT1
#define bmEINT8              bmBIT0


 /* PINTE2 Bit Masks */
#define bmEINT17             bmBIT1
#define bmEINT16             bmBIT0

 /* PINTF0 Bit Masks */
#define bmINT7F              bmBIT7
#define bmINT6F              bmBIT6
#define bmINT5F              bmBIT5
#define bmINT4F              bmBIT4
#define bmINT3F              bmBIT3
#define bmINT2F              bmBIT2
#define bmINT1F              bmBIT1
#define bmINT0F              bmBIT0

 /* PINTF1 Bit Masks */
#define bmINT15F             bmBIT7
#define bmINT14F             bmBIT6
#define bmINT13F             bmBIT5
#define bmINT12F             bmBIT4
#define bmINT11F             bmBIT3
#define bmINT10F             bmBIT2
#define bmINT9F              bmBIT1
#define bmINT8F              bmBIT0

/* PINTF2 Bit Masks */
#define P2INTF            	 bmBIT7
#define bmINT17F             bmBIT1
#define bmINT16F             bmBIT0

 /* TCON1 Bit Masks */
#define bmT1OUT              bmBIT5
#define bmT1X12              bmBIT4
#define bmT0OUT              bmBIT1
#define bmT0X12              bmBIT0

 /* TMOD Bit Masks */
#define bmGATE1              bmBIT7
#define bmCT1                bmBIT6
#define bmT1MODE            (bmBIT5 | bmBIT4)
#define bmGATE0              bmBIT3
#define bmCT0                bmBIT2
#define bmT0MODE            (bmBIT1 | bmBIT0)

 /* T3CON Bit Masks */
#define bmTF3                bmBIT7
#define bmT3PD_EN            bmBIT6
#define bmT3PS              (bmBIT5 | bmBIT4)
#define bmTR3                bmBIT2
#define bmT3CLKS            (bmBIT1 | bmBIT0)

 /* T4CON Bit Masks */
#define bmTF4                bmBIT7
#define bmTC4                bmBIT6
#define bmT4PS              (bmBIT5 | bmBIT4)
#define bmT4M               (bmBIT3 | bmBIT2)
#define bmTR4                bmBIT1
#define bmT4CLKS             bmBIT0

 /* T5CON Bit Masks */
#define bmTF5                bmBIT7
#define bmEXF5               bmBIT6
#define bmT5PS              (bmBIT5 | bmBIT4)
#define bmT5M               (bmBIT3 | bmBIT2)
#define bmTR5                bmBIT1
#define bmEXEN5              bmBIT0

 /* T5CON1 Bit Masks */
#define bmCAPM              (bmBIT1 | bmBIT0)

 /* PWMEN Bit Masks */
#define PWM21EN     		bmBIT6
#define PWM11EN				bmBIT5
#define PWM01EN             bmBIT4
#define PWM2EN   			bmBIT2
#define PWM1EN 	            bmBIT1
#define PWM0EN              bmBIT0

 /* PWMM Bit Masks */
#define EFLT2     		    bmBIT7
#define PWM2M				bmBIT6
#define PWM1M               bmBIT5
#define PWM0M   			bmBIT4
#define RELOAD2 	        bmBIT2
#define RELOAD1             bmBIT1
#define RELOAD0             bmBIT0

 /* FLTMODE Bit Masks */
#define EFLT1     		    bmBIT7
#define EFLT0 				bmBIT6
#define FLT2_MODE           (bmBIT5 | bmBIT4)
#define FLT1_MODE  			(bmBIT3 | bmBIT2)
#define FLT0_MODE 	        (bmBIT1 | bmBIT0)

  /* PWM0C Bit Masks */
#define bmPWM0IE            bmBIT7
#define bmPWM0IF            bmBIT6
#define bmFLT0S             bmBIT5
#define bmFLT0C             bmBIT4
#define bmPWM0S            (bmBIT3 | bmBIT2)
#define bmCK0              (bmBIT1 | bmBIT0)

 /* PWM1C Bit Masks */
#define bmPWM1IE            bmBIT7
#define bmPWM1IF            bmBIT6
#define bmFLT1S             bmBIT5
#define bmFLT1C             bmBIT4
#define bmPWM1S            (bmBIT3 | bmBIT2)
#define bmCK1              (bmBIT1 | bmBIT0)

 /* PWM2C Bit Masks */
#define bmPWM2IE            bmBIT7
#define bmPWM2IF            bmBIT6
#define bmFLT2S             bmBIT5
#define bmFLT2C             bmBIT4
#define bmPWM2S            (bmBIT3 | bmBIT2)
#define bmCK2              (bmBIT1 | bmBIT0)


 /* PWM3C Bit Masks */
#define bmPWM3EN             bmBIT7
#define bmPWM3IE             bmBIT6
#define bmPWM3IF             bmBIT5
#define bmPWM3OEN            bmBIT4
#define bmPWM3S              bmBIT3
#define bmPTCK3             (bmBIT2 | bmBIT1 | bmBIT0)

 /* WDTC Bit Masks */
#define bmWDTF               bmBIT5
#define bmWDTCLR             bmBIT4
#define bmWDTPD              bmBIT3
#define bmWDTPS             (bmBIT2 | bmBIT1 | bmBIT0)

 /* SCON Bit Masks */
#define bmUART_FE            bmBIT7
#define bmUART_RXROV         bmBIT6
#define bmUART_TXCOL         bmBIT5
#define bmUART_REN           bmBIT4
#define bmUART_TB8           bmBIT3
#define bmUART_RB8           bmBIT2
#define bmUART_TI            bmBIT1
#define bmUART_RI            bmBIT0

 /* SCON2 Bit Masks */
#define bmUART_SMOD          bmBIT7
#define bmUART_BRTSEL		 bmBIT6
#define bmUART_UX6           bmBIT5
#define bmUART_SM           (bmBIT2 | bmBIT1)
#define bmUART_SM0           bmBIT2 
#define bmUART_SM1	         bmBIT1
#define bmUART_SM2           bmBIT0

 /* S2CON Bit Masks */
#define bmUART2_FE            bmBIT7
#define bmUART2_REN           bmBIT4
#define bmUART2_TB8           bmBIT3
#define bmUART2_RB8           bmBIT2
#define bmUART2_TI            bmBIT1
#define bmUART2_RI            bmBIT0

 /* S2CON2 Bit Masks */
#define bmUART2_BRTSEL        bmBIT6
#define bmUART2_SM1           bmBIT1 
#define bmUART2_SM2	          bmBIT0

 /* SPCTL Bit Masks */
#define bmSPI_SSIG           bmBIT7
#define bmSPI_SPEN           bmBIT6
#define bmSPI_DORD           bmBIT5
#define bmSPI_MSTR           bmBIT4
#define bmSPI_CPOL           bmBIT3
#define bmSPI_CPHA           bmBIT2
#define bmSPI_SPR           (bmBIT1 | bmBIT0)

 /* SPSTAT Bit Masks */
#define bmSPI_SPIF           bmBIT7
#define bmSPI_WCOL           bmBIT6
#define bmSPI_RXOV	     	 bmBIT5
#define bmSPI_MODF	     	 bmBIT4


 /* ADCC0 Bit Masks */
#define bmADCEN              bmBIT7
#define bmADCST              bmBIT6
#define bmADCIF              bmBIT5
#define bmVREFO              bmBIT3
#define bmVREFS              bmBIT2
#define bmINREF_S            (bmBIT1 | bmBIT0)

 /* ADCC1 Bit Masks */
#define bmICHS              (bmBIT7 | bmBIT6)
#define bmXCHS              (bmBIT3 | bmBIT2 | bmBIT1 | bmBIT0)

 /* ADCC2 Bit Masks */
#define bmADCL               bmBIT7
#define bmALIGN              bmBIT6
#define bmADCTS             (bmBIT5 | bmBIT4 | bmBIT3)
#define bmADCS              (bmBIT2 | bmBIT1 | bmBIT0)

 /* LVDC Bit Masks */
#define bmLVDEN              bmBIT7
#define bmLVDS               bmBIT6
#define bmLVDIE              bmBIT5
#define bmLVDF               bmBIT3
#define bmLVDV              (bmBIT2 | bmBIT1 | bmBIT0)

 /* CRCC Bit Masks */
#define bmCRCBIT             bmBIT2
#define bmCRCRSV             bmBIT1
#define bmCRCRST             bmBIT0


 /* SCANCON Bit Masks */
#define bmSEL               bmBIT7
#define bmBUF               bmBIT6
#define bmCONT              bmBIT5
#define bmSCAN              bmBIT4
#define bmSMP               bmBIT3
#define bmNUM               (bmBIT2 | bmBIT1 | bmBIT0)

/*------------------------------------------------
Interrupt Vectors:
Interrupt Address = (Number * 8) + 3
------------------------------------------------*/
#define INT0_VECTOR         0   /* 0x03 EXTERNal Interrupt 0 */
#define TIMER0_VECTOR       1   /* 0x0B Timer 0 */
#define INT1_VECTOR	    	2   /* 0x13 EXTERNal Interrupt 1 */
#define TIMER1_VECTOR	    3   /* 0x1B Timer 1 */
#define UART1_VECTOR	    4   /* 0x23 Serial port 1 */
#define WDT_VECTOR	    	5   /* 0x2B WDT */
#define LVD_VECTOR	    	6   /* 0x33 LVD */
#define UART2_VECTOR	    7   /* 0x3B Serial port 2 */
#define SPI_VECTOR	    	8   /* 0x43 SPI */
#define IIC_VECTOR	    	9   /* 0x4B IIC */
#define T3_VECTOR	    	10  /* 0x53 Timer 3 */
#define T4_VECTOR	   		11  /* 0x5B Timer 4 */
#define PWM_VECTOR	    	12  /* 0x63 PWM */
#define T5_VECTOR	    	13  /* 0x6B Timer 5 */
#define ADC_VECTOR	    	15  /* 0x7B ADC */
#define INT2_7_VECTOR	   	16  /* 0x83 INT2~INT7 */
#define INT8_17_VECTOR	    17  /* 0x8B INT8~INT17 */
#define P2INT_VECTOR	    18  /* 0x93 P2INT */

//#define SET_BIT(REG,BIT)     ((REG) |= (BIT))
//#define CLEAR_BIT(REG,BIT)   ((REG) &= ~(BIT))
//#define READ_BIT(REG,BIT)    ((REG) & (BIT))
//#define CLEAR_REG(REG)        ((REG) = (0x0))
//#define WRITE_REG(REG,VAL)   ((REG) = (VAL))
//#define READ_REG(REG)         ((REG))
//#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#endif/* __HC89F0541_H__ */
