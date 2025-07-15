#ifndef FUNCIONES_H
#define FUNCIONES_H


#include <stdio.h>
#include <stdbool.h>
//Tamaño de carácteres en arreglos
#define TAM_NOMBRE 100
#define TAM_PLACA 10
#define TAM_CEDULA 10
#define TAM_USUARIO 20
#define TAM_CONTRASENA 10

//Estructura de los datos


typedef struct{
	
	char nombrePropietario[TAM_NOMBRE];
	char numCedula[TAM_CEDULA]; // cambio a char
	char modeloAuto[10];
	char placa[TAM_PLACA];
	char colorAuto[10];
	int anioAuto;
	int multaVehiculo;
	
}datosUsuario;

//Funciones 

void menu();

int continuar();

void opcionesUsuario(int *opcionEscoger, int rangoOpciones);float calcularValormatricula(int pagoAtiempo, int hizoRevisionVehiculo, int diasPago, float multasVehiculo, int tipoVehiculo);

int validacionCaracteres(char stringValidar[]);

void validacionEntradaNombre(char *stringValidar, int tamanoChar);

void validacionNumerica(int *intValidar);

void validacionCedula(char *cedulaValidar); //cambio a char

int validarPlaca(char placa[]);

void pedirPlaca(char placa[]);

float calcularValormatricula(int pagoAtiempo, int hizoevisionVehiculo, int diasPago, float multasVehiculo, int tipoVehiculo);

void buscarVehiculo(const char *nombreArchivo, const char *datoBuscado);

void limpiarTerminal();

void registroVehiculos(FILE *archivoDatos, int *continuarRegistro);

void valorPago();

int buscarMulta(const char *nombreArchivo, const char *placaBuscada);

void cargarUsuarios();

void guardarUsuarios();

bool verificarUsuario(const char* usuario, const char* contrasena);

bool usuarioExiste(const char* usuario);

void registrar();

void iniciarSesion();

void clearInputBuffer();

void registrarLog(const char *nivel, const char *funcion, const char *mensaje);	
#endif
