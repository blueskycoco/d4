/**********************************************************************//**
    Filename: hal_board.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_BOARD_H
#define HAL_BOARD_H


/*----------------------------------------------------------------
 *                  Function Prototypes
 *----------------------------------------------------------------
 */
void halBoardInit(void);
void hal430SetSystemClock(void);
void Msp430_ADC12_Init(void);
unsigned short Get_Power();
void hal_buzzer(int type);
void send_wave();
#endif /* HAL_BOARD_H */
