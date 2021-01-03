#ifndef __HAL_KEY_H__
#define __HAL_KEY_H__

#include  <msp430x14x.h>
#include <stdint.h>

#define LONGPRESS 2				//定义长按设置键的时间	

//************ 按键的IO口宏定义 *************
#define BUTTON_S1        (P1IN & BIT0)
#define BUTTON_S2        (P1IN & BIT1)
void setkeyscan();				//设置键的扫描判断函数
void pro_sklp();				//长按设置功能键的处理函数
void pro_sksp();				//短按设置功能键的处理函数

#endif