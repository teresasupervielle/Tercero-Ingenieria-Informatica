#ifndef PARAMETERS_H_
#define PARAMETERS_H_

/// Time in ms the LED stays ON or OFF.
uint16_t SET_POINT = 200; //Limite (obtenido tras ver los datos recogidos con la LDR) para que se encienda la luz	

#define CONFIGURATION		0 //Estado configuracion
#define PRODUCTION			1 //Estado produccion
#define SAMPLE_TIME			1000 //Tiempo para que adquiera un dato de la LDR o del POT

#endif /* PORTS_H_ */
