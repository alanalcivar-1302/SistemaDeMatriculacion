#include "funciones.h"

#include <stdio.h>
#include <stdlib.h>


//TamaÃ±o de carÃ¡cteres en arreglos


void limpiarTerminal(){
	system("cls");
}
	
void menu(){
	printf("1. Registrar veh%cculo\n", 161);         
	printf("2. Buscar veh%cculo por placa\n", 161);   
	printf("3. Consultar valor a pagar por matr%ccula\n", 161); 
	printf("4. Agendar cita de revisi%cn\n", 162);   
	printf("5. Listar vehiculos registrados\n");
	printf("6. Salir\n");
	
};
	
void clearInputBuffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
