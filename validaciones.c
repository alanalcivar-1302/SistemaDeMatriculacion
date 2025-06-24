#include "funciones.h"

#include <stdio.h>
#include <string.h>

void opcionesUsuario(int *opcionEscoger, int rangoOpciones){
	
	while ((*opcionEscoger < 0) || (*opcionEscoger > rangoOpciones	)){
		printf("Opcion no valida, ingrese nuevamente (1-%d)\n",rangoOpciones);
		scanf("%d",	opcionEscoger);
	}
};

//Nombre - Caracteres
int validacionCaracteres(char stringValidar[]){
	//int i = 0;
	for (int i = 0; stringValidar[i] != '\0'; i++){
		if ((isalpha(stringValidar[i]) != 0) || (stringValidar[i] = '\0')){
			return 0;
		}
	}
	return 1;
}

void validacionEntradaNombre(char *stringValidar){
	int resultado, intentos = 0;
	do
	{
		if (intentos == 0){
			intentos++;
		}
		else{
			if (intentos == 1){
				printf("Se ingresó información erronea\n");
			}
		}
		scanf("%s",stringValidar);
		resultado = validacionCaracteres(stringValidar);
	}while(resultado != 0);
	
}
	
//Validacion Cedula

void validacionNumerica(int *valor) {
	
	while (scanf("%d", valor) != 1) {
		clearInputBuffer();
		printf("Entrada inválida. Ingrese solo números: \n");
	}
	
}

void validacionCedula(int *cedulaValidar) {
	char cedulaStr[11];
	int intentos = 0;
	
	do {
		if (intentos > 0) {
			printf("Cédula incompleta, ingrese nuevamente: \n");
		}
		
		validacionNumerica(cedulaValidar); 
		sprintf(cedulaStr, "%d", *cedulaValidar); 
		intentos++;
		
	} while (strlen(cedulaStr) != 10);
}
	
//Validacion placa
int validarPlaca(char placa[]) {
	if (strlen(placa) != 8)
		return 0;
	
	for (int i = 0; i < 3; i++) {
		if (!isupper(placa[i])) 
			return 0;
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
		printf("Ingrese la placa (ej: ABC-1234): \n");
		fgets(placa, TAM_PLACA, stdin);
		placa[strcspn(placa, "\n")] = '\0';
		if (!validarPlaca(placa)) 
			printf("Placa invalida, intente de nuevo.\n");
	} while (!validarPlaca(placa));
}
	



