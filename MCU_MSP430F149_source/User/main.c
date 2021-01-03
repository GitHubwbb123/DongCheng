/**
************************************************************
* @file         main.c
* @brief        MCU�� ����ļ�
* @author       Gizwits
* @date         2016-09-05
* @version      V03010101
* @copyright    Gizwits
* 
* @note         ������.ֻΪ����Ӳ������
*               Gizwits Smart Cloud  for Smart Products
*               ����|��ֵ?|����|����|��ȫ|����|����|��̬
*               www.gizwits.com
*
***********************************************************/
/********************************************************
** ������ֲ˵��
*
* 1��ʵ����ģ��ͨ�Ŵ���������1���ж�������д�뻷�λ�����;2��ʵ��uartWrite()���ڷ��ͺ�����
* 2��ʵ�ִ��ڴ�ӡ����printf()
* 3��ʵ��ms��ʱ����gizTimerMs()ά��ϵͳʱ��
* 4��ʵ��MCU��λ����,ģ�������MCU��λ
* 5��ʵ��������������,����gizwitsSetMode()����ʵ��ģ����������
* 6��ʵ��userHandle()���ݵĲɼ��������߼���
* 7��ʵ��gizwitsEventProcess()��������ľ���ִ��(�����߼�)
* 8��ʵ��mcuRestart()��λ����
* 
*
*********************************************************/


#include <string.h>
#include  <stdio.h>
#include "hal_uart.h"

#include "gizwits_protocol.h"
#include "gizwits_product.h"

/** �û�����ǰ�豸״̬�ṹ��*/
dataPoint_t currentDataPoint;

/**
* @brief������ں���

* �ڸú���������û���صĳ�ʼ��,�����߼�ѭ��
* @param none
* @return none
*/
int main(void)
{  
    WDTCTL = WDTPW + WDTHOLD;                 // �رտ��Ź�
    int_clk();
    TimerAInit() ;
    uart_init();                              //���ڳ�ʼ��
    _EINT();    
	
    userInit();

    gizwitsInit();
    
    printf("MCU Init !");
    
    while(1)
    {
        userHandle();
        
        gizwitsHandle((dataPoint_t *)&currentDataPoint);
        
        setkeyscan();					//��⹦�ܼ�
       
    }
}
