/**
 * @file  hal_lcd.c
 *
 * Copyright 2010 Texas Instruments, Inc.
 ***************************************************************************/

#include "msp430.h"
#include "hal_lcd.h"

#define sclk P2OUT
#define di P2OUT
#define a0 P1OUT
#define cs1 P2OUT
#define rst P1OUT

#define BIT_SCLK BIT7
#define BIT_DI BIT5
#define BIT_A0 BIT6
#define BIT_CS1 BIT0
#define BIT_RST BIT7
/*
const unsigned char niu[1024]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0xC0,0x40,0x60,0x20,0x30,0x18,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x08,0x38,0xF0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xE0,0xE0,0xD0,0x30,0x70,0x60,0x30,0x70,
	0x70,0x00,0x00,0x40,0xE0,0xF0,0xF0,0xE0,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF0,0xF8,0xF8,
	0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xE0,0x80,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x1E,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xC0,0x00,0x00,
	0x00,0xE0,0x80,0x00,0x00,0x1C,0xFC,0x70,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xE0,0x80,0x00,0x00,0x00,0x03,0x0F,0x3E,0x7C,0xF0,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0xFD,0xE9,0x01,0x00,0x00,0x00,0x00,0x38,0x00,
	0x00,0x30,0x30,0x00,0x00,0x00,0x06,0xFF,0x1D,0x0E,0x06,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xF8,0xFE,0xFF,0x1F,0x0F,0x03,0x03,0x01,0x01,0x01,0x00,
	0x00,0x00,0x00,0x01,0x01,0x01,0x03,0x03,0x07,0x07,0x07,0x0F,0x3F,0x7F,0xFF,0xFF,
	0xFC,0xF0,0xE0,0x81,0x01,0x01,0x01,0x00,0xF0,0xFC,0xFF,0xFF,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x0C,0xF8,0xF8,0x30,0x60,0x7F,0x43,0x47,0x5C,
	0xF8,0xFF,0x0F,0x1E,0x38,0x70,0xC7,0xFC,0x81,0x83,0x8E,0x5C,0x78,0x70,0xE0,0xC0,
	0xC0,0x8F,0xFF,0xFE,0xF8,0xE0,0xC0,0xC0,0xE0,0xF8,0xFF,0x00,0x00,0xC0,0xE0,0x60,
	0x70,0x70,0x30,0xF0,0xF8,0xFC,0x06,0x03,0x01,0x01,0x01,0x41,0x73,0x32,0x86,0xFC,
	0x7C,0x8E,0x02,0x73,0x41,0x41,0x01,0x01,0x02,0x06,0xFC,0x78,0x70,0x70,0x60,0x60,
	0xE0,0xE0,0xC0,0x00,0x00,0xFF,0xFF,0xFF,0xFC,0xE4,0xC2,0x02,0x81,0xC1,0xE0,0xE2,
	0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0xE1,0xF1,
	0xF3,0xFF,0x7F,0x3F,0x7F,0x7C,0xF8,0xF0,0xE1,0xC7,0x9F,0xBF,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0F,0x7C,0xFC,0x78,0x70,0xC1,0xCF,0xFE,0xE0,0x8E,0x10,0x1D,0x33,
	0x3F,0x1E,0x1C,0x80,0x00,0x00,0x00,0x01,0x01,0x1C,0x02,0x2F,0x33,0x3F,0x3F,0x1F,
	0x0F,0x07,0x87,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x04,0x3F,0x67,0xC7,0x8F,0xFE,0x1E,0x06,0x26,0xC6,0x82,0x03,0x01,0x00,
	0x00,0x01,0x83,0xC2,0x66,0x06,0x06,0xFE,0x9E,0x8F,0xC7,0x6F,0x3E,0x08,0x00,0x00,
	0x00,0x01,0x01,0x00,0x00,0x07,0x07,0x8F,0xFF,0xFF,0x07,0x0F,0x0F,0x67,0xEF,0xFF,
	0xF0,0xF8,0x3F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x03,0x07,0x3F,
	0x67,0x67,0x7F,0x7E,0x7F,0x5F,0x00,0x00,0x01,0x03,0xFF,0xFF,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x03,0x07,0x3F,0xFE,0xF8,0xE0,
	0xC0,0x80,0x00,0x01,0x12,0x70,0x70,0x70,0x10,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,
	0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x01,0x07,0x03,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x0F,0x3C,0xE0,0x80,0x00,0x07,0x1F,0x3F,0x3E,
	0x3F,0x3F,0x0F,0x03,0x80,0xE0,0x38,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF0,0xC0,0x80,0x81,0x01,
	0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,
	0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xF0,0xFC,0xFF,0xFF,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,
	0x07,0x07,0x03,0x02,0x06,0x06,0x06,0x06,0x06,0x06,0x07,0x03,0x03,0x07,0x07,0x07,
	0x07,0x07,0x07,0x00,0x00,0x01,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x0F,0x06,0x06,0x04,0x0C,0x0C,
	0x04,0x06,0x06,0x07,0x0D,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x06,0x04,0x04,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x03,0x03,0x01,0x01,0x00,
	0x00,0x00,0x00,0x04,0x06,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	};*/
const unsigned char FONT16X8[128][16]={
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 00h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0xe0,0xf2,0x18,0x18,0xf2,0xe0,0x00, /* A(..) 01h */
	0x00,0x0f,0x0f,0x01,0x01,0x0f,0x0f,0x00},
	{0x00,0xf8,0xfa,0x00,0x00,0xfa,0xf8,0x00, /* U(..) 02h */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x07,0x00}, 
	{0x00,0xc0,0xe8,0x20,0x20,0xe8,0xc0,0x00, /* e(..) 03h */
	0x00,0x07,0x0f,0x09,0x09,0x09,0x01,0x00},
	{0x00,0xf8,0xf8,0x89,0x8a,0x88,0x08,0x00, /* E(\)  04h */
	0x00,0x0f,0x0f,0x08,0x08,0x08,0x08,0x00},
	{0x00,0xc0,0xe0,0x28,0x24,0xe0,0xc0,0x00, /* e(/)  05h */
	0x00,0x07,0x0f,0x09,0x09,0x09,0x01,0x00},
	{0x00,0xc0,0xe8,0x24,0x24,0xe8,0xc0,0x00, /* e(^)  06h */
	0x00,0x07,0x0f,0x09,0x09,0x09,0x01,0x00},
	{0x00,0xe0,0xe8,0x24,0x28,0xe4,0xc0,0x00, /* n(~)  07h */
	0x00,0x0f,0x0f,0x00,0x00,0x0f,0x0f,0x00},
	{0x00,0xc0,0xe0,0x28,0x24,0xe0,0xc0,0x00, /* o(/)  08h */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0x00,0x20,0x24,0x28,0xe0,0xc0,0x00, /* a(\)  09h */
	0x00,0x06,0x0f,0x09,0x09,0x0f,0x0f,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 0ah */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 0bh */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 0ch */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 0dh */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 0eh */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 0fh */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 10h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 11h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 12h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 13h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 14h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 15h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 16h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 17h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 18h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 19h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 1ah */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 1bh */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 1ch */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x10,0xf8,0xf8,0x10,0x20,0x00, /* 'up' 1dh */
	0x00,0x00,0x00,0x0f,0x0f,0x00,0x00,0x00},
	{0x00,0x00,0x00,0xf8,0xf8,0x00,0x00,0x00, /* 'down' 1eh */
	0x00,0x02,0x04,0x0f,0x0f,0x04,0x02,0x00},
	{0x00,0xf8,0xfc,0x04,0x04,0xfc,0xf4,0x04, /* ???? 1fh */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*   20h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x70,0xf8,0xf8,0x70,0x00,0x00,0x00, /* ! 21h */
	0x00,0x00,0x0d,0x0d,0x00,0x00,0x00,0x00},
	{0x1c,0x3c,0x00,0x00,0x00,0x3c,0x1c,0x00, /* " 22h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x20,0xf8,0xf8,0x20,0xf8,0xf8,0x20,0x00, /* # 23h */
	0x02,0x0f,0x0f,0x02,0x0f,0x0f,0x02,0x00},
	{0x70,0xf8,0x88,0x8e,0x8e,0x98,0x30,0x00, /* $ 24h */
	0x06,0x0c,0x08,0x38,0x38,0x0f,0x07,0x00},
	{0x60,0x60,0x00,0x00,0x80,0xc0,0x60,0x00, /* % 25h */
	0x08,0x0c,0x06,0x03,0x01,0x0c,0x0c,0x00},
	{0x00,0xb0,0xf8,0xc8,0x78,0xb0,0x80,0x00, /* & 26h */
	0x07,0x0f,0x08,0x09,0x07,0x0f,0x08,0x00},
	{0x00,0x00,0x00,0x0e,0x0e,0x00,0x00,0x00, /* ' 27h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0xe0,0xf0,0x18,0x08,0x00,0x00,0x00, /* ( 28h */
	0x00,0x03,0x07,0x0c,0x08,0x00,0x00,0x00},
	{0x00,0x00,0x08,0x18,0xf0,0xe0,0x00,0x00, /* ) 29h */
	0x00,0x00,0x08,0x0c,0x07,0x03,0x00,0x00},
	{0x80,0xa0,0xe0,0xc0,0xe0,0xa0,0x80,0x00, /* * 2ah */
	0x00,0x02,0x03,0x01,0x03,0x02,0x00,0x00},
	{0x80,0x80,0xf0,0xf0,0x80,0x80,0x00,0x00, /* + 2bh */
	0x01,0x01,0x0f,0x0f,0x01,0x01,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* , 2ch */
	0x00,0x10,0x1e,0x0e,0x00,0x00,0x00,0x00},
	{0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00, /* - 2dh */
	0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* . 2eh */
	0x00,0x00,0x0c,0x0c,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x80,0xc0,0x60,0x30,0x18,0x00, /* / 2fh */
	0x06,0x03,0x01,0x00,0x00,0x00,0x00,0x00},
	{0x00,0xf0,0xf8,0x08,0x68,0xf8,0xf0,0x00, /* 0 30h */
	0x00,0x07,0x0f,0x0b,0x08,0x0f,0x07,0x00},
	{0x00,0x20,0x20,0x30,0xf8,0xf8,0x00,0x00, /* 1 31h */
	0x00,0x00,0x00,0x00,0x0f,0x0f,0x00,0x00},
	{0x00,0x30,0x38,0x08,0x88,0xf8,0x70,0x00, /* 2 32h */
	0x00,0x0c,0x0e,0x0b,0x09,0x08,0x08,0x00},
	{0x00,0x30,0x38,0x88,0x88,0xf8,0x70,0x00, /* 3 33h */
	0x00,0x06,0x0e,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0x00,0xf8,0xf8,0x00,0xe0,0xe0,0x00, /* 4 34h */
	0x00,0x03,0x03,0x02,0x02,0x0f,0x0f,0x02},
	{0x00,0x78,0x78,0x48,0x48,0xc8,0x88,0x00, /* 5 35h */
	0x00,0x08,0x08,0x08,0x0c,0x07,0x03,0x00},
	{0x00,0xc0,0xe0,0x78,0x58,0xc8,0x80,0x00, /* 6 36h */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0x08,0x08,0x88,0xe8,0x78,0x18,0x00, /* 7 37h */
	0x00,0x00,0x0e,0x0f,0x01,0x00,0x00,0x00},
	{0x00,0x70,0xf8,0xc8,0x88,0xf8,0x70,0x00, /* 8 38h */
	0x00,0x07,0x0f,0x08,0x09,0x0f,0x07,0x00},
	{0x00,0xf0,0xf8,0x08,0x08,0xf8,0xf0,0x00, /* 9 39h */
	0x00,0x00,0x09,0x0d,0x0f,0x03,0x01,0x00},
	{0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00, /* : 3ah */
	0x00,0x00,0x06,0x06,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00, /* ; 3bh */
	0x00,0x08,0x0e,0x06,0x00,0x00,0x00,0x00},
	{0x00,0x80,0xc0,0x60,0x30,0x18,0x08,0x00, /* < 3ch */
	0x00,0x00,0x01,0x03,0x06,0x0c,0x08,0x00},
	{0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00, /* = 3dh */
	0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00},
	{0x00,0x08,0x18,0x30,0x60,0xc0,0x80,0x00, /* > 3eh */
	0x00,0x08,0x0c,0x06,0x03,0x01,0x00,0x00},
	{0x30,0x38,0x08,0x88,0xc8,0x78,0x30,0x00, /* ? 3fh */
	0x00,0x00,0x00,0x0d,0x0d,0x00,0x00,0x00},
	{0xf0,0xf8,0x08,0xc8,0xc8,0xf8,0xf0,0x00, /* @ 40h */
	0x07,0x0f,0x08,0x0b,0x0b,0x0b,0x01,0x00},
	{0x00,0xe0,0xf0,0x18,0x18,0xf0,0xe0,0x00, /* A 41h */
	0x00,0x0f,0x0f,0x01,0x01,0x0f,0x0f,0x00},
	{0x00,0xf8,0xf8,0x88,0x88,0xf8,0x70,0x00, /* B 42h */
	0x00,0x0f,0x0f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0xf0,0xf8,0x08,0x08,0x38,0x30,0x00, /* C 43h */
	0x00,0x07,0x0f,0x08,0x08,0x0e,0x06,0x00},
	{0x00,0xf8,0xf8,0x08,0x18,0xf0,0xe0,0x00, /* D 44h */
	0x00,0x0f,0x0f,0x08,0x0c,0x07,0x03,0x00},
	{0x00,0xf8,0xf8,0x88,0x88,0x88,0x08,0x00, /* E 45h */
	0x00,0x0f,0x0f,0x08,0x08,0x08,0x08,0x00},
	{0x00,0xf8,0xf8,0x88,0x88,0x88,0x08,0x00, /* F 46h */
	0x00,0x0f,0x0f,0x00,0x00,0x00,0x00,0x00},
	{0x00,0xf0,0xf8,0x08,0x08,0x38,0x30,0x00, /* G 47h */
	0x00,0x07,0x0f,0x08,0x09,0x0f,0x0f,0x00},
	{0x00,0xf8,0xf8,0x80,0x80,0xf8,0xf8,0x00, /* H 48h */
	0x00,0x0f,0x0f,0x00,0x00,0x0f,0x0f,0x00},
	{0x00,0x00,0x08,0xf8,0xf8,0x08,0x00,0x00, /* I 49h */
	0x00,0x00,0x08,0x0f,0x0f,0x08,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0xf8,0xf8,0x00, /* J 4ah */
	0x00,0x06,0x0e,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0xf8,0xf8,0x80,0xe0,0x78,0x18,0x00, /* K 4bh */
	0x00,0x0f,0x0f,0x00,0x03,0x0f,0x0c,0x00},
	{0x00,0xf8,0xf8,0x00,0x00,0x00,0x00,0x00, /* L 4ch */
	0x00,0x0f,0x0f,0x08,0x08,0x08,0x08,0x00},
	{0x00,0xf8,0xf8,0x20,0xc0,0x20,0xf8,0xf8, /* M 4dh */
	0x00,0x0f,0x0f,0x00,0x01,0x00,0x0f,0x0f},
	{0x00,0xf8,0xf8,0x60,0xc0,0x80,0xf8,0xf8, /* N 4eh */
	0x00,0x0f,0x0f,0x00,0x00,0x01,0x0f,0x0f},
	{0x00,0xf0,0xf8,0x08,0x08,0xf8,0xf0,0x00, /* O 4fh */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0xf8,0xf8,0x88,0x88,0xf8,0x70,0x00, /* P 50h */
	0x00,0x0f,0x0f,0x00,0x00,0x00,0x00,0x00},
	{0x00,0xf0,0xf8,0x08,0x08,0xf8,0xf0,0x00, /* Q 51h */
	0x00,0x07,0x0f,0x08,0x18,0x3f,0x27,0x00},
	{0x00,0xf8,0xf8,0x88,0x88,0xf8,0x70,0x00, /* R 52h */
	0x00,0x0f,0x0f,0x00,0x01,0x0f,0x0e,0x00},
	{0x00,0x30,0x78,0xc8,0x88,0x18,0x10,0x00, /* S 53h */
	0x00,0x04,0x0c,0x08,0x09,0x0f,0x06,0x00},
	{0x00,0x08,0x08,0xf8,0xf8,0x08,0x08,0x00, /* T 54h */
	0x00,0x00,0x00,0x0f,0x0f,0x00,0x00,0x00},
	{0x00,0xf8,0xf8,0x00,0x00,0xf8,0xf8,0x00, /* U 55h */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0xf8,0xf8,0x00,0x00,0xf8,0xf8,0x00, /* V 56h */
	0x00,0x03,0x07,0x0c,0x0c,0x07,0x03,0x00},
	{0x00,0xf8,0xf8,0x00,0xc0,0x00,0xf8,0xf8, /* W 57h */
	0x00,0x01,0x0f,0x0e,0x01,0x0e,0x0f,0x01},
	{0x00,0x18,0x38,0xe0,0xc0,0x38,0x18,0x00, /* X 58h */
	0x00,0x0e,0x0f,0x00,0x01,0x0f,0x0e,0x00},
	{0x00,0x78,0xf8,0x80,0x80,0xf8,0x78,0x00, /* Y 59h */
	0x00,0x00,0x00,0x0f,0x0f,0x00,0x00,0x00},
	{0x00,0x08,0x08,0x88,0xc8,0x78,0x38,0x00, /* Z 5ah */
	0x00,0x0e,0x0f,0x09,0x08,0x08,0x08,0x00},
	{0x00,0xf8,0xf8,0x08,0x08,0x00,0x00,0x00, /* [ 5bh */
	0x00,0x0f,0x0f,0x08,0x08,0x00,0x00,0x00},
	{0x38,0x70,0xe0,0xc0,0x80,0x00,0x00,0x00, /* \ 5ch */
	0x00,0x00,0x00,0x01,0x03,0x07,0x0e,0x00},
	{0x00,0x08,0x08,0xf8,0xf8,0x00,0x00,0x00, /* ] 5dh */
	0x00,0x08,0x08,0x0f,0x0f,0x00,0x00,0x00},
	{0x10,0x18,0x0c,0x06,0x0c,0x18,0x10,0x00, /* ^ 5eh */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* _ 5fh */
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00},
	{0x00,0x00,0x06,0x0e,0x08,0x00,0x00,0x00, /* ` 60h */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x20,0x20,0x20,0xe0,0xc0,0x00, /* a 61h */
	0x00,0x06,0x0f,0x09,0x09,0x0f,0x0f,0x00},
	{0x00,0xf8,0xf8,0x20,0x20,0xe0,0xc0,0x00, /* b 62h */
	0x00,0x0f,0x0f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0xc0,0xe0,0x20,0x20,0x60,0x40,0x00, /* c 63h */
	0x00,0x07,0x0f,0x08,0x08,0x0c,0x04,0x00},
	{0x00,0xc0,0xe0,0x20,0x20,0xf8,0xf8,0x00, /* d 64h */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x0f,0x00},
	{0x00,0xc0,0xe0,0x20,0x20,0xe0,0xc0,0x00, /* e 65h */
	0x00,0x07,0x0f,0x09,0x09,0x09,0x01,0x00},
	{0x00,0x40,0xf0,0xf8,0x48,0x48,0x48,0x00, /* f 66h */
	0x00,0x00,0x0f,0x0f,0x00,0x00,0x00,0x00},
	{0x00,0xc0,0xe0,0x20,0x20,0xe0,0xe0,0x00, /* g 67h */
	0x00,0x47,0x4f,0x48,0x48,0x7f,0x3f,0x00},
	{0x00,0xf8,0xf8,0x20,0x20,0xe0,0xc0,0x00, /* h 68h */
	0x00,0x0f,0x0f,0x00,0x00,0x0f,0x0f,0x00},
	{0x00,0x20,0x20,0xec,0xec,0x00,0x00,0x00, /* i 69h */
	0x00,0x08,0x08,0x0f,0x0f,0x08,0x08,0x00},
	{0x00,0x00,0x20,0x20,0xec,0xec,0x00,0x00, /* j 6ah */
	0x00,0x40,0x40,0x40,0x7f,0x3f,0x00,0x00},
	{0x00,0xf8,0xf8,0x00,0x80,0xe0,0x60,0x00, /* k 6bh */
	0x00,0x0f,0x0f,0x01,0x03,0x0e,0x0c,0x00},
	{0x00,0x08,0x08,0xf8,0xf8,0x00,0x00,0x00, /* l 6ch */
	0x00,0x08,0x08,0x0f,0x0f,0x08,0x08,0x00},
	{0x00,0xe0,0xe0,0x20,0xe0,0x20,0xe0,0xc0, /* m 6dh */
	0x00,0x0f,0x0f,0x00,0x07,0x00,0x0f,0x0f},
	{0x00,0xe0,0xe0,0x20,0x20,0xe0,0xc0,0x00, /* n 6eh */
	0x00,0x0f,0x0f,0x00,0x00,0x0f,0x0f,0x00},
	{0x00,0xc0,0xe0,0x20,0x20,0xe0,0xc0,0x00, /* o 6fh */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0xe0,0xe0,0x20,0x20,0xe0,0xc0,0x00, /* p 70h */
	0x00,0x7f,0x7f,0x08,0x08,0x0f,0x07,0x00},
	{0x00,0xc0,0xe0,0x20,0x20,0xe0,0xe0,0x00, /* q 71h */
	0x00,0x07,0x0f,0x08,0x08,0x7f,0x7f,0x00},
	{0x00,0xe0,0xe0,0x80,0x40,0x60,0x60,0x00, /* r 72h */
	0x00,0x0f,0x0f,0x00,0x00,0x00,0x00,0x00},
	{0x00,0xc0,0xe0,0x20,0x20,0x20,0x20,0x00, /* s 73h */
	0x00,0x08,0x09,0x09,0x09,0x0f,0x06,0x00},
	{0x00,0x20,0xf8,0xf8,0x20,0x20,0x20,0x00, /* t 74h */
	0x00,0x00,0x07,0x0f,0x08,0x08,0x08,0x00},
	{0x00,0xe0,0xe0,0x00,0x00,0xe0,0xe0,0x00, /* u 75h */
	0x00,0x07,0x0f,0x08,0x08,0x0f,0x0f,0x00},
	{0x00,0xe0,0xe0,0x00,0x00,0xe0,0xe0,0x00, /* v 76h */
	0x00,0x03,0x07,0x0c,0x0c,0x07,0x03,0x00},
	{0x00,0xe0,0xe0,0x00,0xc0,0x00,0xe0,0xe0, /* w 77h */
	0x00,0x03,0x0f,0x0c,0x03,0x0c,0x0f,0x03},
	{0x00,0x60,0xe0,0x80,0x80,0xe0,0x60,0x00, /* x 78h */
	0x00,0x0c,0x0e,0x03,0x03,0x0e,0x0c,0x00},
	{0x00,0xe0,0xe0,0x00,0x00,0xe0,0xe0,0x00, /* y 79h */
	0x40,0x47,0x4f,0x68,0x38,0x1f,0x07,0x00},
	{0x00,0x20,0x20,0x20,0xa0,0xe0,0x60,0x00, /* z 7ah */
	0x00,0x0c,0x0e,0x0b,0x09,0x08,0x08,0x00},
	{0x80,0x80,0xf0,0x78,0x08,0x08,0x00,0x00, /* { 7bh */
	0x00,0x00,0x07,0x0f,0x08,0x08,0x00,0x00},
	{0x00,0x00,0x78,0x78,0x00,0x00,0x00,0x00, /* | 7ch */
	0x00,0x00,0x0f,0x0f,0x00,0x00,0x00,0x00},
	{0x08,0x08,0x78,0xf0,0x80,0x80,0x00,0x00, /* } 7dh */
	0x08,0x08,0x0f,0x07,0x00,0x00,0x00,0x00},
	{0x10,0x18,0x08,0x18,0x10,0x18,0x08,0x00, /* ~ 7eh */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, /*  7fh */
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}
};

void data_send(unsigned char dat)
{
	unsigned char s,temp;
	int i;
	sclk&=~BIT_SCLK;
	
	s=dat;
	for(i=8;i>0;i--)
	{
		sclk&=~BIT_SCLK;
		//delay_us(1);		
		delay_us(1);		
		temp=s & 0x80;
		if(temp)
		{di|=BIT_DI;}
		else {di&=~BIT_DI;}
		sclk|=BIT_SCLK;
		s=s<<1;
	}
}

void w_coms(unsigned char x)
{
	a0&=~BIT_A0;
	cs1&=~BIT_CS1;
	data_send(x);
	cs1|=BIT_CS1;
}


void wdatas(unsigned char dat)
{
	a0|=BIT_A0;
	cs1&=~BIT_CS1;
	data_send(dat);
	cs1|=BIT_CS1;
}
/*
void display_map(unsigned char *p)
{
	unsigned char seg;
	unsigned char page;
	for(page=0xb0;page<0xb9;page++) 
	{
		w_coms(page);
		w_coms(0x10);
		w_coms(0x00);
		for(seg=0;seg<128;seg++)
		{ wdatas(*p++); }
	}
}
*/
void Setxy(unsigned char x,unsigned char y)
{ 
	unsigned char tmp=0;
	y=y&0x0F;    
	y=y|0xb0;
	tmp=x;
	tmp>>=4;     
	tmp|=0x10;
	x&=0x0F;
	w_coms(y); 
	w_coms(tmp);
	w_coms(x);  
}

void display_HZ(unsigned char x,unsigned char y,unsigned char *p) 
{
	unsigned char i;
	w_coms(0xa4);
	Setxy(x,y);      
	for(i=0;i<8;i++)
	{
		wdatas(*p++);
	}                           
	y+=1;
	Setxy(x,y);     
	for(i=8;i<16;i++)
	{
		wdatas(*p++); 
	}   
}

void Init_Lcd(void)
{
	unsigned char i,x=0,y=0;
	rst&=~BIT_RST;	
	delay_us(1);	
	delay_us(1);	
	rst|=BIT_RST;
	w_coms(0xaf); //ON DISPLAY
	w_coms(0x40); //STAR DISPLAY
	w_coms(0xa0); //ADC NORMAL
	w_coms(0xa6); //
	w_coms(0xa4); //CLEAR
	w_coms(0xa2); //1/9BIAS
	w_coms(0xc8); //COMMON OUTPUT DIRECTION
	w_coms(0x2f); //POWER CONTROL
	w_coms(0x24); //RESISTER RATIO
	w_coms(0x81); //VOLUM MODE SET
	w_coms(0x24); //RESISTER RATIO	
	//display_map((unsigned char *)niu);
	Delay(10);
	for(i=0x21;i<0x5f;i++)
	{
		display_HZ(x,y,(unsigned char *)(FONT16X8[i]));
		x=x+8;
		if(x==128)
		{
		  x=0;
		  y=y+2;
		}
			
	}
}

