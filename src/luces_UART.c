/*=============================================================================
 * Author: Nicolas Vargas Alice <nicolas.vargas.a@gmail.com>
 * Date: 2021/04/16
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "luces_UART.h"
#include "funcLuces.h"
#include "funcUART.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

estadoMEF_t luces; 		// Variable de estado
/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();
   inicializacionUART();
   inicializaMEF(&luces);
   inicializaADC();
   // ----- Repeat for ever -------------------------
   while(true) {
	   actualizaMEF(&luces);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
