/**
************************************************************
* @file         main.c
* @brief        MCU版 入口文件
* @author       Gizwits
* @date         2016-09-05
* @version      V03010101
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值?|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
/********************************************************
** 代码移植说明
*
* 1、实现与模组通信串口驱动（1、中断收数据写入环形缓冲区;2、实现uartWrite()串口发送函数）
* 2、实现串口打印函数printf()
* 3、实现ms定时器，gizTimerMs()维护系统时间
* 4、实现MCU复位函数,模组可请求MCU复位
* 5、实现配置入网功能,调用gizwitsSetMode()函数实现模组配网功能
* 6、实现userHandle()数据的采集（上行逻辑）
* 7、实现gizwitsEventProcess()控制命令的具体执行(下行逻辑)
* 8、实现mcuRestart()复位函数
* 
*
*********************************************************/


#include <string.h>
#include  <stdio.h>
#include "hal_uart.h"

#include "gizwits_protocol.h"
#include "gizwits_product.h"

/** 用户区当前设备状态结构体*/
dataPoint_t currentDataPoint;

/**
* @brief程序入口函数

* 在该函数中完成用户相关的初始化,及主逻辑循环
* @param none
* @return none
*/
int main(void)
{  
    WDTCTL = WDTPW + WDTHOLD;                 // 关闭看门狗
    int_clk();
    TimerAInit() ;
    uart_init();                              //串口初始化
    _EINT();    
	
    userInit();

    gizwitsInit();
    
    printf("MCU Init !");
    
    while(1)
    {
        userHandle();
        
        gizwitsHandle((dataPoint_t *)&currentDataPoint);
        
        setkeyscan();					//检测功能键
       
    }
}
