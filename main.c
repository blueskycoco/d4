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
			//这里写自己的程序，把程序做在一个有限的循环里，这样做完之后就可以自动结束并关机。
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
			//如需定时，上边这个LPM3要被包括在那个有循环的循环体中，这样才能实现类似便携式仪表5分钟自动关机的效果。如果不使用定时也可以不要LPM3这句话。
			WDTCTL = WDTPW + WDTHOLD + WDTNMI;             // Stop watchdog timer
			flag=0;
		}
		else
		{
			//如果周边设备在关机时有需要复位的或是关闭的在这里处理
			printf("we are in power off state\r\n");
		}
		LPM4;
	}
}
#pragma vector=WDT_VECTOR                 //看门狗定时中断服务
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
		//RST/NMI不可屏蔽中断
		IFG1 &= ~NMIIFG;
		IE1 |= NMIIE;
		LPM4_EXIT;
	}
}
