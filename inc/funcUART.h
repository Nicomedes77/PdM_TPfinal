/*=============================================================================
 * Author: Nicolas Vargas Alice <nicolas.vargas.a@gmail.com>
 * Date: 2021/04/16
 *===========================================================================*/
/*=============================================================================
 * funcUART.h
 * Declaración de variables y prototipos de funciones.
 *===========================================================================*/


#ifndef CODIGOSNICO_LUCES_UART_INC_FUNCUART_H_
#define CODIGOSNICO_LUCES_UART_INC_FUNCUART_H_

#include "sapi.h"
#include "luces_UART.h"

/*
 * Variables con estados posibles de la MEF.
 */
typedef enum{
	PARA,
	CONFIGURACION,
	ARMO_SECUENCIA,
	SECUENCIA_FIJA,
}estadoMEF_t;

/* Funcion: inicializacionUART
 * Se encarga de la configuración inicial de la UART. */
void inicializacionUART(void);

/* Funcion: inicializaMEF
 * Se encarga de setear los estados inciales de la MEF. */
void inicializaMEF(estadoMEF_t * sec);

/* Funcion: inicializaADC
 * Se encarga de la configuración inicial de la ADC. */
void inicializaADC(void);

/* Funcion: actualizaMEF
 * Se encarga de actualizar los estados de la MEF a partir de lo recibido por la UART. */
void actualizaMEF(estadoMEF_t * sec);

/* Funcion: msjSentidoSec
 * Se encarga de mostrar en pantalla un mensaje al usuario referido al sentido de ejecucion de la secuencia. */
void msjSentidoSec(void);

#endif /* CODIGOSNICO_LUCES_UART_INC_FUNCUART_H_ */
