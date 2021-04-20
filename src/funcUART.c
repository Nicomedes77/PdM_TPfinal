/*
 * funcUART.c
 *
 *  Created on: 16 abr. 2021
 *      Author: Nicolás Vargas Alice
 *      Descripción: Archivo .c con funciones referidas al manejo del puerto UART USB
 *      placa EDU-CIAA-NXP
 */

#include "sapi.h"
#include "funcUART.h"
#include "funcLuces.h"
#include "luces_UART.h"

bool_t sentido = TRUE;
delay_t delay1;

void inicializacionUART(void){
	uartConfig(UART_USB,115200);
}

void inicializaMEF(estadoMEF_t* sec){
	sec = PARA;
}

void inicializaADC(void){
	adcConfig( ADC_ENABLE ); /* ADC */
}

void actualizaMEF(estadoMEF_t* sec){

	uint8_t	datoRecibido = 0;
	sentido = TRUE;		//sentido = TRUE -> sentido horario || sentido = FALSE -> sentido antihorario
	static uint16_t valADC = 0;

	switch(*sec){
//
	case PARA:
//
		printf("\n");
		printf("estado -> PARA. \n");
		printf("\n");
		printf("****************************** \n");
		printf("Sistema de control de luces \n");
		printf("****************************** \n");
		printf("\n");
		printf("Por favor, ingrese la letra 'c' para configurar. \n");
		printf("\n");

		do{
			uartReadByte(UART_USB, &datoRecibido);
		}
		while(datoRecibido!= 'c');

//		printf("estoy afuera\n");
		*sec = CONFIGURACION;
		break;
//
	case CONFIGURACION:
//
		printf("****************************** \n");
		printf("estado -> CONFIGURACION. \n");
		printf("\n");
		printf("Elija el tiempo de ejecucion de la secuencia girando el potenciometro: \n");
		printf("Ingrese 's' si quiere ingresar una secuencia propia. \n");
		printf("Ingrese 'f' si quiere elegir secuencia cargada. \n");
		printf("Ingrese 'p' si volver al inicio. \n");
		printf("****************************** \n");
		printf("\n");
//
		while(!uartReadByte(UART_USB, &datoRecibido)){// Elije el tiempo de secuencia y espera comando

			//lee ADC1
			valADC = adcRead(CH1);
			if(valADC > 800){
				printf("t = 1500 ms \n");
				printf("\n");
				delayConfig( &delay1, 1500);
			}
			if((valADC <= 800)&&(valADC > 200)){
				printf("t = 1000 ms \n");
				printf("\n");
				delayConfig( &delay1, 1000);
			}
			if(valADC < 200){
				printf("t = 500 ms \n");
				printf("\n");
				delayConfig( &delay1, 500);
			}
			delay(1000);
		}
//
		if( datoRecibido == 's' ){
        	   *sec = ARMO_SECUENCIA;
           }
		else if( datoRecibido == 'f' ){
        	   *sec = SECUENCIA_FIJA;
           }
		else if( datoRecibido == 'p' ){
        	   *sec = PARA;
        	   printf("\n");
           }
        else{
        	   printf("Dato ingresado invalido. Ingrese valor correcto\n");
       		printf("\n");
           }
		break;
//
	case ARMO_SECUENCIA:
		printf("****************************** \n");
		printf("estado -> ARMO_SECUENCIA. \n");
		printf("\n");
		printf("Ingrese la secuencia con los letras r (rojo), b (Azul), V (verde), A (amarillo).\n");
		printf("Ingresando la letra 'p' vuelve al inicio.\n");
		printf("****************************** \n");
		printf("\n");
//		while(!uartReadByte(UART_USB, &datoRecibido)){}	// ESPERA UN COMANDO
		printf("Sentido Horario (ingrese 'h') o Antihorario (ingrese 'a')? \n");
		printf("Ingresando: \n");
		printf("'h' ejecuta la secuencia en sentido horario\n");
		printf("'a' ejecuta la secuencia en sentido antihorario\n");
		printf("'p' vuelve al menu inicial\n");
		creaSec(sentido);
		*sec = PARA;
		break;
//
	case SECUENCIA_FIJA:
		printf("****************************** \n");
		printf("estado -> SECUENCIA_FIJA. \n");
		printf("\n");
		printf("Ingrese '1', '2' o '3' para elegir la secuencia. \n");
		printf("\n");
		//pregunta si la quiere en sentido horario o antihorario

		while(!uartReadByte(UART_USB, &datoRecibido)){} //ESPERA UN COMANDO
//
           if( datoRecibido == '1' ){
        	   printf("Sentido Horario (ingrese 'h') o Antihorario (ingrese 'a')? \n");
        	   printf("Ingresando: \n");
        	   printf("'h' ejecuta la secuencia en sentido horario\n");
        	   printf("'a' ejecuta la secuencia en sentido antihorario\n");
        	   printf("'p' vuelve al menu inicial\n");
        	   printf("ejecutando secuencia 1...\n");
        	   haceSec1(sentido);
        	   *sec = PARA;
           }
           else if( datoRecibido == '2' ){
        	   printf("Sentido Horario (ingrese 'h') o Antihorario (ingrese 'a')? \n");
        	   printf("Ingresando: \n");
        	   printf("'h' ejecuta la secuencia en sentido horario\n");
        	   printf("'a' ejecuta la secuencia en sentido antihorario\n");
        	   printf("'p' vuelve al menu inicial\n");
        	   printf("ejecutando secuencia 2...\n");
        	   printf(" \n");
        	   haceSec2(sentido);
        	   *sec = PARA;
           }
           else if( datoRecibido == '3' ){
        	   printf("Sentido Horario (ingrese 'h') o Antihorario (ingrese 'a')? \n");
        	   printf("Ingresando: \n");
        	   printf("'h' ejecuta la secuencia en sentido horario\n");
        	   printf("'a' ejecuta la secuencia en sentido antihorario\n");
        	   printf("'p' vuelve al menu inicial\n");
        	   printf("ejecutando secuencia 3...\n");
        	   printf(" \n");
        	   haceSec3(sentido);
        	   *sec = PARA;
           }
           else{
        	   printf("ingresa comando invalido. vuelve al inicio \n");
        	   printf(" \n");
        	   *sec = PARA;
           }
		break;
//
	default:
		sec = PARA;
		printf("Estado erroneo. Vuelva al estado inicial\r\n");
		printf(" \n");
		break;
	}
}
