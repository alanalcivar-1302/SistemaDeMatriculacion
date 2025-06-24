#include "funciones.h" 
#include <stdio.h>
float calcularValormatricula(int pagoAtiempo, int hizoevisionVehiculo, int diasPago, float multasVehiculo, int tipoVehiculo) {

	//Datos del recargo y descuentos
	float recargoRevision = 50.0; //Dólares
	float recargoMes = 25.0; //Dólares
	float descuentoProntopago = 0.5; //Porcentaje de descuento (50%)
	float MatriculaporVehiculo; //Variable de subsecciones para el tipo de vehículo.
	
	//Precio de matrícula con respecto al tipo de vehículo 
	switch (tipoVehiculo){
		case 1: MatriculaporVehiculo = 100.0;  //Para auto
			break;
		case 2: MatriculaporVehiculo = 150.0; //Para motocicleta
			break;
		case 3: MatriculaporVehiculo = 250.0; //Para camión
			break;
		case 4: MatriculaporVehiculo = 175,0; //Para Bus
			break;
	}
	
	// Se suman recargos
	if (hizoevisionVehiculo == 2) {
		MatriculaporVehiculo += recargoRevision;
	}
	
	if (pagoAtiempo == 2) {
		MatriculaporVehiculo += recargoMes;
	}
	
	// Descuento solamente si días <= 20
	if (pagoAtiempo == 1 && diasPago <= 20) {
		MatriculaporVehiculo *= (1 - descuentoProntopago);   // Para 50% de descuento
	}
	
	// Total a pagar
	return MatriculaporVehiculo + multasVehiculo;
	
}
