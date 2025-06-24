#include "funciones.h"

#include <stdio.h>

float calcularValormatricula(int pagoAtiempo, int hizoRevisionVehiculo, int diasPago, float multasVehiculo, int tipoVehiculo) {
	
	//Datos del recargo y descuentos
	float recargoRevision = 50.0; //D?lares
	float recargoMes = 25.0; //D?lares
	float descuentoProntopago = 0.5; //Porcentaje de descuento (50%)
	float MatriculaporVehiculo; //Variable de subsecciones para el tipo de veh?culo.
	
	//Precio de matr?cula con respecto al tipo de veh?culo 
	switch (tipoVehiculo){
	case 1: 
		MatriculaporVehiculo = 100.0;  //Para auto
		break;
	case 2: 
		MatriculaporVehiculo = 150.0; //Para motocicleta
		break;
	case 3: 
		MatriculaporVehiculo = 250.0; //Para cami?n
		break;
	case 4: 
		MatriculaporVehiculo = 175.0; //Para Bus
		break;
	default:
		return 0;
	}
	
	// Se suman recargos
	if (hizoRevisionVehiculo == 2) {
		MatriculaporVehiculo += recargoRevision;
	}
	
	if (pagoAtiempo == 2) {
		MatriculaporVehiculo += recargoMes;
	}
	
	// Descuento solamente si d?as <= 20
	if (pagoAtiempo == 1 && diasPago <= 20) {
		MatriculaporVehiculo *= (1 - descuentoProntopago);   // Para 50% de descuento
	}
	
	// Total a pagar
	return MatriculaporVehiculo + multasVehiculo;
	
}
