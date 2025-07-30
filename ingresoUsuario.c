#include "funciones.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>

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
		printf("Qu%c desea realizar?\n",130);
		opcionesUsuario(&opcionUsuario, 6);
		
		limpiarTerminal();
		
		
		switch (opcionUsuario){
		case 1:
			
			registroVehiculos(&archivoDatos,&opcionOperacion);
			
			break;
		case 2:
			printf("-----Buscar veh%cculo-----\n",161);
			
			clearInputBuffer();
			
			printf("Ingrese la placa (ej: ABC-1234): \n");
			pedirPlaca(placaBuscar);
			
			buscarVehiculo("datosVehiculos.txt",placaBuscar);
			system("pause");
			
			break;
		case 3:{

				valorPago();
			break;
		}
		case 4:
				printf("-----Agendar cita de revisi%cn-----\n",162);
				agendarCita();
				break;
		case 5:
			printf("-----Listar veh%cculos registrados-----\n",161);
			
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
		printf("No se pueden registrar m%cs usuarios.\n",160);
		return;
	}
	
	printf("\nIngrese nuevo usuario: ");
	scanf("%49s", usuarios[totalUsuarios].usuario);
	
	printf("Ingrese nueva contrase%ca: ",164);
	scanf("%49s", usuarios[totalUsuarios].contrasena);
	
	totalUsuarios++;
	guardarUsuarios();
	printf("\n%cRegistro exitoso!\n",33);
	system("pause");
	limpiarTerminal();
	menuInicio();
}

void iniciarSesion() {
	int opcion;
	
	printf("\n¿Desea registrarse antes de iniciar sesi%cn?\n",162);
	printf("1. Si\n");
	printf("2. No, quiero iniciar sesi%cn\n",162);
	printf("\nSeleccione una opci%cn: ",162);
	opcionesUsuario(&opcion, 2);// Asumiendo que esta función valida la opción
	
	if (opcion == 1) {
		limpiarTerminal();
		registrar();  // Llama a la función de registro
		return;  // Termina la función para no continuar con el inicio de sesión
	}
	char usuario[50];
	char contrasena[50];
	
	limpiarTerminal();
	printf("Usuario: ");
	scanf("%49s", usuario);
	
	printf("Contrase%ca: ",164);
	scanf("%49s", contrasena);
	
	if (verificarUsuario(usuario, contrasena)) {
		printf("\n%cIngreso correcto! Bienvenido %s \n",33,usuario);
		system("pause");
		limpiarTerminal();
		menuInicio();
		
	} else {
		limpiarTerminal();
		int opcion;
		printf("\nUsuario o contrase%ca incorrectos\n",164);
		printf("1.Regresar\n");
		//printf("2. Registrarse\n");
		//printf("Seleccione una opci%cn: ",162);
		scanf("%d", &opcion);
		
		if (opcion == 1) {
			limpiarTerminal();
			iniciarSesion();
		} /*else if (opcion == 2) {
			limpiarTerminal();
			registrar();
			iniciarSesion();
		}*/
	}
}


