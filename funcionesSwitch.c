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
		
		limpiarTerminal();
		printf("Seleccione su tipo de veh%cculo: \n",161);
		printf(" 1. Autom%cvil \n 2. Motocicleta \n 3. Cami%cn \n 4. Bus \n",162,162);
		opcionesUsuario(&persona.tipoVehiculo, 4);
		
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
			
			fprintf(archivoDatos, "%s,%s,%s,%s,%s,%d,%d,%d\n",persona.nombrePropietario, persona.numCedula,persona.modeloAuto, persona.placa,persona.colorAuto, persona.anioAuto,persona.multaVehiculo,persona.tipoVehiculo);
			
			fclose(archivoDatos);
			
			printf("Veh%cculo registrado correctamente.\n",161);
			printf("Nombre: %s\n", persona.nombrePropietario);
			printf("C%cdula: %s\n",130,persona.numCedula);
			printf("Modelo: %s\n", persona.modeloAuto);
			printf("Placa: %s\n", persona.placa);
			printf("Color: %s\n", persona.colorAuto);
			printf("A%co veh%cculo: %d\n",164,161,persona.anioAuto);
			printf("Tipo veh%cculo: %d\n",161,persona.tipoVehiculo);
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
	char *etiquetas[8] = {
		"Nombre",
			"Cédula",
			"Modelo",
			"Placa",
			"Color",
			"Anio vehiculo",
			"Valor de Multas",
			"Tipo de vehiculo"
	};
	
	char *etiquetaTipo[4] = {
			"Automovil",
			"Motocicleta",
			"Camion",
			"Bus"
	};
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	while (fgets(lineasTxt, sizeof(lineasTxt), archivo)) {
		lineasTxt[strcspn(lineasTxt, "\n")] = '\0';
		
		if (strstr(lineasTxt, datoBuscado) != NULL) {
			char *campo = strtok(lineasTxt, ",");
			int i = 1;
			
			while (campo != NULL && i <= 8) {
				if (i == 8) {
					int aux = *campo - '0';
					if (aux >= 0 && aux <= 3)
						printf("%s: %s\n", etiquetas[i - 1], etiquetaTipo[aux - 1]);
					else
						printf("%s: Desconocido (%s)\n", etiquetas[i - 1], campo);
				} else {
					printf("%s: %s\n", etiquetas[i - 1], campo);
				}
				
				campo = strtok(NULL, ",");
				i++;
			}
			
			encontrado = 1;
			break;
		}
	}
	
	if (!encontrado) {
		printf("No se encontr%c ning%cn registro con '%s'\n", 162, 163, datoBuscado); 
	}
	
	fclose(archivo);
}

void valorPago(){
	int nuevoPagomatricula = 0;
	
	while (nuevoPagomatricula != 2) {
		int revision, tipoVehiculo, multasVehiculo, totalpagoMatricula;
		char placa[TAM_PLACA];
		
		printf("Ingrese placa del vehiculo a matricular (ej: ABC-1234)\n");
		clearInputBuffer();
		pedirPlaca(placa);
		limpiarTerminal();
		
		revision = extraerRevisiones(placa);
		
		if(revision == 3){
			tipoVehiculo = obtenerTipoVehiculo("datosVehiculos.txt", placa);
			
			multasVehiculo = buscarMulta("datosVehiculos.txt",placa);
			
			totalpagoMatricula = calcularValormatricula(multasVehiculo, tipoVehiculo);
			
			printf("\n--------------- COMPROBANTE DE MATRICULA ---------------\n");
			printf("Recuerde guardar el comprobante. \n");
			printf("Multas: $%d\n", multasVehiculo);
			printf("Total a pagar: $%d\n", totalpagoMatricula);
			printf("----------------------------------------------------------\n");
			
			
		}
		if(revision == -1)
			printf("El auto con la placa %s no esta en nuestros registros\n",placa);
		
		if((revision < 3) && (revision > 0))
			printf("Debe realizar las 3 revisiones\n");
		
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
