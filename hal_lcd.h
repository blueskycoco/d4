/*******************************************************************************
    Filename: hal_lcd.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_LCD_H
#define HAL_LCD_H
#define CPU_CLOCK 6000000
#if CPU_CLOCK == 6000000
            #define delay_us(us)    __delay_cycles(6*(us))
            #define delay_ms(ms)    __delay_cycles(6000*(ms))
#else
            #pragma error "CPU_CLOCK is defined implicitly!"
#endif

void Init_Lcd(void);
#endif /* HAL_LCD_H */
