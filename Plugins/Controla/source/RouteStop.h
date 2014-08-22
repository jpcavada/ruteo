#pragma once

#include "programmer.h"


class RouteStop {
	public:
		LINK* link;				//Puntero al Link de Paramics al que esta detencion se encuetra asociada
		float spot;				//Fracción del link donde el vehiculo debe detenerse (entre 0 y 1)
		int stopTime;			//Tiempo restante de detención
		int timeStopped;		//tiempo que lleva detenido
		
		RouteStop (LINK* link, float lugar, int tiempo) {
			this->link = link;
			this->spot = lugar;
			this->stopTime = tiempo;
			this->timeStopped = 0;
			
		}
};