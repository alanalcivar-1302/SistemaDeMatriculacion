#include "funciones.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	
	int opcionUsuario = 0, opcionOperacion = 0;
	FILE *archivoDatos;
	datosUsuario persona;
	
	while (opcionUsuario != 5){
		
		menu();
		printf("¿Qué desea realizar?\n");
		scanf("%d",&opcionUsuario);
		opcionesUsuario(&opcionUsuario, 5);
		
		//Limpiar terminal
		system("cls");
		
		
		switch (opcionUsuario){
		case 1:
			printf("-----Registro de vehiculos-----\n");
			
			registroVehiculos(&archivoDatos,&opcionOperacion);

			break;
		case 2:
			printf("-----Buscar vehículo-----\n");
			pedirPlaca(placaBuscar);
			buscarVehiculo("datosVehiculos.txt",placaBuscar);
			break;
		case 3:{
			
			int nuevoPagomatricula = 1;
			
			while (nuevoPagomatricula) {
				int pagoAtiempo, hizoRevisionVehiculo, diasPago, tipoVehiculo ;
				float multasVehiculo, totalpagoMatricula ;
				
				printf("Seleccione su tipo de vehículo: \n");
				printf(" 1. Automóvil \n 2. Motocicleta \n 3. Camión \n 4. Bus \n");
				opcionesUsuario(&tipoVehiculo,4);
				
				printf("¿Realizó la revisión técnica? (1=Sí, 2=No): \n");
				opcionesUsuario(&hizoRevisionVehiculo,2);
				
				printf("¿Pagó la matrícula a tiempo? (1=Sí, 2=No): \n");
				opcionesUsuario(&pagoAtiempo,2);
				scanf("%d", &pagoAtiempo);
				
				printf("¿Cuántos días han pasado desde la notificación?: \n");
				scanf("%d", &diasPago);
				
				printf("Valor total de multas (sin descuentos): $\n");
				opcionesUsuario(&multasVehiculo,1000);
				
				//Total a pagar de la matrícula
				
				totalpagoMatricula = calcularValormatricula(pagoAtiempo, hizoRevisionVehiculo, diasPago, multasVehiculo, tipoVehiculo) ;
				
				if (totalpagoMatricula >= 0) {
					printf("\n--------------- COMPROBANTE DE MATRICULA ---------------\n");
					printf("Recuerde guardar el comprobante. \n");
					printf("Multas: $%.2f\n", multasVehiculo);
					printf("Total a pagar: $%.2f\n", totalpagoMatricula);
					printf("----------------------------------------------------------\n");
				}
				
				// Desea revisar nuevo pago?
				
				printf("\n¿Desea procesar otro pago de matrícula? (1 = Sí, 0 = No): \n");
				scanf("%d", &nuevoPagomatricula);
			}
			
			printf("Gracias por preferir nuestro sistema. Regrese mas tarde.\n");
			
			break;
		}
		case 4:
				printf("-----Agendar cita de revisión-----\n");
				break;
		case 5:
			break;
		default:
			break;
		}
		opcionUsuario = continuar();
	}
	
	return 0;
}
