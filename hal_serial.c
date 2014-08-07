/* Standard includes. */
#include "msp430.h"
#include <stdlib.h>

/* Demo application includes. */
void Init_Uart( unsigned long ulWantedBaud)
{
	unsigned long ulBaudRateCount;

	/* Generate the baud rate constants for the wanted baud rate. */
	ulBaudRateCount = 6000000 / ulWantedBaud;

	U0ME |= UTXE0 + URXE0; 
	UCTL0 |= CHAR;        // 8-bit character
	UTCTL0 |= (SSEL1+SSEL0);	// UCLK = MCLK
	UBR00 = ( unsigned char) ( ulBaudRateCount & ( unsigned long ) 0xff );
	ulBaudRateCount >>= 8UL;
	UBR10 = ( unsigned char) ( ulBaudRateCount & ( unsigned long ) 0xff );

	UMCTL0 = 0x00; 		// 6MHz 115200 modulation
	UCTL0 &= ~SWRST;        // Initialize USCI state machine
	U0IE |= URXIE0;           // 允许接收中断

	return ;
}

#pragma vector=UART0RX_VECTOR
__interrupt void prvUSCI_A1_ISR( void )
{
	signed char cChar;

	if( ( U0IFG & URXIFG0 ) != 0 )
	{
		/* Get the character from the UART and post it on the queue of Rxed
		   characters. */
		cChar = RXBUF0;
		TXBUF0 = cChar;
	}	
	LPM3_EXIT;

}
void putchar(unsigned b) {
	while (!( U0IFG & UTXIFG0 ));			// USCI_A0 TX buffer ready?
	TXBUF0 = b;
}

