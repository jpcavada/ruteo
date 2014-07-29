#pragma once
#include "programmer.h"
#include "Route.h"

//----------Foward declaration-------------
//class VEHICLE;
//---------End of Foward declaration-------

class manualVHC {
	
public:
	VEHICLE* vehicle;
	ROUTE* rutaBase;

	int id;

	manualVHC(VEHICLE* vehicle);
	~manualVHC(void);

	//implementadas pero no probadas
	void routeListAdd(LINK* link);								//add link to the current route
	void buildRouteInformation(void);							//Usar este metodo para cargar una nueva ruta.
	bool isStartOfFixedReRoute(LINK* link);						// is the given link at the *start* of a re-routing section
	bool isEndOfFixedReRoute(LINK* link);						// is the given link at the *end* of a re-routing section
	ROUTE* getRoute();								// return a route that's start link matches the given link
	bool isOnFixedReRoute(LINK* link);							// is the given link part of a re-routing section
	LINK* nextFixedReRouteLink(LINK* link);						// find the next link on the route, follwoing the given one

	//no implementadas (yet)!
//	int checkForcedRouteChoice(LINK *link, VEHICLE *vehicle);	// find the next link on the vehicles fixed route, if any?
};
