/*******************************************************************************
    Filename: hal_lcd.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_EEPROM_H
#define HAL_EEPROM_H
typedef unsigned char uchar;
typedef unsigned int  uint;

uchar Read_NByte_currentaddress(uchar * readbuf,uchar n);

uchar Write_NByte(uchar * outbuf,uchar n,uchar dataaddress);
uchar Read_NByte_Randomaddress(uchar * readbuf,uchar n,uchar dataaddress);

#endif /* HAL_EEPROM_H */
