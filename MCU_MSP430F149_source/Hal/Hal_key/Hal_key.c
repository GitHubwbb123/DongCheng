#include <hal_key.h>
#include <hal_uart.h>
#include "gizwits_protocol.h"


unsigned char	skeycount;		//���ð���ʱ��������
unsigned char	skpttime;		//���ð���ʱ��
unsigned char	skpflag;		//���ð������±�־
unsigned char	longflag =0;		//���ó�����־
unsigned char	sflag;			//������ʾ״̬��־,0-��ͨ����,1-��ʱ����,2-����ʱ������


void setkeyscan();				//���ü���ɨ���жϺ���
void pro_sklp();				//�������ù��ܼ��Ĵ�����
void pro_sksp();				//�̰����ù��ܼ��Ĵ�����

 
//=======�ӳ���==================================
/*��⼰����๦�����ð���k2*/
void setkeyscan()
{
	if (skpflag)										//�ж��Ƿ��Ѿ��м�����δ������
	{
		if(skeycount>LONGPRESS)							//����ǳ�����ִ�г��������ù���
		{
			pro_sklp();
			skpflag=0;
                        longflag=1;
		}
		else if((skpttime>0) && (skpttime<=LONGPRESS))	//��������Ƕ̰���ִ�ж̰��Ĺ���,������ֱ������
		{
			pro_sksp();
			skpflag=0;
		}
	}
	else
	{
		if(!BUTTON_S1)								//�������ü�
		{
			delay_ms(100);						//���̷���
			if((!BUTTON_S1) && longflag==0)
			{
				skeycount=0;					//��ʼ������ʱ��������
				skpttime=0;						//��ʼ������ʱ��
				skpflag=1;						//��־�Ѿ��м�������
                                longflag=0;
			}
		}else{
                        longflag=0;
                }
	}
}

		
	

/*(�̰�k2)*/
void pro_sksp()
{
	sflag=0;								//����״̬��־
	//����Ϊ�̰����Ĵ������
        printf("key1 Short Press,enter airlink");
	gizwitsSetMode(WIFI_AIRLINK_MODE);//����airlink����ģʽ
}


/*(����k2)*/
void pro_sklp()
{
	sflag=0;								//����״̬��־
	//����Ϊ�������Ĵ������
        printf("key1 long Press,reset devide");
	gizwitsSetMode(WIFI_RESET_MODE);//resetģ��

}

void key_init()
{
	skeycount=0;						        //��ʼ�����ܼ�����ʱ��������
	skpttime=0;							//��ʼ�����ܼ����µ���ʱ��
	sflag=0;							//��ʼ����ʾ״̬��־,0-��ͨ����,1-��ʱ����,2-����ʱ������
        P1DIR|=BIT0;                                                   //����S1�˿���Ϊ����˿�
        P1DIR&=~BIT1;  
        P2DIR|=BIT0+BIT1+BIT2+BIT3;

}

