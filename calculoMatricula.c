#include "funciones.h"

#include <stdio.h>
#include <string.h>

float calcularValormatricula(int pagoAtiempo, int hizoRevisionVehiculo, int diasPago, float multasVehiculo, int tipoVehiculo) {
	
	//Datos del recargo y descuentos
	float recargoRevision = 50.0; //D?lares
	float recargoMes = 25.0; //D?lares
	float descuentoProntopago = 0.5;  //Porcentaje de descuento (50%)
	float MatriculaporVehiculo; //Variable de subsecciones para el tipo de veh?culo.
	
	//Precio de matr?cula con respecto al tipo de veh?culo 
	switch (tipoVehiculo){
	case 1: 
		MatriculaporVehiculo = 100.0;  //Para auto
		break;
	case 2: 
		MatriculaporVehiculo = 150.0; //Para motocicleta
		break;
	case 3: 
		MatriculaporVehiculo = 250.0; //Para cami?n
		break;
	case 4: 
		MatriculaporVehiculo = 175.0; //Para Bus
		break;
	default:
		return 0;
	}
	
	// Se suman recargos
	if (hizoRevisionVehiculo == 2) {
		MatriculaporVehiculo += recargoRevision;
	}
	
	if (pagoAtiempo == 2) {
		MatriculaporVehiculo += recargoMes;
	}
	
	// Descuento solamente si d?as <= 20
	if (pagoAtiempo == 1 && diasPago <= 20) {
		MatriculaporVehiculo *= (1 - descuentoProntopago);   // Para 50% de descuento
	}
	
	// Total a pagar
	return MatriculaporVehiculo + multasVehiculo;
	
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
