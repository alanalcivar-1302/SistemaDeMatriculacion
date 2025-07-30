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
			printf("Nombre inv%clido. Solo letras y espacios. Intente de nuevo:\n",160);
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
			printf("C%cdula inv%clida. Debe tener 10 d%cgitos num%cricos.\n",130,160,161,130);
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
			printf("A%co inv%clido. Debe estar entre 1990 y 2025.\n",164,160);
		}
	}
}


void opcionesUsuario(int *opcionEscoger, int rangoOpciones){
	
	int resultado;
	resultado = scanf("%d",opcionEscoger);
	
	while (resultado != 1){
		printf("Error, se ha ingresado informaci%cn err%cnea\n",162,162);
		clearInputBuffer();
		resultado = (scanf("%d",opcionEscoger));
	}
	while ((*opcionEscoger < 0) || (*opcionEscoger > rangoOpciones)){
		printf("Opci%cn no v%clida, ingrese nuevamente (1-%d)\n",162,160,rangoOpciones);
		scanf("%d",	opcionEscoger);
	}
};

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
			printf("Placa inv%clida, intente de nuevo.\n",160);
	} while (!validarPlaca(placa));
}
