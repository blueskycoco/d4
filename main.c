/* Standard includes. */
#include <stdio.h>

/* Hardware includes. */
#include "msp430.h"
#include "hal_buttons.h"
#include "hal_board.h"
#include "hal_serial.h"
#include "hal_lcd.h"

volatile unsigned char flag=0;

void main( void )
{
	unsigned int ucState=0xffff;
	int i=0;
	halBoardInit();
	hal430SetSystemClock();
	halButtonsInit();
	Init_Uart(115200);
	Init_Lcd();
	printf("main\r\n");
	 while(1)
	{
		if(flag==1)
		{
			WDTCTL = WDTPW + WDTNMI + WDTTMSEL + WDTSSEL + WDTCNTCL;             // Start watchdog timer
			IE1 |= WDTIE;                         // Enable WDT interrupt
			printf("we are in active state\r\n");
			//����д�Լ��ĳ��򣬰ѳ�������һ�����޵�ѭ�����������֮��Ϳ����Զ��������ػ���
			for(i=0;i<300000;i++){
			ucState = halButtonsPressed();
			
			if(ucState!=0xffff)
			{
				printf("%x is pressed\r\n",ucState);
				switch(ucState)
					{
					case BUTTON_MATL:
						printf("matl is pressed\r\n");
						break;
					case BUTTON_HARD:
						printf("hard is pressed\r\n");
						break;
					case BUTTON_DIREC:
						printf("direc is pressed\r\n");
						break;
					case BUTTON_TIMES:
						printf("times is pressed\r\n");
						break;						
					case BUTTON_SAVE:
						printf("save is pressed\r\n");
						break;
					case BUTTON_UP:
						printf("up is pressed\r\n");
						break;
					case BUTTON_DEL:
						printf("del is pressed\r\n");
						break;
					case BUTTON_AVE:
						printf("ave is pressed\r\n");
						break;
					case BUTTON_LEFT:
						printf("left is pressed\r\n");
						break;
					case BUTTON_MENU:
						printf("menu is pressed\r\n");
						break;
					case BUTTON_RIGHT:
						printf("right is pressed\r\n");
						break;
					case BUTTON_BACKLIGHT:
						printf("backlight is pressed\r\n");
						break;
					case BUTTON_ESC:
						printf("esc is pressed\r\n");
						break;
					case BUTTON_DOWN:
						printf("down is pressed\r\n");
						break;
					case BUTTON_ENTER:
						printf("enter is pressed\r\n");
						break;
					default:
						break;
					}
			}			
			delay_ms(1);
			LPM3;
			}
			//���趨ʱ���ϱ����LPM3Ҫ���������Ǹ���ѭ����ѭ�����У���������ʵ�����Ʊ�Яʽ�Ǳ�5�����Զ��ػ���Ч���������ʹ�ö�ʱҲ���Բ�ҪLPM3��仰��
			WDTCTL = WDTPW + WDTHOLD + WDTNMI;             // Stop watchdog timer
			flag=0;
		}
		else
		{
			//����ܱ��豸�ڹػ�ʱ����Ҫ��λ�Ļ��ǹرյ������ﴦ��
			printf("we are in power off state\r\n");
		}
		LPM4;
	}
}
#pragma vector=WDT_VECTOR                 //���Ź���ʱ�жϷ���
__interrupt void wdt_timer(void)  
{
	printf("wdt timer\r\n");
   	LPM3_EXIT;             // Cleat LPM3 bits from 0(SR)
}

#pragma vector=NMI_VECTOR
__interrupt void prvNMIInterrupt( void )
{

	printf("NMI intr\r\n");
	if((IFG1&NMIIFG)==NMIIFG)
	{
		if(flag==1)
		{
			flag=0;
			printf("going to sleep\r\n");
		}
		else
		{
			flag=1;
			printf("wakeup from sleep\r\n");
		}
		//RST/NMI���������ж�
		IFG1 &= ~NMIIFG;
		IE1 |= NMIIE;
		LPM4_EXIT;
	}
}
