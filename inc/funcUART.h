/*
 * funcUART.h
 *
 *  Created on: 16 abr. 2021
 *      Author: nicolas
 */


#ifndef CODIGOSNICO_LUCES_UART_INC_FUNCUART_H_
#define CODIGOSNICO_LUCES_UART_INC_FUNCUART_H_

#include "sapi.h"
#include "luces_UART.h"

typedef enum{
   PARA,
   CONFIGURACION,
   ARMO_SECUENCIA,
   SECUENCIA_FIJA,
}estadoMEF_t;


void inicializacionUART(void);

void inicializaMEF(estadoMEF_t * sec);

void inicializaADC(void);

void actualizaMEF(estadoMEF_t * sec);

#endif /* CODIGOSNICO_LUCES_UART_INC_FUNCUART_H_ */
