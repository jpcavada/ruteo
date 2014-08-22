
#pragma once

#include "programmer.h"

#define ROUTE_DEFAULT		0

class ROUTE {
	public:
		ROUTE* next;						//Puntero al siguiente elemento de la ruta
		LINK* link;							//Puntero al link de Parammics correspondiente a este elemento de la ruta
		bool passed;						//Indica si el vehiculo ya ha pasado por este elemento de la ruta o no.
		
		ROUTE (LINK* link, ROUTE* next) {
			this->link = link;
			this->next = next;
			this->passed = false;
		}
};
