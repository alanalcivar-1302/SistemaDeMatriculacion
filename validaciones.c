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
	
	// Eliminar salto de lÃ­nea
	for (int i = 0; tiempoTexto[i] != '\0'; i++) {
		if (tiempoTexto[i] == '\n') {
			tiempoTexto[i] = '\0';
			break;
		}
	}
	
	fprintf(log, "[%s] [%s] [%s] %s\n", tiempoTexto, nivel, funcion, mensaje);
	fclose(log);
}

void validacionEntradaNombre(char *destino, int tam) {
	int valido = 0;
	while (!valido) {
		fgets(destino, tam, stdin);
		destino[strcspn(destino, "\n")] = '\0';  // Elimina el salto de línea
		
		valido = 1;
		for (int i = 0; destino[i] != '\0'; i++) {
			if (!isalpha(destino[i]) && destino[i] != ' ') {
				valido = 0;
				break;
			}
		}
		
		if (!valido) {
			printf("Nombre inválido. Solo letras y espacios. Intente de nuevo:\n");
		}
	}
}

void validacionCedula(char *cedula, int tam) {
	int valido = 0;
	while (!valido) {
		fgets(cedula, tam, stdin);
		cedula[strcspn(cedula, "\n")] = '\0';
		
		int len = strlen(cedula);
		valido = (len == 10);
		for (int i = 0; i < len && valido; i++) {
			if (!isdigit(cedula[i])) {
				valido = 0;
			}
		}
		if (!valido)
			printf("Cédula inválida. Debe tener 10 dígitos numéricos.\n");
	}
}

void validacionAnio(int *anio) {
	char buffer[10];
	int valido = 0;
	while (!valido) {
		fgets(buffer, sizeof(buffer), stdin);
		if (sscanf(buffer, "%d", anio) == 1 && *anio >= 1990 && *anio <= 2025) {
			valido = 1;
		} else {
			printf("Año inválido. Debe estar entre 1990 y 2025.\n");
		}
	}
}

/*
void opcionesUsuario(int *opcionEscoger, int rangoOpciones) {
	char linea[10];  // pequeño, suficiente para leer un número
	
	while (1) {
		printf("Ingrese una opción (0-%d): ", rangoOpciones);
		fgets(linea, sizeof(linea), stdin);  // lee la línea
		
		if (sscanf(linea, "%d", opcionEscoger) != 1) {
			printf("Se ha ingresado información errónea, intente nuevamente.\n");
			continue;
		}
		
		if (*opcionEscoger < 0 || *opcionEscoger > rangoOpciones) {
			printf("Opción no válida, intente nuevamente (0-%d).\n", rangoOpciones);
			continue;
		}
		
		break;  // entrada válida
	}
}*/

void opcionesUsuario(int *opcionEscoger, int rangoOpciones){
	
	int resultado;
	resultado = scanf("%d",opcionEscoger);
	
	while (resultado != 1){
		printf("Error, se ha ingresado informacion erronea\n");
		clearInputBuffer();
		resultado = (scanf("%d",opcionEscoger));
	}
	while ((*opcionEscoger < 0) || (*opcionEscoger > rangoOpciones)){
		printf("Opcion no valida, ingrese nuevamente (1-%d)\n",rangoOpciones);
		scanf("%d",	opcionEscoger);
	}
};

/*
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
				printf("Se ingresÃ³ informaciÃ³n erronea\n");
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
		printf("Entrada invÃ¡lida. Ingrese solo nÃºmeros: \n");
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
			printf("CÃ©dula incompleta ingrese nuevamente\n");
		
		if(condiciones == 2)
			printf("Se ingresÃ³ informaciÃ³n erronea, ingrese nuevamente su cÃ©dula\n");
		
	} while ((condiciones == 0) || (condiciones == 2));
}

*/

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
