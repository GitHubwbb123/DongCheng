#include <hal_key.h>
#include <hal_uart.h>
#include "gizwits_protocol.h"


unsigned char	skeycount;		//设置按键时长计数器
unsigned char	skpttime;		//设置按键时长
unsigned char	skpflag;		//设置按键按下标志
unsigned char	longflag =0;		//设置长按标志
unsigned char	sflag;			//设置显示状态标志,0-普通运行,1-定时设置,2-日历时钟设置


void setkeyscan();				//设置键的扫描判断函数
void pro_sklp();				//长按设置功能键的处理函数
void pro_sksp();				//短按设置功能键的处理函数

 
//=======子程序==================================
/*检测及处理多功能设置按键k2*/
void setkeyscan()
{
	if (skpflag)										//判断是否已经有键按下未被处理
	{
		if(skeycount>LONGPRESS)							//如果是长按则执行长按键设置功能
		{
			pro_sklp();
			skpflag=0;
                        longflag=1;
		}
		else if((skpttime>0) && (skpttime<=LONGPRESS))	//否则如果是短按则执行短按的功能,都不是直接跳过
		{
			pro_sksp();
			skpflag=0;
		}
	}
	else
	{
		if(!BUTTON_S1)								//按下设置键
		{
			delay_ms(100);						//键盘防抖
			if((!BUTTON_S1) && longflag==0)
			{
				skeycount=0;					//初始化按键时长计数器
				skpttime=0;						//初始化按键时长
				skpflag=1;						//标志已经有键被按下
                                longflag=0;
			}
		}else{
                        longflag=0;
                }
	}
}

		
	

/*(短按k2)*/
void pro_sksp()
{
	sflag=0;								//设置状态标志
	//以下为短按键的处理程序
        printf("key1 Short Press,enter airlink");
	gizwitsSetMode(WIFI_AIRLINK_MODE);//进入airlink配网模式
}


/*(长按k2)*/
void pro_sklp()
{
	sflag=0;								//设置状态标志
	//以下为长按键的处理程序
        printf("key1 long Press,reset devide");
	gizwitsSetMode(WIFI_RESET_MODE);//reset模组

}

void key_init()
{
	skeycount=0;						        //初始化功能键按下时长计数器
	skpttime=0;							//初始化功能键按下的总时长
	sflag=0;							//初始化显示状态标志,0-普通运行,1-定时设置,2-日历时钟设置
        P1DIR|=BIT0;                                                   //按键S1端口做为输入端口
        P1DIR&=~BIT1;  
        P2DIR|=BIT0+BIT1+BIT2+BIT3;

}

