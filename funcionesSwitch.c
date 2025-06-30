#include "funciones.h"

#include <stdio.h>
#include <string.h>

void registroVehiculos(FILE *archivoDatos, int *continuarRegistros){
			
	archivoDatos = fopen("datosVehiculos.txt","a");

	if (archivoDatos == NULL) {
		printf("Error: El archivo no existe.\n");
		registrarLog("ERROR", "main", "No se pudo abrir el archivo datosVehiculos.txt.");
		fclose(archivoDatos);
	}
	else{
		clearInputBuffer();
		
		do {
			
			//ingresar datos del usuario
			printf("Ingrese el nombre del propietario\n");
			validacionEntradaNombre(&persona.nombrePropietario);
			
			limpiarTerminal();
	
			printf("Ingrese su numero de cedula \n");
			validacionCedula(&persona.numCedula);
	
			limpiarTerminal();
			
			printf("Ingrese el modelo del vehiculo\n");
			scanf("%s",&persona.modeloAuto);
			
			limpiarTerminal();
	
			clearInputBuffer();
			pedirPlaca(persona.placa);
	
			limpiarTerminal();
			
			printf("Ingresar el color del vehículo\n");
			scanf("%s",&persona.colorAuto);
	
			limpiarTerminal();
			
			printf("Ingresar año del vehículo\n");
			scanf("%d",&persona.anioAuto);
	
			limpiarTerminal();
			
			//Escribir los datos en el txt 
			fprintf(archivoDatos,"%s,%d,%s,%s,%s,%d\n",persona.nombrePropietario,persona.numCedula, persona.modeloAuto,persona.placa, persona.colorAuto, persona.anioAuto);
			
			fclose(archivoDatos);

			printf("Desea registrar otro vehiculo 1. Si, 2. No");
			opcionesUsuario(&continuarRegistros,2);

		}while(continuarRegistros == 2);
	}
		
}


void buscarVehiculo(const char *nombreArchivo, const char *datoBuscado) {
	FILE *archivo = fopen(nombreArchivo, "r");
	char lineasTxt[101];  
	int encontrado = 0;
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	while (fgets(lineasTxt, sizeof(lineasTxt), archivo)) {
		
		// Elimina el salto de línea final
		lineasTxt[strcspn(lineasTxt, "\n")] = '\0';
		
		// Si la línea contiene el dato buscado (placa, cédula, etc.)
		if (strstr(lineasTxt, datoBuscado) != NULL) {
			printf("Línea encontrada: %s\n", lineasTxt);
			
			// Separar por comas
			char *campo = strtok(lineasTxt, ",");
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
