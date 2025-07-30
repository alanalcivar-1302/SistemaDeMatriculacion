#include "funciones.h"

#include <stdio.h>
#include <string.h>

int calcularValormatricula(int multasVehiculo, int tipoVehiculo) {
	
	int matriculaporVehiculo; //Variable de subsecciones para el tipo de veh?culo.
	
	//Precio de matr?cula con respecto al tipo de veh?culo 
	switch (tipoVehiculo){
	case 1: 
		matriculaporVehiculo = 100;  //Para auto
		break;
	case 2: 
		matriculaporVehiculo = 150; //Para motocicleta
		break;
	case 3: 
		matriculaporVehiculo = 250; //Para cami?n
		break;
	case 4: 
		matriculaporVehiculo = 175; //Para Bus
		break;
	default:
		return 0;
	}
	
	// Total a pagar
	return matriculaporVehiculo + multasVehiculo;
	
}

int buscarMulta(const char *nombreArchivo, const char *placaBuscada) {
	FILE *archivo = fopen(nombreArchivo, "r");
	char linea[201];
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return -1;  // Valor especial para indicar error
	}
	
	while (fgets(linea, sizeof(linea), archivo)) {
		// Elimina el salto de lÃ­nea final
		linea[strcspn(linea, "\n")] = '\0';
		
		// Verifica si la lÃ­nea contiene la placa buscada
		if (strstr(linea, placaBuscada) != NULL) {
			char *campo = strtok(linea, ",");
			int i = 1;
			
			while (campo != NULL) {
				if (i == 7) {  
					int multa = atoi(campo);
					fclose(archivo);
					return multa;
				}
				campo = strtok(NULL, ",");
				i++;
			}
		}
	}
	
	fclose(archivo);
	printf("No se encontrc% ninguna multa con la placa '%s'\n",162,placaBuscada);
	return -1;
}

int obtenerTipoVehiculo(const char *nombreArchivo, const char *placaBuscada) {
	FILE *archivo = fopen(nombreArchivo, "r");
	char linea[201];
	
	if (archivo == NULL) {
		printf("Error: no se pudo abrir el archivo.\n");
		return -1; // Código de error
	}
	
	while (fgets(linea, sizeof(linea), archivo)) {
		linea[strcspn(linea, "\n")] = '\0';  // Eliminar salto de línea
		char lineaCopia[201];
		strcpy(lineaCopia, linea);
		
		// Verificamos si la línea contiene la placa
		if (strstr(linea, placaBuscada) != NULL) {
			char *campo = strtok(lineaCopia, ",");
			int campoIndex = 1;
			
			int tipoNum = -1;
			while (campo != NULL) {
				if (campoIndex == 8) {  
					tipoNum = *campo - '0';
					break;
				}
				campo = strtok(NULL, ",");
				campoIndex++;
			}
			
			fclose(archivo);
			
			if (tipoNum >= 0 && tipoNum <= 3)
				return tipoNum;
			else
				return -1; // Tipo inválido
		}
	}
	
	fclose(archivo);
	return -1; // No se encontró la placa
}

int extraerRevisiones(const char *placaBuscada) {
	FILE *archivo = fopen("revisiones.txt", "r");
	char linea[201];
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return -1;
	}
	
	while (fgets(linea, sizeof(linea), archivo)) {
		linea[strcspn(linea, "\n")] = '\0';
		
		// Separar los campos por coma
		char *placa = strtok(linea, ",");
		char *revStr = strtok(NULL, ",");
		
		if (placa && revStr && strcmp(placa, placaBuscada) == 0) {
			int revisiones = atoi(revStr);
			fclose(archivo);
			return revisiones;
		}
	}
	
	fclose(archivo);
	return -1;
}
