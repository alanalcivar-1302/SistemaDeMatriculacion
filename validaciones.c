#include "funciones.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void registrarLog(const char *nivel, const char *funcion, const char *mensaje) {
	FILE *log = fopen("log_programa.txt", "a");
	
	if (log == NULL) {
		printf("No se pudo abrir el archivo de log.\n");
		return;
	}
	
	time_t tiempoActual = time(NULL);
	char *tiempoTexto = ctime(&tiempoActual);
	
	// Eliminar salto de línea
	for (int i = 0; tiempoTexto[i] != '\0'; i++) {
		if (tiempoTexto[i] == '\n') {
			tiempoTexto[i] = '\0';
			break;
		}
	}
	
	fprintf(log, "[%s] [%s] [%s] %s\n", tiempoTexto, nivel, funcion, mensaje);
	fclose(log);
}

void opcionesUsuario(int *opcionEscoger, int rangoOpciones){
	
	scanf("%d",opcionEscoger);
	while ((*opcionEscoger < 0) || (*opcionEscoger > rangoOpciones)){
		printf("Opcion no valida, ingrese nuevamente (1-%d)\n",rangoOpciones);
		scanf("%d",	opcionEscoger);
	}
};

//Nombre - Caracteres
int validacionCaracteres(char stringValidar[]){
	for (int i = 0; stringValidar[i] != '\0'; i++){
		if (!isalpha(stringValidar[i]) || (stringValidar[i] == '\0')){
			return 0;
		}
	}
	return 1;
}

void validacionEntradaNombre(char *stringValidar){
	int resultado, intentos = 0;
	do
	{
		if (intentos == 0){
			intentos++;
		}
		else{
			if (intentos == 1){
				printf("Se ingresó información erronea\n");
			}
		}
		scanf("%s",stringValidar);
		resultado = validacionCaracteres(stringValidar);
	}while(resultado != 1);
	
}
			
//Validacion Cedula

void validacionNumerica(int *valor) {
	
	while (scanf("%d", valor) != 1) {
		clearInputBuffer();
		printf("Entrada inválida. Ingrese solo números: \n");
	}
	
}


void validacionCedula(char *cedulaValidar){
	int longitud = 0, condiciones = 0;
	
	do {
		condiciones = 0;
		
		scanf("%s",cedulaValidar);
		limpiarTerminal();
		
		for (int i = 0; cedulaValidar[i] != '\0'; i++){
			if (!isdigit(cedulaValidar[i])){
				condiciones = 2;
				break;
			}
			else{
				if(i == 9){
					longitud = strlen(cedulaValidar);
					if (longitud == 10){
						condiciones = 1;
					}
				}
			}
		}
		
		if (condiciones == 0)
			printf("Cédula incompleta ingrese nuevamente\n");
		
		if(condiciones == 2)
			printf("Se ingresó información erronea, ingrese nuevamente su cédula\n");
		
	} while ((condiciones == 0) || (condiciones == 2));
}


//Validacion placa
int validarPlaca(char placa[]) {
	if (strlen(placa) != 8)
		return 0;
	
	for (int i = 0; i < 3; i++) {
		if (!isalpha(placa[i])){
			return 0;
		}
		placa[i] = toupper(placa[i]);
	}
	
	if (placa[3] != '-') 
		return 0;
	
	for (int i = 4; i < 8; i++) {
		if (!isdigit(placa[i])) 
			return 0;
	}
	return 1;
}

void pedirPlaca(char placa[]) {
	do {
		fgets(placa, TAM_PLACA, stdin);
		placa[strcspn(placa, "\n")] = '\0';
		if (!validarPlaca(placa)) 
			printf("Placa invalida, intente de nuevo.\n");
	} while (!validarPlaca(placa));
}
