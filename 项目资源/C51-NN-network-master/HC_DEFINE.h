/*--------------------------------------------------------------------------
HC_DEFINE.H
Ver:1.1

Copyright (c) 2009-2016 Shanghai Holychip Electronic Technology Co., Ltd.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __HC_DEFINE_H__
#define __HC_DEFINE_H__

#define TRUE    1
#define FALSE   0

#define OK       1
#define FAIL     0

typedef unsigned char   BYTE;
typedef unsigned char   uchar;
typedef unsigned int    uint;
typedef unsigned long   ulong;

typedef unsigned short  WORD;
typedef unsigned long   DWORD;

typedef bit            	BOOL;
typedef bit            	bool;

typedef	signed char		s8;
typedef	signed int		s16;
typedef	signed long		s32;

typedef	signed char	idata	si8;
typedef	signed int	idata	si16;
typedef	signed long	idata	si32;

typedef	signed char	xdata	sx8;
typedef	signed int	xdata	sx16;
typedef	signed long	xdata	sx32;

typedef	code signed char		sc8; /*!< Read Only */
typedef	code signed int			sc16;/*!< Read Only */
typedef	code signed long		sc32;/*!< Read Only */

typedef	unsigned char	 u8;
typedef	unsigned int   u16;
typedef	unsigned long	 u32;


typedef	unsigned char	 idata ui8;
typedef	unsigned int   idata ui16;
typedef	unsigned long	 idata ui32;

typedef	unsigned char	 xdata ux8;
typedef	unsigned int   xdata ux16;
typedef	unsigned long	 xdata ux32;

typedef	code unsigned char		uc8; /*!< Read Only */
typedef	code unsigned int			uc16;/*!< Read Only */
typedef	code unsigned long		uc32;/*!< Read Only */

typedef union {
    unsigned char byte;
    struct {        
        unsigned char high : 4;
        unsigned char low  : 4;
			}half;
}strChar;

typedef union {
    unsigned int word;
    struct {
        unsigned char high;
        unsigned char low;
    }byte;
}strInt;

typedef union {
    unsigned long dword;
    struct {
        unsigned int high;
        unsigned int low; 
    }word;
    struct {
        unsigned char m_high;
        unsigned char m_low;
        unsigned char l_high;
        unsigned char l_low; 
    }byte;
}strLong;

#define	MAKEWORD(v1,v2)	(((Word)(v1)<<8) + (Word)(v2))
#define	HIBYTE(v1)		  ((Byte)((v1)>>8))
#define	LOBYTE(v1)		  ((Byte)((v1)&0xff))

#define LongToBin(n) \
(                    \
((n >> 21) & 0x80) | \
((n >> 18) & 0x40) | \
((n >> 15) & 0x20) | \
((n >> 12) & 0x10) | \
((n >>  9) & 0x08) | \
((n >>  6) & 0x04) | \
((n >>  3) & 0x02) | \
((n      ) & 0x01)   \
)
#define Bin(n) LongToBin(0x##n##l)	//write binary charactor set,exsample : Bin(11111111) = 0xff

#endif/* __HC_DEFINE_H__ */
