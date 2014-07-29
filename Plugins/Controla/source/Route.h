#pragma once

#include "programmer.h"

#define ROUTE_DEFAULT		0

class ROUTE {
	public:
		ROUTE* next;
		LINK* link;
		ROUTE (LINK* link, ROUTE* next) {
			this->link = link;
			this->next = next;
		}
};
