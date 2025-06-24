#include "funciones.h"

#include <stdio.h>


//Tamaño de carácteres en arreglos
#define TAM_CEDULA 15
#define TAM_NOMBRE 100
#define TAM_PLACA 10


void menu(){
	printf("1. Registrar vehículo \n");
	printf("2. Buscar vehículo por placa \n");
	printf("3. Consultar valor a pagar por matricula\n");
	printf("4. Agendar cita de revisión\n");
	printf("5. Salir\n");
};
	
	
int continuar(){
	int opcionUsuario;
	printf("¿Desea realizar algo más? (1. Si/2. No)\n");
	scanf("%d",&opcionUsuario);
	
	//Validacion de la respuesta del usuario
	while (opcionUsuario != 2 && opcionUsuario != 1){
		printf("Opción no valida ingrese (1. Si/2. No) \n");
		scanf("%d",&opcionUsuario);
	}
	
	if (opcionUsuario == 2){
		printf("Gracias, vuelva pronto\n");
		return 5; //Rompe el while del menú
	}
	else
		return 0;
};
	

void clearInputBuffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

	
