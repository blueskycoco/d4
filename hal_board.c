/**
 * @file  hal_board.c
 *
 * Copyright 2010 Texas Instruments, Inc.
 ******************************************************************************/
#include "msp430.h"
#include "hal_board.h"


/**********************************************************************//**
 * @brief  Initializes all GPIO configurations.
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void halBoardInit(void)
{
	//Tie unused ports
	P1OUT  = 0;
	P1DIR  = 0xFF;
	P1SEL  = 0;
	P2OUT  = 0;
	P2DIR  = 0xFF;
	P2SEL  = 0;
	P3OUT  = 0;
	P3DIR  = 0xFF;
	P3SEL  = 0;
	P4OUT  = 0;
	P4DIR  = 0xf0;
	P4SEL  = 0x00;
	P5OUT  = 0;
	P5DIR  = 0xFF;                        
	P5SEL  = 0;
	P6OUT = 0;
	P6DIR = 0xFF;
	P6SEL = 0;

	P6SEL &= ~0x10;
	P6DIR |= 0x10;
	P6OUT &= ~0x10;
	P6OUT |= 0x10;

	P3SEL |= BIT4 + BIT5;        
	IE1|=NMIIE;
}

/**********************************************************************//**
 * @brief  Set function for MCLK frequency.
 *
 *
 * @return none
 *************************************************************************/
void hal430SetSystemClock()
{
	unsigned char i = 0, j = 0;
	WDTCTL = WDTPW + WDTHOLD+WDTNMI+WDTNMIES;
	BCSCTL1 &= ~XT2OFF;
	do
	{   
		j++;
		if(j == 11) // XT2 Switching Overtime  
		{
			break;
		}
		IFG1 &= ~OFIFG;       
		for(i=0xff;i>0;i--);
	}
	while((IFG1&OFIFG));    // 判断XT2是否已经稳定
	BCSCTL2 |= SELM_2+SELS+DIVS_0; // 切换XT2为MCLK,SMCLK的时钟源 ,SMCLK2分频
	_EINT();
	IE1 |= NMIIE;
	return ;
}
