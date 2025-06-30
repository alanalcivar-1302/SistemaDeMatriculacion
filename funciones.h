#ifndef FUNCIONES_H
#define FUNCIONES_H

//Tamaño de carácteres en arreglos
//#define TAM_CEDULA 15
#define TAM_NOMBRE 100
#define TAM_PLACA 10
#define TAM_CEDULA 10

//Estructura de los datos

typedef struct{
	
	char nombrePropietario[TAM_NOMBRE];
	char numCedula[TAM_CEDULA];
	char modeloAuto[10];
	char placa[TAM_PLACA];
	char colorAuto[10];
	int anioAuto;
	
}datosUsuario;


//Funciones 

void menu();

int continuar();

void opcionesUsuario(int *opcionEscoger, int rangoOpciones);float calcularValormatricula(int pagoAtiempo, int hizoRevisionVehiculo, int diasPago, float multasVehiculo, int tipoVehiculo);

int validacionCaracteres(char stringValidar[]);

void validacionEntradaNombre(char *stringValidar);
	
void validacionNumerica(char *intValidar);

void validacionCedula(char *cedulaValidar);

int validarPlaca(char placa[]);

void pedirPlaca(char placa[]);

float calcularValormatricula(int pagoAtiempo, int hizoevisionVehiculo, int diasPago, float multasVehiculo, int tipoVehiculo);

void buscarVehiculo(const char *nombreArchivo, const char *datoBuscado);

void limpiarTerminal();

void registroVehiculos(FILE *archivoDatos, *continuarRegistro)

#endif
