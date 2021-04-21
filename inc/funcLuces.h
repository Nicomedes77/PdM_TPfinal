/*=============================================================================
 * Author: Nicolas Vargas Alice <nicolas.vargas.a@gmail.com>
 * Date: 2021/04/16
 *===========================================================================*/
/*=============================================================================
 * funcluces.h
 * Declaración de variables y prototipos de funciones.
 *===========================================================================*/

#ifndef CODIGOSNICO_LUCES_UART_INC_FUNCLUCES_H_
#define CODIGOSNICO_LUCES_UART_INC_FUNCLUCES_H_

#include "sapi.h"
#include "funcUART.h"
#include "funcLuces.h"
#include "luces_UART.h"

/* Funcion: apagaLuces
 * apaga todas las luces de la placa */
static void apagaLuces(void);

/* Funcion: haceSec1
 * ejecuta secuencia prefijada Nº1 */
void haceSec1(bool_t sentido);

/* Funcion: haceSec2
 * ejecuta secuencia prefijada Nº2 */
void haceSec2(bool_t sentido);

/* Funcion: haceSec3
 * ejecuta secuencia prefijada Nº3 */
void haceSec3(bool_t sentido);

/* Funcion: creaSec
 * controla la creación de una secuencia nueva */
void creaSec(bool_t sentido);

/* Funcion: prendeSec_N
 * enciende la luz correspondiente a la secuencia creada en la funcion creaSec() */
static void prendeSec_N(uint8_t val);

#endif /* CODIGOSNICO_LUCES_UART_INC_FUNCLUCES_H_ */
