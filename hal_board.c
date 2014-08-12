/**
 * @file  hal_board.c
 *
 * Copyright 2010 Texas Instruments, Inc.
 ******************************************************************************/
#include <stdio.h>
#include "msp430.h"
#include "hal_lcd.h"
#include "hal_board.h"

extern void Delay(int ms);
#define U1_5_PORT P4OUT		//20hz wave h
#define U1_5_PIN BIT5
#define U1_1_PORT P2OUT		//out wave l
#define U1_1_PIN BIT4
#define U1_9_PORT P1IN		//back wave h
#define U1_9_PIN BIT0
#define U6_1_PORT P2OUT		//ctl 221d work
#define U6_1_PIN BIT1
#define U6_4_PORT P1IN		// /Q intr
#define U6_4_PIN BIT5
#define VQ1_2_PORT P6OUT  	//vq1 ctl
#define VQ1_2_PIN BIT2
#define VQ2_2_PORT P3OUT	//vq2 ctl
#define VQ2_2_PIN BIT6
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
  P1DIR  = 0xde;
  P1SEL  = 0;
  P1IES &=0xfe;//p1.0 is low to high U1.9
  P1IES |=0x20;//p1.5 is high to low U6.4
  P1IE |=0x21;
  
  P2OUT  = 0x10;
  P2DIR  = 0xFF;
  P2SEL  = 0;
  P3OUT  = 0;
  P3DIR  = 0xFF;
  P3SEL  = 0;
  P4OUT  = 0x20;//p4.5 h
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
  unsigned char i = 0;
  WDTCTL = WDTPW + WDTHOLD+WDTNMI+WDTNMIES;
  BCSCTL1 &= ~XT2OFF;
  do
  {   
	IFG1 &= ~OFIFG;       
	for(i=0xff;i>0;i--);
  }
  while((IFG1&OFIFG));    // 判断XT2是否已经稳定
  BCSCTL2 |= SELM_2+SELS+DIVS_0; // 切换XT2为MCLK,SMCLK的时钟源 ,SMCLK2分频
  _EINT();
  IE1 |= NMIIE;
  return ;
}

void hal_buzzer(int type)
{
  if(type==0)
  {
	// power on
	P5OUT |=BIT5;
	Delay(20);
	P5OUT &=~BIT5;

  }
  else if(type==1)
  {
	//measure
	P5OUT |=BIT5;
	Delay(10);
	P5OUT &=~BIT5;

  }else if(type==2)
  {
	//button
	P5OUT |=BIT5;
	Delay(30);
	P5OUT &=~BIT5;

  }else
  {//others
	P5OUT |=BIT5;
	Delay(5);
	P5OUT &=~BIT5;

  }
}
void send_wave()
{
	int i=0;
	for(i=0;i<24;i++)
	{
	U1_5_PORT&=~U1_5_PIN;
	delay_us(37);
	U1_5_PORT|=U1_5_PIN;
	delay_us(1);
	}
	U1_5_PORT&=~U1_5_PIN;
	delay_us(18);
	U1_5_PORT|=U1_5_PIN;
}
void Msp430_ADC12_Init(void)
{
  P6SEL |= BIT0;   // 使能AD通道输入P6.0
  P6DIR |= BIT0;   
  ADC12CTL0 = ADC12ON + MSC + SHT0_8 + REFON + REF2_5V;          
  ADC12CTL1 = SHP + CONSEQ_0; // 用采样定时,单次+单通道
  ADC12MCTL0 = INCH_0 + SREF_1 + EOS;  // ref+=AVcc, 通道A0
  ADC12IE = 0x01;    // 使能 ADC12IFG.0
  ADC12CTL0 |= ENC;  // 使能 ADC12
  ADC12CTL0 |= ADC12SC;   // 开始转换
  //   _EINT();  
}
unsigned short PowerVoltage = 0;
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR(void)
{  
      PowerVoltage = (unsigned short)((ADC12MEM0 * 2.5) / 40.95 ); // Get Power Voltage
}
unsigned short Get_Power()
{
    	ADC12CTL0 |= ADC12SC;   // 开始转换
  	printf("Current Power is %x\r\n",PowerVoltage);
	return PowerVoltage;
}
#pragma vector=PORT1_VECTOR
__interrupt void PORT1ISR(void){
	if( ( P1IFG & BIT0 ) != 0 )
	{
		printf("back wave intr \r\n");
		P1IFG&=~BIT0;
	}
	if( ( P1IFG & BIT5 ) != 0 )
	{
		printf("U6 pin4 ,/Q intr \r\n");
		P1IFG&=~BIT5;
	}
}
