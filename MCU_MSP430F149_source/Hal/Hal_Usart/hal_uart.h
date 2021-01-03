#ifndef _UART_H
#define _UART_H

#include  <msp430x14x.h>
#include  <stdint.h>

#define CPU_F ((double)8000000)   
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))  
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 

void TimerAInit();
void uart_init(void);
void int_clk();

#endif