#include "msp430.h"
#include "hal_at24c02.h"
#define SCL_H {P3OUT |= BIT6;}
#define SCL_L {P3OUT &= ~BIT6;}
#define SDA_H {P3OUT |= BIT7;}
#define SDA_L {P3OUT &= ~BIT7;}

#define SDA_in  {P3DIR &= ~BIT7;}   //SDA改成输入模式
#define SDA_out {P3DIR |= BIT7;}    //SDA变回输出模式
#define SDA_val P3IN&BIT7        //SDA的位值

#define TRUE    1
#define FALSE   0
#define deviceaddress 0xa0  //AT24C02的设备地址

/*******************************************
 * 函数名称：delay
 * 功    能：延时约15us的时间
 * 参    数：无
 * 返回值  ：无
 * ********************************************/
void delay(void)
{
	uchar i;

	for(i = 0;i < 15;i++)
		__delay_cycles(6);
}    
/*******************************************
 * 函数名称：start
 * 功    能：完成IIC的起始条件操作
 * 参    数：无
 * 返回值  ：无
 * ********************************************/
void start(void)
{
	SCL_H;
	SDA_H;
	delay();
	SDA_L;
	delay();
	SCL_L;
	delay();
}
/*******************************************
 * 函数名称：stop
 * 功    能：完成IIC的终止条件操作
 * 参    数：无
 * 返回值  ：无
 * ********************************************/
void stop(void)
{
	SDA_L;
	delay();
	SCL_H;
	delay();
	SDA_H;
	delay();       
}
/*******************************************
 * 函数名称：mack
 * 功    能：完成IIC的主机应答操作
 * 参    数：无
 * 返回值  ：无
 * ********************************************/
void mack(void)
{
	SDA_L;
	__delay_cycles(6); __delay_cycles(6);
	SCL_H;
	delay();
	SCL_L;
	__delay_cycles(6);__delay_cycles(6);
	SDA_H;     
	delay();
}
/*******************************************
 * 函数名称：mnack
 * 功    能：完成IIC的主机无应答操作
 * 参    数：无
 * 返回值  ：无
 * ********************************************/
void mnack(void)
{
	SDA_H;
	__delay_cycles(6);__delay_cycles(6);
	SCL_H;
	delay();
	SCL_L;
	__delay_cycles(6);__delay_cycles(6);
	SDA_L;   
	delay();       
}

/**********检查应答信号函数******************/
/*如果返回值为1则证明有应答信号，反之没有*/
/*******************************************
 * 函数名称：check
 * 功    能：检查从机的应答操作
 * 参    数：无
 * 返回值  ：从机是否有应答：1--有，0--无
 * ********************************************/
uchar check(void)
{
	uchar slaveack;

	SDA_H;
	__delay_cycles(6);__delay_cycles(6);
	SCL_H;
	__delay_cycles(6);__delay_cycles(6);
	SDA_in;
	__delay_cycles(6);__delay_cycles(6);
	slaveack = SDA_val;   //读入SDA数值
	SCL_L;
	delay();
	SDA_out;
	if(slaveack)    return FALSE;
	else            return TRUE;
}
/*******************************************
 * 函数名称：write1
 * 功    能：向IIC总线发送一个1
 * 参    数：无
 * 返回值  ：无
 * ********************************************/
void write1(void)
{
	SDA_H;
	delay();
	SCL_H;
	delay();
	SCL_L;                
	delay();
}
/*******************************************
 * 函数名称：write0
 * 功    能：向IIC总线发送一个0
 * 参    数：无
 * 返回值  ：无
 * ********************************************/
void write0(void)
{
	SDA_L;
	delay();
	SCL_H;
	delay();             
	SCL_L;                
	delay();
}
/*******************************************
 * 函数名称：write1byte
 * 功    能：向IIC总线发送一个字节的数据
 * 参    数：wdata--发送的数据
 * 返回值  ：无
 * ********************************************/
void write1byte(uchar wdata)
{
	uchar i;

	for(i = 8;i > 0;i--)
	{
		if(wdata & 0x80)    write1();
		else                 write0();
		wdata <<= 1;
	}                  

	SDA_H;
	__delay_cycles(6);
}
/*******************************************
 * 函数名称：writeNbyte
 * 功    能：向IIC总线发送N个字节的数据
 * 参    数：outbuffer--指向发送数据存放首地址
 *           的指针
 *                     n--数据的个数
 *                     返回值  ：发送是否成功的标志：1--成功，0--失败
 *                     ********************************************/
uchar writeNbyte(uchar * outbuffer,uchar n)
{
	uchar i;

	for(i = 0;i < n;i++)
	{
		write1byte(* outbuffer);
		if(check())      
		{
			outbuffer++;            
		}
		else 
		{
			stop();
			return FALSE;
		}
	}

	stop();
	return TRUE;            
}
/*******************************************
 * 函数名称：read1byte
 * 功    能：从IIC总线读取一个字节
 * 参    数：无
 * 返回值  ：读取的数据
 * ********************************************/
uchar read1byte(void)
{
	uchar  rdata = 0x00,i;
	uchar flag;

	for(i = 0;i < 8;i++)
	{
		SDA_H;
		delay();
		SCL_H;
		SDA_in;
		delay();
		flag = SDA_val;
		rdata <<= 1;
		if(flag)    rdata |= 0x01;
		SDA_out;
		SCL_L;
		delay();
	}

	return rdata;
}
/*******************************************
 * 函数名称：readNbyte
 * 功    能：从IIC总线读取N个字节的数据
 * 参    数：inbuffer--读取后数据存放的首地址
 *           n--数据的个数
 *           返回值  ：无
 *           ********************************************/
void readNbyte(uchar * inbuffer,uchar n)
{
	uchar i;

	for(i = 0;i < n;i++)
	{
		inbuffer[i] = read1byte();
		if(i < (n-1))    mack();
		else            mnack();
	}

	stop();
}
//#include "IIC.h"
//typedef unsigned char uchar;
//typedef unsigned int  uint;



/*******************************************
函数名称：delay_10ms
功    能：延时约6ms，等待EEPROM完成内部写入
参    数：无
返回值  ：无
********************************************/
void delay_10ms(void)
{
    volatile uint i = 10;
    while(i--)
    __delay_cycles(6000);
}
/*******************************************
函数名称：Write_1Byte
功    能：向EEPROM中写入1个字节的数据
参    数：Wdata--写入的数据
          dataaddress--数据的写入地址
返回值  ：写入结果：1--成功，0--失败
********************************************/
uchar Write_1Byte(uchar wdata,uchar dataaddress)
{
    start();
    write1byte(deviceaddress);
    if(check()) 
        write1byte(dataaddress);
    else 
        return 0;
    if(check()) 
        write1byte(wdata);
    else 
        return 0;
    if(check())        stop();
    else            return 0;
    
    delay_10ms();       //等待EEPROM完成内部写入
    return 1; 
}
/*******************************************
函数名称：Write_NByte
功    能：向EEPROM中写入N个字节的数据
参    数：outbuf--指向写入数据存放首地址的指针
          n--数据个数，最大不能超过8，由页地址
             决定其最大长度
          dataaddress--数据写入的首地址
返回值  ：写入结果：1--成功，0--失败
********************************************/
uchar Write_NByte(uchar * outbuf,uchar n,uchar dataaddress)
{
    uchar  flag; 
    
    start();
    write1byte(deviceaddress);                  //写入器件地址
    if(check() == 1) 
        write1byte(dataaddress);                //写入数据字地址
    else 
        return 0;
    if(check()) 
        flag=writeNbyte(outbuf,n);
    else 
        return 0;
    delay_10ms();       //等待EEPROM完成内部写入
    if(flag)    return 1;
    else        return 0;

}
/*******************************************
函数名称：Read_1Byte_currentaddress
功    能：从EEPROM的当前地址读取1个字节的数据
参    数：无
返回值  ：读取的数据
********************************************/
uchar Read_1Byte_currentaddress(void)
{
    uchar temp;
    
    start();
    write1byte((deviceaddress|0x01));
    if(check())    
        temp = read1byte();
    else 
        return 0;
    mnack();
    stop();
    return temp;
}
/*******************************************
函数名称：Read_NByte_currentaddress
功    能：从EEPROM的当前地址读取N个字节的数据
参    数：readbuf--指向保存数据地址的指针
          n--读取数据的个数
返回值  ：读取结果：1--成功，0--失败
********************************************/
uchar Read_NByte_currentaddress(uchar * readbuf,uchar n)
{   
    start();
    write1byte((deviceaddress|0x01));
    if(check()) 
        readNbyte(readbuf,n);
    else 
        return 0;
    
    return  1;
}

/*******************************************
函数名称：Read_1Byte_Randomaddress
功    能：从EEPROM的指定地址读取1个字节的数据
参    数：dataaddress--数据读取的地址
返回值  ：读取的数据
********************************************/
uchar Read_1Byte_Randomaddress(uchar dataaddress)
{
    uchar temp;
    
    start();
    write1byte(deviceaddress);
    if(check())    
        write1byte(dataaddress);
    else 
        return 0;
    if(check()) 
    {
        start();
        write1byte((deviceaddress|0x01));
    }
    else    
        return 0;
    if(check())    
        temp = read1byte();
    else 
        return 0;

    mnack();
    stop();
    return temp;
}
/*******************************************
函数名称：Read_NByte_Randomaddress
功    能：从EEPROM的指定地址读取N个字节的数据
参    数：readbuf--指向保存数据地址的指针
          n--读取数据的个数
          dataaddress--数据读取的首地址
返回值  ：读取结果：1--成功，0--失败
********************************************/
uchar Read_NByte_Randomaddress(uchar * readbuf,uchar n,uchar dataaddress)
{
    start();
    write1byte(deviceaddress);
    if(check())    
        write1byte(dataaddress);
    else 
        return 0;
    if(check()) 
    {
        start();
        write1byte(deviceaddress|0x01);
    }
    else 
        return 0;
    if(check()) 
        readNbyte(readbuf,n);
    else 
        return 0;
    
    return 1;    
}

