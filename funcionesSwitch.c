#include "funciones.h"

#include <stdio.h>
#include <string.h>

void buscarYSepararPorComa(const char *nombreArchivo, const char *datoBuscado) {
	FILE *archivo = fopen(nombreArchivo, "r");
	char linea[101];  
	int encontrado = 0;
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	while (fgets(linea, sizeof(linea), archivo)) {
		
		// Elimina el salto de línea final
		linea[strcspn(linea, "\n")] = '\0';
		
		// Si la línea contiene el dato buscado (placa, cédula, etc.)
		if (strstr(linea, datoBuscado) != NULL) {
			printf("Línea encontrada: %s\n", linea);
			
			// Separar por comas
			char *campo = strtok(linea, ",");
			int i = 1;
			
			while (campo != NULL) {
				printf("Campo %d: %s\n", i, campo);
				campo = strtok(NULL, ",");
				i++;
			}
			
			encontrado = 1;
			break; 
		}
	}
	
	if (!encontrado) {
		printf("No se encontró ningún registro con '%s'\n", datoBuscado);
	}
	
	fclose(archivo);
}
