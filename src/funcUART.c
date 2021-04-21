/*=============================================================================
 * Author: Nicolas Vargas Alice <nicolas.vargas.a@gmail.com>
 * Date: 2021/04/16
 *===========================================================================*/
/*=============================================================================
 * funcUART.c
 * Declaración de variables e implementacion de funciones relacionadas al
 * periferico UART.
 *===========================================================================*/

#include "sapi.h"
#include "funcUART.h"
#include "funcLuces.h"
#include "luces_UART.h"

bool_t sentido = TRUE;	//variable que determina el sentido de ejecucion de la secuencia
delay_t delay1;			//variable para configurar delay no bloqueante que determina el tiempo de cambio de la secuencia.
uint8_t	datoRecibido = 0;	//variable que almacena el dato recibido por UART.

void inicializacionUART(void){
	uartConfig(UART_USB,115200); //configuración UART USB
}

void inicializaMEF(estadoMEF_t* sec){
	sec = PARA;		//estado inicial de la variable de estado de la MEF.
}

void inicializaADC(void){
	adcConfig( ADC_ENABLE ); //configuración ADC
}

void msjSentidoSec(void){
	printf("Sentido Horario (ingrese 'h') o Antihorario (ingrese 'a')? \n");
	printf("Ingresando: \n");
	printf("'h' ejecuta la secuencia en sentido horario\n");
	printf("'a' ejecuta la secuencia en sentido antihorario\n");
	printf("'p' vuelve al menu inicial\n");
}

void actualizaMEF(estadoMEF_t * sec){

	datoRecibido = 0;
	sentido = TRUE;						//sentido = TRUE -> sentido horario || sentido = FALSE -> sentido antihorario
	static uint16_t valADC = 0;			//variable de almacenado de dato recibido desde el ADC

	switch(*sec){
	//
	case PARA:	//estado PARA
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
	case CONFIGURACION: //estado CONFIGURACION
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
		while(!uartReadByte(UART_USB, &datoRecibido)){// Elije el tiempo de secuencia y espera comando.

			valADC = adcRead(CH1);	//lee valor desde ADC CH1
			if(valADC > 800){			//valADC > 800 => delay = 1500 ms
				printf("t = 1500 ms \n");
				//				printf("\n");
				delayConfig( &delay1, 1500);
			}
			if((valADC <= 800)&&(valADC > 200)){	// (200 < valADC <= 800) => delay = 1000 ms
				printf("t = 1000 ms \n");
				//				printf("\n");
				delayConfig( &delay1, 1000);
			}
			if(valADC < 200){ 						//valADC < 200 => delay = 500 ms
				printf("t = 500 ms \n");
				//				printf("\n");
				delayConfig( &delay1, 500);
			}
			delay(1000);
		}
		//
		if( datoRecibido == 's' ){		//El usuario elije armar una secuencia.
			*sec = ARMO_SECUENCIA;
		}
		else if( datoRecibido == 'f' ){	//El usuario elije una secuencia prefijada.
			*sec = SECUENCIA_FIJA;
		}
		else if( datoRecibido == 'p' ){ //El usuario elije volver al estado inicial.
			*sec = PARA;
			printf("\n");
		}
		else{		//El usuario ingresó un comando invalido
			printf("Dato ingresado invalido. Ingrese valor correcto\n");
			printf("\n");
		}
		break;
		//
	case ARMO_SECUENCIA: //estado ARMO_SECUENCIA
		printf("****************************** \n");
		printf("estado -> ARMO_SECUENCIA. \n");
		printf("\n");
		printf("Indicaciones antes de crear la secuencia: \n");
		printf("\n");
		printf("1 - Ingrese la secuencia con los letras r (rojo), b (Azul), v (verde), a (amarillo).\n");
		printf("2 - Al finalizar la carga de la secuencia, ingrese el caracter 'x' para indicarle al sistema que finalizo la secuencia creada. \n");
		printf("3 - Ingresando la letra 'p' vuelve al inicio.\n");
		printf("****************************** \n");
		//		while(!uartReadByte(UART_USB, &datoRecibido)){}	// ESPERA UN COMANDO
		creaSec(sentido);	//ejecuta la creación de una secuencia. No retorna de la función si el sistema no recibe un caracter 'p' por UART.
		*sec = PARA; 		//Retorna al inicio del sistema.
		break;
		//
	case SECUENCIA_FIJA: //estado SECUENCIA_FIJA
		printf("****************************** \n");
		printf("estado -> SECUENCIA_FIJA. \n");
		printf("\n");
		printf("Ingrese '1', '2' o '3' para elegir la secuencia. \n");
		printf("\n");

		while(!uartReadByte(UART_USB, &datoRecibido)){} //ESPERA UN COMANDO
		//
		if( datoRecibido == '1' ){
			msjSentidoSec();	//muestra información respecto al sentido de ejecución.
			printf("ejecutando secuencia 1...\n");
			haceSec1(sentido); //ejecuta secuencia Nº1. No retorna de la función si el sistema no recibe un caracter 'p' por UART.
			*sec = PARA;		//Retorna al inicio del sistema.
		}
		else if( datoRecibido == '2' ){
			msjSentidoSec();	//muestra información respecto al sentido de ejecución.
			printf("ejecutando secuencia 2...\n");
			printf(" \n");
			haceSec2(sentido);	//ejecuta secuencia Nº2. No retorna de la función si el sistema no recibe un caracter 'p' por UART.
			*sec = PARA;		//Retorna al inicio del sistema.
		}
		else if( datoRecibido == '3' ){
			msjSentidoSec();	//muestra información respecto al sentido de ejecución.
			printf("ejecutando secuencia 3...\n");
			printf(" \n");
			haceSec3(sentido);	//ejecuta secuencia Nº3. No retorna de la función si el sistema no recibe un caracter 'p' por UART.
			*sec = PARA;			//Retorna al inicio del sistema.
		}
		else{
			printf("ingresa comando invalido. vuelve al inicio \n");
			printf(" \n");
			*sec = PARA;		//Retorna al inicio del sistema.
		}
		break;
		//
	default:	//si la orden recibida por la UART no corresponde con ninguno de los estados restantes, setea el estado = PARA.
		sec = PARA;
		printf("Estado erroneo. Vuelva al estado inicial\r\n");
		printf(" \n");
		break;
	}
}
