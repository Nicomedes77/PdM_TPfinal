/*=============================================================================
 * Author: Nicolas Vargas Alice <nicolas.vargas.a@gmail.com>
 * Date: 2021/04/16
 *===========================================================================*/
/*=============================================================================
 * funcUART.c
 * Declaración de variables e implementacion de funciones relacionadas a la
 * ejecución de las secuencias de luces.
 *===========================================================================*/

#include "sapi.h"
#include "funcUART.h"

static 	uint8_t datoRecibido2;	//variable de lectura de dato recibido en UART
static	int i = 0;				//indice para estructuras de control
static 	bool_t primeraVez = TRUE;	//variable que indica si se va a comenzar o ya comenzó una secuencia.


delay_t delay1;	// Variable de Retardo no bloqueante

static void apagaLuces(void){
	gpioWrite(LEDB,OFF);
	gpioWrite(LED1,OFF);
	gpioWrite(LED2,OFF);
	gpioWrite(LED3,OFF);
}

static void prendeSec_N(uint8_t val){
	switch(val){
	case 'r':
		gpioWrite(LED2,ON); //LED rojo
		break;
	case 'a':
		gpioWrite(LED1,ON); //LED amarillo
		break;
	case 'b':
		gpioWrite(LEDB,ON); //LED azul
		break;
	case 'v':
		gpioWrite(LED3,ON); //LED verde
		break;
	default:
		break;
	}
}

void creaSec(bool_t sentido){
	primeraVez = TRUE;
	uint8_t sec_nueva[20];	//Array que almacena la secuencia enviada por UART.
	uint8_t datoSecNueva;	//Variable que almacena dato recibido por UART.
	i = 0;					//Inicialización de indice.
	int n_leds;				//variable que almacena el largo de la secuencia enviada.

	printf("Ingresando valores... \n");
	printf(" \n");

	do{
		//uartReadByte(UART_USB, &datoSecNueva);
		while(!uartReadByte(UART_USB, &datoSecNueva)){}	// ESPERA UN COMANDO
		if(datoSecNueva == 'p'){
			return;
		}
		if(datoSecNueva == 'r'){
			sec_nueva[i] = datoSecNueva;
			i++;
		}
		if(datoSecNueva == 'b'){
			sec_nueva[i] = datoSecNueva;
			i++;
		}
		if(datoSecNueva == 'v'){
			sec_nueva[i] = datoSecNueva;
			i++;
		}
		if(datoSecNueva == 'a'){
			sec_nueva[i] = datoSecNueva;
			i++;
		}
	}while(datoSecNueva != 'x');	//el caracter 'x' indica el fin de la secuencia enviada. Cuando se detecta, deja de leer UART.

	printf("secuencia creada! \n");
	printf(" \n");
	msjSentidoSec();	//muestra información respecto al sentido de ejecución.
	printf(" \n");
	printf("ejecutando secuencia...\n");
	printf(" \n");

	n_leds = i;			// a partir del valor del indice i en este punto, conozco el largo de la secuencia enviada.

	do{
		if (delayRead(&delay1)){
			apagaLuces();					//Apaga todas las luces
			if(primeraVez == TRUE){
				i = 0;
				primeraVez = FALSE;
			}

			if(sentido == TRUE){			//sentido = FALSE
				if(i == n_leds){
					prendeSec_N(sec_nueva[i]);
					i = 0;
				}
				else{
					prendeSec_N(sec_nueva[i]);
					i++;
				}
			}
			else{							//sentido = FALSE
				if(i == 0){
					prendeSec_N(sec_nueva[i]);
					i = n_leds;
				}
				else{
					prendeSec_N(sec_nueva[i]);
					i--;
				}
			}
		}

		uartReadByte(UART_USB, &datoSecNueva);
		if(datoSecNueva == 'a'){	// si recibo 'a', sentido ANTIHORARIO de ejecucion.
			sentido = FALSE;
		}
		if(datoSecNueva == 'h'){ // si recibo 'h', sentido HORARIO de ejecucion.
			sentido = TRUE;
		}
	}
	while(datoSecNueva!= 'p');	// si recibo 'p', vuelve al estado inicial del sistema.

	//limpia el vector de almacenaje de la secuencia enviada
	for(i = 0; i < n_leds; i++){
		sec_nueva[i] = 0;
	}
	primeraVez = TRUE;
	apagaLuces();					//Apaga todas las luces
	return;
}

//secuencia prefijada Nº1
void haceSec1(bool_t sentido){
	datoRecibido2 = 0;
	gpioMap_t sec_led1[] = {LED2, LED1, LEDB, LED1};
	static uint8_t n_leds = sizeof(sec_led1)/sizeof(gpioMap_t);

	do{
		if (delayRead(&delay1)){
			apagaLuces();					//Apaga todas las luces
			if(primeraVez == TRUE){
				i = 0;
				primeraVez = FALSE;
			}

			if(sentido == TRUE){			//sentido = FALSE
				if(i == n_leds){
					i = 0;
					gpioWrite(sec_led1[i],ON);
				}
				else{
					i++;
					gpioWrite(sec_led1[i],ON);
				}
			}
			else{							//sentido = FALSE
				if(i == 0){
					i = n_leds;
					gpioWrite(sec_led1[i],ON);
				}
				else{
					i--;
					gpioWrite(sec_led1[i],ON);
				}
			}
		}

		uartReadByte(UART_USB, &datoRecibido2);
		if(datoRecibido2 == 'a'){
			sentido = FALSE;
		}
		if(datoRecibido2 == 'h'){
			sentido = TRUE;
		}
	}
	while(datoRecibido2!= 'p');

	primeraVez = TRUE;
	apagaLuces();					//Apaga todas las luces
	return;
}

//secuencia prefijada Nº2
void haceSec2(bool_t sentido){
	datoRecibido2 = 0;
	gpioMap_t sec_led2[] = {LED3, LED2, LEDB, LED2};	//secuencia prefijada2
	static uint8_t n_leds = sizeof(sec_led2)/sizeof(gpioMap_t);

	do{
		if (delayRead(&delay1)){
			apagaLuces();					//Apaga todas las luces
			if(primeraVez == TRUE){
				i = 0;
				primeraVez = FALSE;
			}

			if(sentido == TRUE){			//sentido = FALSE
				if(i == n_leds){
					i = 0;
					gpioWrite(sec_led2[i],ON);
				}
				else{
					i++;
					gpioWrite(sec_led2[i],ON);
				}
			}
			else{							//sentido = FALSE
				if(i == 0){
					i = n_leds;
					gpioWrite(sec_led2[i],ON);
				}
				else{
					i--;
					gpioWrite(sec_led2[i],ON);
				}
			}
		}

		uartReadByte(UART_USB, &datoRecibido2);
		if(datoRecibido2 == 'a'){
			sentido = FALSE;
		}
		if(datoRecibido2 == 'h'){
			sentido = TRUE;
		}
	}
	while(datoRecibido2!= 'p');

	primeraVez = TRUE;
	apagaLuces();					//Apaga todas las luces
	return;
}

//secuencia prefijada Nº3
void haceSec3(bool_t sentido){
	datoRecibido2 = 0;
	gpioMap_t sec_led3[] = {LEDB, LED1, LED2, LED3};	//secuencia prefijada3
	static uint8_t n_leds = sizeof(sec_led3)/sizeof(gpioMap_t);

	do{
		if (delayRead(&delay1)){
			apagaLuces();					//Apaga todas las luces
			if(primeraVez == TRUE){
				i = 0;
				primeraVez = FALSE;
			}

			if(sentido == TRUE){			//sentido = FALSE
				if(i == n_leds){
					i = 0;
					gpioWrite(sec_led3[i],ON);
				}
				else{
					i++;
					gpioWrite(sec_led3[i],ON);
				}
			}
			else{							//sentido = FALSE
				if(i == 0){
					i = n_leds;
					gpioWrite(sec_led3[i],ON);
				}
				else{
					i--;
					gpioWrite(sec_led3[i],ON);
				}
			}
		}

		uartReadByte(UART_USB, &datoRecibido2);
		if(datoRecibido2 == 'a'){
			sentido = FALSE;
		}
		if(datoRecibido2 == 'h'){
			sentido = TRUE;
		}
	}
	while(datoRecibido2!= 'p');

	primeraVez = TRUE;
	apagaLuces();					//Apaga todas las luces
	return;
}
