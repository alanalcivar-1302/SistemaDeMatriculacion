#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <stdbool.h>
#include "funciones.h"


#define ARCHIVO "fechasAsignadas.txt"
#define intervalosMax 18

#define MAX_LINEA 100
#define MAX_PLACAS 1000

void crearCarpetaComprobantes() {
#ifdef _WIN32
	_mkdir("comprobantes");
#else
	mkdir("comprobantes", 0777);
#endif
}


typedef struct {
	char placa[50];
	int conteo;
} Revision;

bool actualizarRevisiones(const char *placa) {
	Revision lista[MAX_PLACAS];
	int total = 0;
	bool placaEncontrada = false;
	
	FILE *archivo = fopen("revisiones.txt", "r");
	if (archivo != NULL) {
		char linea[MAX_LINEA];
		while (fgets(linea, sizeof(linea), archivo)) {
			char placaArchivo[50];
			int numRevisiones;
			if (sscanf(linea, "%[^,],%d", placaArchivo, &numRevisiones) == 2) {
				strcpy(lista[total].placa, placaArchivo);
				lista[total].conteo = numRevisiones;
				total++;
			}
		}
		fclose(archivo);
	}
	
	// Buscar la placa en la lista
	for (int i = 0; i < total; i++) {
		if (strcmp(lista[i].placa, placa) == 0) {
			placaEncontrada = true;
			if (lista[i].conteo >= 3) {
				// Ya tiene las 3 revisiones máximas
				return false;
			}
			lista[i].conteo++;  // Incrementar contador
			break;
		}
	}
	
	// Si no estaba en la lista, agregarla con 1
	if (!placaEncontrada) {
		if (total >= MAX_PLACAS) {
			printf("Error: límite máximo de placas alcanzado.\n");
			return false;
		}
		strcpy(lista[total].placa, placa);
		lista[total].conteo = 1;
		total++;
	}
	
	// Reescribir el archivo con todos los datos actualizados
	archivo = fopen("revisiones.txt", "w");
	if (archivo == NULL) {
		perror("Error al abrir revisiones.txt para escritura");
		return false;
	}
	
	for (int i = 0; i < total; i++) {
		fprintf(archivo, "%s,%d\n", lista[i].placa, lista[i].conteo);
	}
	
	fclose(archivo);
	return true;
}


char* obtenerNombreDueno(const char *placaBuscada) {
	FILE *archivo = fopen("datosVehiculos.txt", "r");
	if (archivo == NULL) {
		perror("No se pudo abrir el archivo");
		return NULL;
	}
	
	static char nombreDueno[100];
	char linea[256];
	
	while (fgets(linea, sizeof(linea), archivo)) {
		// Eliminar salto de línea
		linea[strcspn(linea, "\n")] = '\0';
		
		char *campos[10];  // Un arreglo suficientemente grande
		char *token = strtok(linea, ",");
		int i = 0;
		
		while (token != NULL && i < 10) {
			campos[i++] = token;
			token = strtok(NULL, ",");
		}
		
		// Validar que haya al menos 7 campos (según tu estructura)
		if (i >= 7 && strcmp(campos[3], placaBuscada) == 0) {
			strncpy(nombreDueno, campos[0], sizeof(nombreDueno) - 1);
			nombreDueno[sizeof(nombreDueno) - 1] = '\0'; // aseguramos null terminator
			fclose(archivo);
			return nombreDueno;
		}
	}
	
	fclose(archivo);
	return NULL;
}



void guardarComprobante(const char *nombreDueno, const char *placa, const char *fechaHora) {
	crearCarpetaComprobantes();  // Asegura que la carpeta exista
	
	char nombreArchivo[150];
	snprintf(nombreArchivo, sizeof(nombreArchivo), "comprobantes/%sComprobante.txt", nombreDueno);
	
	FILE *archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL) {
		perror("Error al crear el comprobante");
		return;
	}
	
	fprintf(archivo, "----- COMPROBANTE DE CITA -----\n");
	fprintf(archivo, "Nombre del propietario: %s\n", nombreDueno);
	fprintf(archivo, "Placa del vehículo: %s\n", placa);
	fprintf(archivo, "Fecha y hora asignadas: %s\n", fechaHora);
	
	fclose(archivo);
	printf("? Comprobante guardado en: %s\n", nombreArchivo);
}


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
void generarFechaYObtenerla(char *fechaHora) {
	time_t t = time(NULL);
	struct tm fecha = *localtime(&t);
	
	srand(time(NULL));
	
	fecha.tm_mday += 1;
	mktime(&fecha);
	
	int intentos;
	
	while (1) {
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
			
			snprintf(fechaHora, 100, "%04d-%02d-%02d %02d:%02d",
					 fecha.tm_year + 1900, fecha.tm_mon + 1, fecha.tm_mday,
					 hora, minuto);
			
			if (!existenciaFecha(fechaHora)) {
				guardarFecha(fechaHora);
				return;  // Ya no se imprime, solo se retorna la cadena en el parámetro
			}
		}
		
		fecha.tm_mday++;
		mktime(&fecha);
	}
}



void agendarCita() {
	char validacionPlaca[TAM_PLACA];
	int validacion;
	char fechaHora[100];
	
	clearInputBuffer();
	
	printf("Ingrese la placa del veh%cculo: \n",161);
	pedirPlaca(validacionPlaca);
	
	validacion = validacionVehiculo("datosVehiculos.txt", validacionPlaca);
	
	while (validacion == 0) {
		limpiarTerminal();
		printf("Veh%cculo no encontrado, ingrese la placa nuevamente:\n",161);
		pedirPlaca(validacionPlaca);
		validacion = validacionVehiculo("datosVehiculos.txt", validacionPlaca);
	}
	
	if (!actualizarRevisiones(validacionPlaca)) {
		printf("El veh%cculo con placa %s ya tiene las 3 revisiones m%cximas permitidas.\n",161, validacionPlaca,160);
		system("pause");
		return;
	}
	
	limpiarTerminal();
	printf("Se realiz%c exitosamente el agendamiento de cita.\n",162);
	printf("\n----- COMPROBANTE DE CITA -----\n");
	buscarVehiculo("datosVehiculos.txt", validacionPlaca);
	
	printf("\nSe le asignar%c una fecha, espere...\n",160);
	generarFechaYObtenerla(fechaHora);
	printf("Fecha y Hora asignadas: %s\n", fechaHora);
	
	char *nombreDueno = obtenerNombreDueno(validacionPlaca);
	if (nombreDueno != NULL) {
		guardarComprobante(nombreDueno, validacionPlaca, fechaHora);
	}
	
	system("pause");
}
