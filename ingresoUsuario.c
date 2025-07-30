#include "funciones.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100
#define TAM_NOMBRE 100
#define TAM_PLACA 10
#define TAM_CEDULA 10

void menuInicio(){
	int opcionUsuario = 0, opcionOperacion = 0;
	FILE *archivoDatos;
	char placaBuscar[TAM_PLACA];
	
	while (opcionUsuario != 6){
		
		menu();
		printf("Â¿QuÃ© desea realizar?\n");
		opcionesUsuario(&opcionUsuario, 6);
		
		limpiarTerminal();
		
		
		switch (opcionUsuario){
		case 1:
			printf("-----Registro de vehiculos-----\n");
			
			registroVehiculos(&archivoDatos,&opcionOperacion);
			
			break;
		case 2:
			printf("-----Buscar vehÃ­culo-----\n");
			
			clearInputBuffer();
			
			printf("Ingrese la placa (ej: ABC-1234): \n");
			pedirPlaca(placaBuscar);
			
			buscarVehiculo("datosVehiculos.txt",placaBuscar);
			system("pause");
			
			break;
		case 3:{
			printf("-----Calculo del valor de la matricula-----\n");
			
			valorPago();
			
			break;
		}
		case 4:
				printf("-----Agendar cita de revisiÃ³n-----\n");
				agendarCita();
				break;
		case 5:
			printf("-----Listar vehiculos registrados-----\n");
			
			listarVehiculos();
			
			break;
		case 6:
			printf("Gracias por usar nuestro sistema\n");
			system("pause");
			break;
		default:
			break;
		}
		limpiarTerminal();
	}
}

typedef struct {
	char usuario[20];
	char contrasena[10];
} usuario;


usuario usuarios[MAX];
int totalUsuarios = 0;

void cargarUsuarios() {
	FILE *archivo = fopen("Users.txt", "r");
	if (archivo) {
		while (fscanf(archivo, "%49[^,],%49s\n", usuarios[totalUsuarios].usuario, 
					  usuarios[totalUsuarios].contrasena) == 2) {
			totalUsuarios++;
		}
		fclose(archivo);
	}
}

void guardarUsuarios() {
	FILE *archivo = fopen("Users.txt", "w");
	for (int i = 0; i < totalUsuarios; i++) {
		fprintf(archivo, "%s,%s\n", usuarios[i].usuario, usuarios[i].contrasena);
	}
	fclose(archivo);
}

bool verificarUsuario(const char* usuario, const char* contrasena) {
	for (int i = 0; i < totalUsuarios; i++) {
		if (strcmp(usuario, usuarios[i].usuario) == 0 && 
			strcmp(contrasena, usuarios[i].contrasena) == 0) {
			return true;
		}
	}
	return false;
}

bool usuarioExiste(const char* usuario) {
	for (int i = 0; i < totalUsuarios; i++) {
		if (strcmp(usuario, usuarios[i].usuario) == 0) {
			return true;
		}
	}
	return false;
}

void registrar() {
	if (totalUsuarios >= MAX) {
		printf("No se pueden registrar mÃ¡s usuarios.\n");
		return;
	}
	
	printf("\nIngrese nuevo usuario: ");
	scanf("%49s", usuarios[totalUsuarios].usuario);
	
	printf("Ingrese nueva contraseÃ±a: ");
	scanf("%49s", usuarios[totalUsuarios].contrasena);
	
	totalUsuarios++;
	guardarUsuarios();
	printf("\nÂ¡Registro exitoso! Ahora puedes iniciar sesiÃ³n.\n\n");
	system("pause");
	limpiarTerminal();
}

void iniciarSesion() {
	char usuario[50];
	char contrasena[50];
	
	
	printf("Usuario: ");
	scanf("%49s", usuario);
	
	printf("ContraseÃ±a: ");
	scanf("%49s", contrasena);
	
	if (verificarUsuario(usuario, contrasena)) {
		printf("\nÂ¡Ingreso correcto! Bienvenido %s \n",usuario);
		system("pause");
		limpiarTerminal();
		menuInicio();
		
	} else {
		limpiarTerminal();
		int opcion;
		printf("\nUsuario o contraseÃ±a incorrectos\n");
		printf("1. Intentar de nuevo\n");
		printf("2. Registrarse\n");
		printf("Seleccione una opciÃ³n: ");
		scanf("%d", &opcion);
		
		if (opcion == 1) {
			limpiarTerminal();
			iniciarSesion();
		} else if (opcion == 2) {
			limpiarTerminal();
			registrar();
			iniciarSesion();
		}
	}
}


