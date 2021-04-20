/*
 * funcLuces.h
 *
 *  Created on: 16 abr. 2021
 *      Author: nicolas
 */

#ifndef CODIGOSNICO_LUCES_UART_INC_FUNCLUCES_H_
#define CODIGOSNICO_LUCES_UART_INC_FUNCLUCES_H_

#include "sapi.h"
#include "funcUART.h"
#include "funcLuces.h"
#include "luces_UART.h"

static void apagaLuces(void);
void haceSec1(bool_t sentido);
void haceSec2(bool_t sentido);
void haceSec3(bool_t sentido);
void creaSec(bool_t sentido);
static void prendeSec_N(uint8_t val);

#endif /* CODIGOSNICO_LUCES_UART_INC_FUNCLUCES_H_ */
