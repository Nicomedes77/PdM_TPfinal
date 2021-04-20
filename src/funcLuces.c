/*
 * funcLuces.c
 *
 *  Created on: 16 abr. 2021
 *      Author: Nicolás Vargas ALice
 *      Descripción: Archivo .c con funciones referidas al manejo de luces led de la
 *      placa EDU-CIAA-NXP
 */

#include "sapi.h"
#include "funcUART.h"

static 	uint8_t datoRecibido2;
static	int i = 0;
static 	bool_t primeraVez = TRUE;

/* Variable de Retardo no bloqueante */
delay_t delay1;

static void apagaLuces(void){
	gpioWrite(LEDB,OFF);
	gpioWrite(LED1,OFF);
	gpioWrite(LED2,OFF);
	gpioWrite(LED3,OFF);
}

static void prendeSec_N(uint8_t val){
	switch(val){
	case 'r':
		gpioWrite(LED2,ON); //rojo
		break;
	case 'a':
		gpioWrite(LED1,ON); //amarillo
		break;
	case 'b':
		gpioWrite(LEDB,ON); //azul
		break;
	case 'v':
		gpioWrite(LED3,ON); //verde
		break;
	default:
		break;
	}
}

void creaSec(bool_t sentido){
		primeraVez = TRUE;
		uint8_t sec_nueva[20];
		uint8_t datoSecNueva;
		i = 0;
		int n_leds;

		printf("Ingresando valores... \n");
		printf(" \n");

		do{
			//uartReadByte(UART_USB, &datoSecNueva);
			while(!uartReadByte(UART_USB, &datoSecNueva)){}	// ESPERA UN COMANDO
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
		}while(datoSecNueva != 'x');

	printf("secuencia creada! \n");
	printf(" \n");
	printf("ejecutando secuencia...\n");
	printf(" \n");

n_leds = i;

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
	if(datoSecNueva == 'a'){
		sentido = FALSE;
	}
	if(datoSecNueva == 'h'){
		sentido = TRUE;
	}
}
while(datoSecNueva!= 'p');

for(i = 0; i < n_leds; i++){
	sec_nueva[i] = 0;
}
primeraVez = TRUE;
apagaLuces();					//Apaga todas las luces
return;
}

void haceSec1(bool_t sentido){
	datoRecibido2 = 0;
	gpioMap_t sec_led1[] = {LED2, LED1, LEDB, LED1};	//secuencia prefijada1
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

