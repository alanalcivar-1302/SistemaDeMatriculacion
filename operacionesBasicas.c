#include "funciones.h"

#include <stdio.h>
#include <stdlib.h>


//TamaÃ±o de carÃ¡cteres en arreglos


void limpiarTerminal(){
	system("cls");
}
	
void menu(){
	printf("1. Registrar vehÃ­culo \n");
	printf("2. Buscar vehÃ­culo por placa \n");
	printf("3. Consultar valor a pagar por matricula\n");
	printf("4. Agendar cita de revisiÃ³n\n");
	printf("5. Listar vehiculos registrados\n");
	printf("6. Salir\n");
};
	
	
int continuar(){
	int opcionUsuario;
	printf("¿Desea realizar algo mas? (1. Si/2. No)\n");
	scanf("%d",&opcionUsuario);
	
	//Validacion de la respuesta del usuario
	while (opcionUsuario != 2 && opcionUsuario != 1){
		printf("Opcion no valida ingrese (1. Si/2. No) \n");
		scanf("%d",&opcionUsuario);
	}
	
	if (opcionUsuario == 2){
		printf("Gracias, vuelva pronto\n");
		return 5; //Rompe el while del menÃº
	}
	else
		return 0;
};
		
		
void clearInputBuffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
