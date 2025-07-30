#include "funciones.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void registroVehiculos(FILE *archivoDatos, int *continuarRegistros) {
	srand(time(NULL));
	char lineaTxt[201];
	int numeroRandom = 0, encontrado = 0;
	datosUsuario persona;
	
	do {
		limpiarTerminal();
		clearInputBuffer();
		encontrado = 0;
		printf("-----Registro de veh%cculos-----\n",161);
		
		printf("Ingrese el nombre del propietario:\n");
		validacionEntradaNombre(persona.nombrePropietario, TAM_NOMBRE);
		
		limpiarTerminal();
		printf("Ingrese su n%cmero de c%cdula:\n",163,130);
		validacionCedula(persona.numCedula, TAM_CEDULA);
		
		limpiarTerminal();
		
		printf("Ingrese el modelo del veh%cculo (ej: MazdaRX):\n",161);
		fgets(persona.modeloAuto, TAM_MODELO, stdin);
		persona.modeloAuto[strcspn(persona.modeloAuto, "\n")] = '\0';
		
		limpiarTerminal();
		printf("Ingrese la placa (ej: ABC-1234):\n");
		pedirPlaca(persona.placa);
		
		limpiarTerminal();
		printf("Ingrese el color del veh%cculo:\n",161);
		fgets(persona.colorAuto, TAM_COLOR, stdin);
		persona.colorAuto[strcspn(persona.colorAuto, "\n")] = '\0';
		
		limpiarTerminal();
		printf("Ingrese el a%co del veh%cculo:\n",164,161);
		validacionAnio(&persona.anioAuto);
		
		numeroRandom = (rand() % 5);
		persona.multaVehiculo = (numeroRandom == 0) ? 0 : (rand() % 501);
		
		// Abrimos aquí para leer cada vez que se registra un nuevo vehículo
		archivoDatos = fopen("datosVehiculos.txt", "r");
		if (archivoDatos != NULL) {
			while (fgets(lineaTxt, sizeof(lineaTxt), archivoDatos)) {
				lineaTxt[strcspn(lineaTxt, "\n")] = '\0';
				
				char *token;
				int campoIndex = 0;
				char placaArchivo[50] = "";
				
				token = strtok(lineaTxt, ",");
				while (token != NULL) {
					campoIndex++;
					if (campoIndex == 4) {
						strcpy(placaArchivo, token);
						break;
					}
					token = strtok(NULL, ",");
				}
				
				if (strcmp(placaArchivo, persona.placa) == 0) {
					encontrado = 1;
					break;
				}
			}
		}
		
		fclose(archivoDatos);
		
		if (!encontrado) {
			archivoDatos = fopen("datosVehiculos.txt", "a");
			if (archivoDatos == NULL) {
				printf("Error: No se pudo abrir el archivo para escritura.\n");
				registrarLog("ERROR", "registroVehiculos", "No se pudo abrir el archivo en modo 'a'");
				return;
			}
			
			fprintf(archivoDatos, "%s,%s,%s,%s,%s,%d,%d\n",persona.nombrePropietario, persona.numCedula,persona.modeloAuto, persona.placa,persona.colorAuto, persona.anioAuto,persona.multaVehiculo);
			
			fclose(archivoDatos);
			
			printf("Veh%cculo registrado correctamente.\n",161);
			printf("Nombre: %s\n", persona.nombrePropietario);
			printf("C%cdula: %s\n",130,persona.numCedula);
			printf("Modelo: %s\n", persona.modeloAuto);
			printf("Placa: %s\n", persona.placa);
			printf("Color: %s\n", persona.colorAuto);
			printf("A%co veh%cculo: %d\n",164,161,persona.anioAuto);
		} else {
			printf("La placa %s ya se encuentra registrada\n", persona.placa);
		}
		
		system("pause");
		limpiarTerminal();
		
		printf("Desea registrar otro veh%cculo? 1. Si, 2. No\n",161);
		opcionesUsuario(continuarRegistros, 2);
		
	} while (*continuarRegistros == 1);
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
		"Anio vehiculo",
		"Valor de Multas"
	};
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	while (fgets(lineasTxt, sizeof(lineasTxt), archivo)) {
		
		// Elimina el salto de linea final
		lineasTxt[strcspn(lineasTxt, "\n")] = '\0';
		
		// Si la linea contiene el dato buscado (placa, cedula, etc.)
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
		printf("No se encontr%c ning%cn registro con '%s'\n",162,163,datoBuscado);
	}
	
	fclose(archivo);
}

void valorPago(){
	int nuevoPagomatricula = 1;
	
	while (nuevoPagomatricula != 2) {
		int pagoAtiempo, hizoRevisionVehiculo, diasPago, tipoVehiculo ;
		float multasVehiculo, totalpagoMatricula;
		char placa[TAM_PLACA];
		
		printf("Seleccione su tipo de veh%cculo: \n",161);
		printf(" 1. AutomÃ³vil \n 2. Motocicleta \n 3. CamiÃ³n \n 4. Bus \n");
		opcionesUsuario(&tipoVehiculo,4);
		
		limpiarTerminal();
		
		printf("Â¿RealizÃ³ la revisiÃ³n tÃ©cnica? 1. Si, 2. No \n");
		opcionesUsuario(&hizoRevisionVehiculo,2);
		
		limpiarTerminal();
		
		printf("Â¿PagÃ³ la matrÃ­cula a tiempo? 1. Si, 2. No \n");
		opcionesUsuario(&pagoAtiempo,2);
		
		limpiarTerminal();
		
		printf("Â¿CuÃ¡ntos dÃ­as han pasado desde la notificaciÃ³n?: \n");
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
			//Total a pagar de la matrÃ­cula
			
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
		
		printf("\nDesea procesar otro pago de matr%ccula? 1. Si, 2. No \n",161);
		scanf("%d", &nuevoPagomatricula);
	}
	
	printf("Gracias por preferir nuestro sistema. Regrese mas tarde.\n");
	
}

void listarVehiculos() {
	FILE *archivo = fopen("datosVehiculos.txt", "r");
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo de vehiculos.\n");
		return;
	}
	
	char linea[256];
	int contador = 0;
	
	printf("=== Lista de vehiculos Registrados ===\n");
	
	while (fgets(linea, sizeof(linea), archivo)) {
		// Eliminar salto de lï¿½nea si existe
		linea[strcspn(linea, "\n")] = '\0';
		
		// Separar campos
		char *nombre = strtok(linea, ",");
		char *cedula = strtok(NULL, ",");
		char *modelo = strtok(NULL, ",");
		char *placa = strtok(NULL, ",");
		char *color = strtok(NULL, ",");
		char *anioStr = strtok(NULL, ",");
		char *multaStr = strtok(NULL, ",");
		
		// Verificar que todos los campos existen
		if (nombre && cedula && modelo && placa && color && anioStr && multaStr) {
			int anio = atoi(anioStr);
			float multa = atof(multaStr);
			
			printf("Registro #%d:\n", ++contador);
			printf("  Nombre : %s\n", nombre);
			printf("  C%cdula : %s\n",130, cedula);
			printf("  Modelo : %s\n", modelo);
			printf("  Placa  : %s\n", placa);
			printf("  Color  : %s\n", color);
			printf("  A%co    : %d\n",164, anio);
			printf("  Multa  : $%.2f\n", multa);
			printf("-----------------------------\n");
		}
	}
	
	if (contador == 0) {
		printf("No hay veh%cculos registrados validos.\n",161);
	}
	
	system("pause");
	
	fclose(archivo);
}
