#ifndef UART_H
#define UART_H
#include <stdint.h>
void UARTNT(uint32_t a,uint32_t b,uint16_t c);
void UARTTX (char * z);
uint8_t UARTRX( uint8_t *s);
#endif
