#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funciones.h"
#define ARCHIVO "fechasAsignadas.txt"
#define intervalosMax 18

int validacionVehiculo(const char *nombreArchivo, const char *datoBuscado) {
	FILE *archivo = fopen("datosVehiculos.txt", "r");
	char lineasTxt[201];  
	int encontrado = 0;
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return 0; // Retornar 0 si no se puede abrir el archivo
	}
	
	while (fgets(lineasTxt, sizeof(lineasTxt), archivo)) {
		// Elimina el salto de línea final
		lineasTxt[strcspn(lineasTxt, "\n")] = '\0';
		
		// Separar por comas
		char *campo = strtok(lineasTxt, ",");
		int contador = 0;
		
		// Avanzar hasta el cuarto campo
		while (campo != NULL && contador < 3) { // Contador empieza en 0, así que para el cuarto campo debe ser 3
			campo = strtok(NULL, ",");
			contador++;
		}
		
		// Verificar si se encontró el cuarto campo y compararlo con el dato buscado
		if (campo != NULL && strcmp(campo, datoBuscado) == 0) {
			encontrado = 1;
			break; 
		}
	}
	
	fclose(archivo);
	
	return encontrado; // Retornar 1 si se encontró, 0 si no
}

// Función para verificar si una fecha-hora ya está en el archivo
int existenciaFecha(const char *fechaHora) {
	FILE *archivo = fopen(ARCHIVO, "r");
	if (archivo == NULL) return 0;
	
	char linea[100];
	while (fgets(linea, sizeof(linea), archivo)) {
		if (strncmp(linea, fechaHora, strlen(fechaHora)) == 0) {
			fclose(archivo);
			return 1;
		}
	}
	fclose(archivo);
	return 0;
}

// Guardar la fecha-hora en el archivo
void guardarFecha(const char *fechaHora) {
	FILE *archivo = fopen(ARCHIVO, "a");
	if (archivo == NULL) {
		perror("No se pudo abrir el archivo");
		return;
	}
	fprintf(archivo, "%s\n", fechaHora);
	fclose(archivo);
}

// Generar fecha única con hora libre en el mismo día
char* generarFecha() {
	time_t t = time(NULL);
	struct tm fecha = *localtime(&t);
	
	// Inicializar la semilla
	srand(time(NULL));
	
	fecha.tm_mday += 1;
	mktime(&fecha);
	
	char fechaHora[100];
	int intentos;
	
	while (1) {
		// Array para controlar qué intervalos ya se intentaron (0 = no usado)
		int usados[intervalosMax] = {0};

		intentos = 0;
		
		while (intentos < intervalosMax) {
			int intervalo;
			do {
				intervalo = rand() % intervalosMax;
			} while (usados[intervalo]);
			
			usados[intervalo] = 1;
			intentos++;
			
			int hora = 9 + (intervalo / 2);
			int minuto = (intervalo % 2) * 30;
			
			snprintf(fechaHora, sizeof(fechaHora), "%04d-%02d-%02d %02d:%02d",
					 fecha.tm_year + 1900, fecha.tm_mon + 1, fecha.tm_mday,
					 hora, minuto);
			
			if (!existenciaFecha(fechaHora)) {
				guardarFecha(fechaHora);
				return printf("Fecha y Hora asignadas: %s\n",fechaHora);
			}
			
		}
		
		// Si todas las horas ya están usadas, pasar al siguiente día
		fecha.tm_mday++;
		mktime(&fecha);
	}
}

void agendarCita() {

	char validacionPlaca[TAM_PLACA]; 
	int validacion;
	
	clearInputBuffer();
	
	printf("Ingrese la placa del vehiculo: \n");
	scanf("%s", validacionPlaca);
	/*printf("%s",validacionPlaca);*/
	pedirPlaca(validacionPlaca);

	
	validacion = validacionVehiculo("datosVhiculos.txt", validacionPlaca); 
	
	while (validacion == 0) {
		limpiarTerminal();
		printf("Vehiculo no encontrado, Ingrese la placa del vehiculo nuevamente: \n");
		
		pedirPlaca(validacionPlaca);
		validacion = validacionVehiculo("datosVhiculos.txt", validacionPlaca); 
		
	}

	if (validacion == 1) {
		limpiarTerminal();
		printf("Se realizo exitosamente el agendamiento de cita.\n");
		printf("\n----- COMPROBANTE DE CITA -----\n");
		buscarVehiculo("datosVehiculos.txt",validacionPlaca);
		printf("\nSe le asignara una fecha espere....\n");
		generarFecha();
		system ("pause");

	} 
}
