#ifndef __HAL_KEY_H__
#define __HAL_KEY_H__

#include  <msp430x14x.h>
#include <stdint.h>

#define LONGPRESS 2				//���峤�����ü���ʱ��	

//************ ������IO�ں궨�� *************
#define BUTTON_S1        (P1IN & BIT0)
#define BUTTON_S2        (P1IN & BIT1)
void setkeyscan();				//���ü���ɨ���жϺ���
void pro_sklp();				//�������ù��ܼ��Ĵ�����
void pro_sksp();				//�̰����ù��ܼ��Ĵ�����

#endif