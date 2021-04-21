/*=============================================================================
 * Author: Nicolas Vargas Alice <nicolas.vargas.a@gmail.com>
 * Date: 2021/04/16
 *===========================================================================*/

/*=============================================================================
 * Descripción:
 *
 * El presente proyecto implementa una Maquina de Estados Finitos (MEF) sobre
 * una comunicación UART. Esta MEF controla el funcionamiento de varias
 * secuencias de luces.
 *
 * Este archivo trabaja en conjunto con los siguientes archivos source (.c):
 *
 * funcUART.c
 * funcLuces.c
 *
 * Este archivo trabaja en conjunto con los siguientes archivos include (.h):
 *
 * funcUART.h
 * funcLuces.h
 * sapi.h
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "luces_UART.h"
#include "funcLuces.h"
#include "funcUART.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

// Variable de estado
estadoMEF_t luces;

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
	// Inicialización de placa, perifericos utilizados y MEF.
	boardInit();
	inicializacionUART();
	inicializaMEF(&luces);
	inicializaADC();
	// ----- Repeat for ever -------------------------
	while(true) {
		// actualización de MEF.
		actualizaMEF(&luces);
	}

	// YOU NEVER REACH HERE, because this program runs directly or on a
	// microcontroller and is not called by any Operating System, as in the
	// case of a PC program.
	return 0;
}
