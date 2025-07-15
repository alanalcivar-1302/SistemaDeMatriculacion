#include "funciones.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void registroVehiculos(FILE *archivoDatos, int *continuarRegistros){
	
	srand(time(NULL));
	
	int numeroRandom = 0;
	datosUsuario persona;
	
	archivoDatos = fopen("datosVehiculos.txt","a");
	
	if (archivoDatos == NULL) {
		printf("Error: El archivo no existe.\n");
		registrarLog("ERROR", "main", "No se pudo abrir el archivo datosVehiculos.txt.");
	}
	else{
		clearInputBuffer();
			
		do {
			
			//ingresar datos del usuario
			printf("Ingrese el nombre del propietario\n");
			validacionEntradaNombre(persona.nombrePropietario,sizeof(persona.nombrePropietario));
			
			limpiarTerminal();
			
			printf("Ingrese su numero de cedula \n");
			validacionCedula(persona.numCedula); //Cambio del &
			
			limpiarTerminal();
			
			printf("Ingrese el modelo del vehiculo (ej: MazdaRx)\n");
			scanf("%s",persona.modeloAuto);
			
			limpiarTerminal();
			
			clearInputBuffer();
			printf("Ingrese la placa (ej: ABC-1234): \n");
			pedirPlaca(persona.placa);
			
			limpiarTerminal();
			
			printf("Ingresar el color del vehículo\n");
			scanf("%s",persona.colorAuto);
			
			limpiarTerminal();
			
			printf("Ingresar año del vehículo\n");
			validacionNumerica(&persona.anioAuto);
			while((persona.anioAuto < 1990) || (persona.anioAuto > 2025)){
				printf("Ingresó un año incorrecto, intente nuevamente\n");
				validacionNumerica(&persona.anioAuto);
			}
			
			numeroRandom = (rand() % 5);
			if (numeroRandom == 0){
				persona.multaVehiculo = 0;
			}
			else{
				persona.multaVehiculo = (rand() % 501);
			}
			
			limpiarTerminal();
			
			//Escribir los datos en el txt 
			fprintf(archivoDatos,"%s,%s,%s,%s,%s,%d,%d\n",persona.nombrePropietario,persona.numCedula,persona.modeloAuto,persona.placa, persona.colorAuto, persona.anioAuto,persona.multaVehiculo);
			
			printf("Se ha registrado correctamente el vehículo\n");
			printf("Nombre: %s\n",persona.nombrePropietario);
			printf("Cedula: %s\n",persona.numCedula);
			printf("Modelo: %s\n",persona.modeloAuto);
			printf("Placa: %s\n",persona.placa);
			printf("Color: %s\n",persona.colorAuto);
			printf("Año vehiculo: %d\n",persona.anioAuto);
			
			system("pause");
			limpiarTerminal();
			
			printf("Desea registrar otro vehiculo 1. Si, 2. No\n");
			opcionesUsuario(continuarRegistros,2);
			
		}while(*continuarRegistros == 1);
	}
	fclose(archivoDatos);
	
}
	

void buscarVehiculo(const char *nombreArchivo, const char *datoBuscado) {
	FILE *archivo = fopen(nombreArchivo, "r");
	char lineasTxt[201];  
	int encontrado = 0;
	char *etiquetas[7] = {
		"Nombre",
		"Cedula",
		"Modelo",
		"Placa",
		"Color",
		"Año vehiculo",
		"Valor de Multas"
	};
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	while (fgets(lineasTxt, sizeof(lineasTxt), archivo)) {
		
		// Elimina el salto de línea final
		lineasTxt[strcspn(lineasTxt, "\n")] = '\0';
		
		// Si la línea contiene el dato buscado (placa, cédula, etc.)
		if (strstr(lineasTxt, datoBuscado) != NULL) {
			// Separar por comas
			char *campo = strtok(lineasTxt, ",");
			int i = 1;
			
			while (campo != NULL) {
				printf("%s: %s\n",etiquetas[i - 1], campo);
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

void valorPago(){
	int nuevoPagomatricula = 1;
	
	while (nuevoPagomatricula) {
		int pagoAtiempo, hizoRevisionVehiculo, diasPago, tipoVehiculo ;
		float multasVehiculo, totalpagoMatricula;
		char placa[TAM_PLACA];
		
		printf("Seleccione su tipo de vehículo: \n");
		printf(" 1. Automóvil \n 2. Motocicleta \n 3. Camión \n 4. Bus \n");
		opcionesUsuario(&tipoVehiculo,4);
		
		limpiarTerminal();
		
		printf("¿Realizó la revisión técnica? 1. Si, 2. No \n");
		opcionesUsuario(&hizoRevisionVehiculo,2);
		
		limpiarTerminal();
		
		printf("¿Pagó la matrícula a tiempo? 1. Si, 2. No \n");
		opcionesUsuario(&pagoAtiempo,2);
		
		limpiarTerminal();
		
		printf("¿Cuántos días han pasado desde la notificación?: \n");
		scanf("%d", &diasPago);
		
		limpiarTerminal();
		
		printf("Ingrese placa del vehiculo a matricular (ej: ABC-1234)\n");
		clearInputBuffer();
		pedirPlaca(placa);
		limpiarTerminal();
		
		multasVehiculo = buscarMulta("datosVehiculos.txt",placa);
		
		if (multasVehiculo == -1){
			printf("Error, el vehiculo no se encuentra en el sistema\n");
		}
		else{
			//Total a pagar de la matrícula
			
			totalpagoMatricula = calcularValormatricula(pagoAtiempo, hizoRevisionVehiculo, diasPago, multasVehiculo, tipoVehiculo) ;
			
			if (totalpagoMatricula >= 0) {
				printf("\n--------------- COMPROBANTE DE MATRICULA ---------------\n");
				printf("Recuerde guardar el comprobante. \n");
				printf("Multas: $%.2f\n", multasVehiculo);
				printf("Total a pagar: $%.2f\n", totalpagoMatricula);
				printf("----------------------------------------------------------\n");
			}
		}
		
		system("pause");
		limpiarTerminal();
		
		// Desea revisar nuevo pago?
		
		printf("\n¿Desea procesar otro pago de matrícula? 1. Si, 2. No \n");
		scanf("%d", &nuevoPagomatricula);
	}
	
	printf("Gracias por preferir nuestro sistema. Regrese mas tarde.\n");
	
}
