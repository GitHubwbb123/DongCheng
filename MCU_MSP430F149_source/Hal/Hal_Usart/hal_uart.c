#include "hal_key.h"
#include "hal_uart.h"
#include "gizwits_protocol.h"
#include "gizwits_product.h"

unsigned int sec1000 = 0;
extern unsigned char	skeycount;		//设置按键时长计数器
extern unsigned char	skpttime;		//设置按键时长
extern unsigned char	skpflag;				//设置按键按下标志

/*************串口初始化函数*************************/
void uart_init(void)
{
    P3SEL |= 0x30;                            // 选择P3.4和P3.5做UART0,P3.6.P3.7做UART1
    P3SEL |= 0xC0;                            //将P3.6，P3.7选做UART1的通信端口与8266通信
    
    ME1 |= UTXE0 + URXE0;                     // 使能USART0的发送和接受
    ME2 |= UTXE1 + URXE1;                     //使能USART1的TXD和RXD
    
    UCTL0 |= CHAR;                            // 选择8位字符
    UCTL1 |= CHAR;                            //选择8-bit字符
    
    UTCTL0 |= SSEL1;                          //驱动时钟选择ACLK
    UTCTL1 |= SSEL0;                          //驱动时钟选择MCLK
    
    UBR01 = 0x03;                             // 波特率9600,
    UBR11 = 0x00;                              
    UMCTL1 = 0x4A;                            // 波特率校验，具体见430用户手册
    
    UBR00 = 0x45;                             //波特率115200
    UBR10 = 0x00;
    UMCTL0 = 0x55;                            //调整
    
    UCTL0 &= ~SWRST;                          // 初始化UART0状态机
    UCTL1 &= ~SWRST;                          //初始化UART状态机
    
    IE1 |= URXIE0;                            // 使能USART0的接收中断
    IE2 |= URXIE1;
       
}//时钟出使化函数
void int_clk()
{
	volatile unsigned int i;
   // P5DIR |= 0x10;                            // P5.4= 输出
    //P5SEL |= 0x10;                            // P5.4= MCLK模式  
    BCSCTL1 &= ~XT2OFF;                       // XT2= HF XTAL
    do
    {
        IFG1 &= ~OFIFG;                        // 清除 OSCFault 位
        for (i = 0xFF; i > 0; i--);            // 标志位设置延时
    }
    while ((IFG1 & OFIFG));                   // OSCFault 位是否设置成功
    BCSCTL2 |= SELM_2;                        // MCLK= XT2 (safe)
    BCSCTL2 |= SELS;					    	//子时钟设置为 XT2未分频
}

/*******************************************
函数名称：UART1_RXISR
功    能：UART1的接收中断服务函数
参    数：无
返回值  ：无
********************************************/

#pragma vector = UART1RX_VECTOR
__interrupt void UART1_RXISR(void)
{
        uint8_t value;
        value = RXBUF1;
        gizPutData(&value, 1);
}
/*******************************************
函数名称：UART0_RXISR
功    能：UART0的接收中断服务函数，在这里唤醒
          CPU，使它退出低功耗模式
参    数：无
返回值  ：无

********************************************/
#pragma vector = UART0RX_VECTOR           //中断入口
__interrupt void UART0_RXISR(void)
{ 
  return;
}

/***************************************************************
函数名称：uart1_byte(uchar xbyte)
函数功能：串口1发送函数
输入参数：*str 字符串首地址
返回值：无
****************************************************************/
void uart1_byte(uint8_t xbyte)
{
  TXBUF1 = xbyte;
  while((IFG2 & UTXIFG1)==0);
  IFG2 &= ~UTXIFG1;
}
/***************************************************************
函数名称：uart0_byte(uchar xbyte)
函数功能：串口0发送函数
输入参数：*str 字符串首地址
返回值：无
****************************************************************/
void uart0_byte(uint8_t xbyte0)
{
  TXBUF0 = xbyte0;
  while((IFG1 & UTXIFG0)==0);
  IFG1 &= ~UTXIFG0;
}
/*********************************************************************
 * 函数名   :   putchar,函数重定向，自动覆盖标准库函数
 * 函数功能 ：  向串口终端发送一个字符
 * 形参     ：  c为待发送的字符
 * 返回值   ：  c
*********************************************************************/
 
int putchar(int ch)
{   
  if (ch == '\n')           //  '\n'(回车)扩展成 '\n''\r' (回车+换行) 
    {
        uart0_byte('\r') ;   //0x0d 换行
    }

    uart0_byte(ch);
    return (ch);
}
/***************************************************************
函数名称：TimerAInit() 
函数功能：定时器初始化
输入参数：
返回值：无
****************************************************************/
void TimerAInit()
{
  //  P2IFG = 0x00;                          //P2中断标志位清零
  //  P2DIR &=~ (BIT0+BIT1);                        //为输入
   // P2IES  |= BIT0;                         //P2.0选择下降沿中断  
   // P2IES&=~BIT1;                      //P2.1上升沿中断
  //  P2IE |= BIT0+BIT1;                          //打开P2.0中断使能
    CCR0 = 32768/1000;                              //设置定时器A的中断时间为1ms
    TACTL = TASSEL_1 + MC_1;             //计数时钟ACLK, 增计数模式8分频+ID_3
    CCTL0 |= CCIE; 
}
/***************************************************************
函数名称：Timer_A() 
函数功能：定时器中断函数
输入参数：
返回值：无
****************************************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void) 
{
        gizTimerMs();
  	sec1000++;
	if(sec1000 >= 1000)	//1秒时间 (1000*1ms=1000ms=1s)
	{
		sec1000 = 0;
		//以下为设置功能键的按键时长计数部分
		if(skpflag)
		{
		 	skeycount++;
			if(BUTTON_S1) skpttime=skeycount;
		}
	}
}