#include "hal_key.h"
#include "hal_uart.h"
#include "gizwits_protocol.h"
#include "gizwits_product.h"

unsigned int sec1000 = 0;
extern unsigned char	skeycount;		//���ð���ʱ��������
extern unsigned char	skpttime;		//���ð���ʱ��
extern unsigned char	skpflag;				//���ð������±�־

/*************���ڳ�ʼ������*************************/
void uart_init(void)
{
    P3SEL |= 0x30;                            // ѡ��P3.4��P3.5��UART0,P3.6.P3.7��UART1
    P3SEL |= 0xC0;                            //��P3.6��P3.7ѡ��UART1��ͨ�Ŷ˿���8266ͨ��
    
    ME1 |= UTXE0 + URXE0;                     // ʹ��USART0�ķ��ͺͽ���
    ME2 |= UTXE1 + URXE1;                     //ʹ��USART1��TXD��RXD
    
    UCTL0 |= CHAR;                            // ѡ��8λ�ַ�
    UCTL1 |= CHAR;                            //ѡ��8-bit�ַ�
    
    UTCTL0 |= SSEL1;                          //����ʱ��ѡ��ACLK
    UTCTL1 |= SSEL0;                          //����ʱ��ѡ��MCLK
    
    UBR01 = 0x03;                             // ������9600,
    UBR11 = 0x00;                              
    UMCTL1 = 0x4A;                            // ������У�飬�����430�û��ֲ�
    
    UBR00 = 0x45;                             //������115200
    UBR10 = 0x00;
    UMCTL0 = 0x55;                            //����
    
    UCTL0 &= ~SWRST;                          // ��ʼ��UART0״̬��
    UCTL1 &= ~SWRST;                          //��ʼ��UART״̬��
    
    IE1 |= URXIE0;                            // ʹ��USART0�Ľ����ж�
    IE2 |= URXIE1;
       
}//ʱ�ӳ�ʹ������
void int_clk()
{
	volatile unsigned int i;
   // P5DIR |= 0x10;                            // P5.4= ���
    //P5SEL |= 0x10;                            // P5.4= MCLKģʽ  
    BCSCTL1 &= ~XT2OFF;                       // XT2= HF XTAL
    do
    {
        IFG1 &= ~OFIFG;                        // ��� OSCFault λ
        for (i = 0xFF; i > 0; i--);            // ��־λ������ʱ
    }
    while ((IFG1 & OFIFG));                   // OSCFault λ�Ƿ����óɹ�
    BCSCTL2 |= SELM_2;                        // MCLK= XT2 (safe)
    BCSCTL2 |= SELS;					    	//��ʱ������Ϊ XT2δ��Ƶ
}

/*******************************************
�������ƣ�UART1_RXISR
��    �ܣ�UART1�Ľ����жϷ�����
��    ������
����ֵ  ����
********************************************/

#pragma vector = UART1RX_VECTOR
__interrupt void UART1_RXISR(void)
{
        uint8_t value;
        value = RXBUF1;
        gizPutData(&value, 1);
}
/*******************************************
�������ƣ�UART0_RXISR
��    �ܣ�UART0�Ľ����жϷ������������﻽��
          CPU��ʹ���˳��͹���ģʽ
��    ������
����ֵ  ����

********************************************/
#pragma vector = UART0RX_VECTOR           //�ж����
__interrupt void UART0_RXISR(void)
{ 
  return;
}

/***************************************************************
�������ƣ�uart1_byte(uchar xbyte)
�������ܣ�����1���ͺ���
���������*str �ַ����׵�ַ
����ֵ����
****************************************************************/
void uart1_byte(uint8_t xbyte)
{
  TXBUF1 = xbyte;
  while((IFG2 & UTXIFG1)==0);
  IFG2 &= ~UTXIFG1;
}
/***************************************************************
�������ƣ�uart0_byte(uchar xbyte)
�������ܣ�����0���ͺ���
���������*str �ַ����׵�ַ
����ֵ����
****************************************************************/
void uart0_byte(uint8_t xbyte0)
{
  TXBUF0 = xbyte0;
  while((IFG1 & UTXIFG0)==0);
  IFG1 &= ~UTXIFG0;
}
/*********************************************************************
 * ������   :   putchar,�����ض����Զ����Ǳ�׼�⺯��
 * �������� ��  �򴮿��ն˷���һ���ַ�
 * �β�     ��  cΪ�����͵��ַ�
 * ����ֵ   ��  c
*********************************************************************/
 
int putchar(int ch)
{   
  if (ch == '\n')           //  '\n'(�س�)��չ�� '\n''\r' (�س�+����) 
    {
        uart0_byte('\r') ;   //0x0d ����
    }

    uart0_byte(ch);
    return (ch);
}
/***************************************************************
�������ƣ�TimerAInit() 
�������ܣ���ʱ����ʼ��
���������
����ֵ����
****************************************************************/
void TimerAInit()
{
  //  P2IFG = 0x00;                          //P2�жϱ�־λ����
  //  P2DIR &=~ (BIT0+BIT1);                        //Ϊ����
   // P2IES  |= BIT0;                         //P2.0ѡ���½����ж�  
   // P2IES&=~BIT1;                      //P2.1�������ж�
  //  P2IE |= BIT0+BIT1;                          //��P2.0�ж�ʹ��
    CCR0 = 32768/1000;                              //���ö�ʱ��A���ж�ʱ��Ϊ1ms
    TACTL = TASSEL_1 + MC_1;             //����ʱ��ACLK, ������ģʽ8��Ƶ+ID_3
    CCTL0 |= CCIE; 
}
/***************************************************************
�������ƣ�Timer_A() 
�������ܣ���ʱ���жϺ���
���������
����ֵ����
****************************************************************/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void) 
{
        gizTimerMs();
  	sec1000++;
	if(sec1000 >= 1000)	//1��ʱ�� (1000*1ms=1000ms=1s)
	{
		sec1000 = 0;
		//����Ϊ���ù��ܼ��İ���ʱ����������
		if(skpflag)
		{
		 	skeycount++;
			if(BUTTON_S1) skpttime=skeycount;
		}
	}
}