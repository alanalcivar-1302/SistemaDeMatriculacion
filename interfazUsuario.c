#include <stdio.h>
#include <stdlib.h>

void menu() {
	printf("1. Agendar citas.\n");
	printf("2. Calculo valor a pagar por matricula.\n");
	printf("3. Buscar auto por cedula.\n");
	printf("4. Salir.\n");
}

void menuDeinicio() {
	printf("1. Usuario.\n");
	printf("2. Administrador.\n");
}

int main() {
	int opcionDeingreso;
	
	do {
		menuDeinicio();
		printf("\nSeleccione como desea ingresar: ");
		scanf("%d", &opcionDeingreso);
		system("cls");
		
		switch (opcionDeingreso) {
		case 1: {
			int opciones;
			do {
				menu();
				printf("\nIngrese una opcion: ");
				scanf("%d", &opciones);
				system("cls");
				
				switch (opciones) {
				case 1:
					printf("Selecciono la opcion 1\n");
					break;
				case 2:
					printf("Selecciono la opcion 2\n");
					break;
				case 3:
					printf("Selecciono la opcion 3\n");
					break;
				case 4:
					printf("Hasta pronto\n");
					break;
				default:
					printf("Opcion no valida. Intente de nuevo.\n");
					break;
				}
			} while (opciones < 1 || opciones > 4); 
			break;
		}
		case 2:
			printf("Menu de administradores.\n");
			break;
		default:
			printf("Opcion no valida. Intente de nuevo.\n");
			break;
		}
	} while (opcionDeingreso != 1 && opcionDeingreso != 2); 
	
	return 0;
}
