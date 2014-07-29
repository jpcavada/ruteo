#include "manualVHC.h"

manualVHC::manualVHC(VEHICLE* vehicle){
	this->vehicle = vehicle;
	this->id = qpg_VHC_uniqueID(vehicle);
	this->rutaBase = NULL;
	qps_VHC_usertag(vehicle, PTRUE);							//Lo marcamos como TAG
	int colour = 12582912;
	int type = 0;
	float size = 0;
	char *format = "";
	qps_DRW_vehicleTag(vehicle, colour, type, size, format);	//Dibujamos un indicador en la simulación.
	buildRouteInformation();
}

manualVHC::~manualVHC(void) {}

void manualVHC::routeListAdd(LINK* link) {
	ROUTE* route;
    // llego hasta el final de la lista y agrego la nueva ruta al final.
    for (route = rutaBase; route != NULL && route->next != NULL; route = route->next) {
    }

	ROUTE* newLink = new ROUTE(link,NULL);
    //newLink->link = link;
    //newLink->next = NULL;

	//si está vacio creo una nueva ruta base
    if (route == NULL) {
        rutaBase = newLink;
    }
    //si ya tiene ruta entonces simplemente la agrego al final.
	else {
        route->next = newLink;
    }
}

void manualVHC::buildRouteInformation() {
	routeListAdd(qpg_NET_link("18:19"));
	routeListAdd(qpg_NET_link("19:27"));
	routeListAdd(qpg_NET_link("27:28"));
	routeListAdd(qpg_NET_link("28:36"));
	routeListAdd(qpg_NET_link("36:37"));
	routeListAdd(qpg_NET_link("37:29"));
	routeListAdd(qpg_NET_link("29:21"));
	routeListAdd(qpg_NET_link("21:20"));
	routeListAdd(qpg_NET_link("20:12"));
	routeListAdd(qpg_NET_link("12:13"));
	routeListAdd(qpg_NET_link("13:14"));
}
//¿Es el link actual es el primero de la ruta?
bool manualVHC::isStartOfFixedReRoute(LINK* link) {
	if(!link)		 return FALSE;
	if(!rutaBase)    return FALSE;
	if(rutaBase->link != link) return FALSE;
	return TRUE;
}
//¿es el link el último de la ruta?
bool manualVHC::isEndOfFixedReRoute(LINK* link) {
	ROUTE* route;
	if(!link)	return FALSE;
    if(!rutaBase)	return FALSE;

    //Itero hasta el final.
    for (route = rutaBase; route != NULL && route->next != NULL; route = route->next) {}

    if(route->link != link)	{
		return FALSE;
    }
	else {
		return TRUE;
    }
}

ROUTE* manualVHC::getRoute() {
	return rutaBase;
} 

//¿Es el link actual parte de la ruta a seguir?
bool manualVHC::isOnFixedReRoute(LINK* link) {
	ROUTE* route;
    if(!link)	return FALSE;
    if(!rutaBase)	return FALSE;

    for (route = rutaBase; route != NULL && route->next != NULL; route = route->next) {
		if(route->link == link) {
			return TRUE;
		}
    }
    return FALSE;
}
//Encuentra el "next" link en la ruta, despues del link actual.
LINK* manualVHC::nextFixedReRouteLink(LINK* link){
	ROUTE* route;

    if(!link)		    return NULL;
    if(!rutaBase)    return NULL;

    for (route = rutaBase; route != NULL && route->next != NULL; route = route->next) {
		if(route->link != link) continue;
	
		// found link, what about the next one
		if(!route->next)	continue;
		if(!route->next->link)	continue;

		return route->next->link;
    }
    return NULL;
}
//Encuentra el siguiete link el la ruta del vehiculo
//int manualVHC::checkForcedRouteChoice(LINK *link, VEHICLE *vehicle){
//	//Obtengo el vehiculo original, para rutearlo.
//	VEHICLE* trueV = qpg_VHC_original(vehicle);
//	//REVISAR SI ES NECESARIO O SI PASA ALGUNA VEZ
//	bool dummyV = FALSE;
//	if(trueV != vehicle) dummyV = TRUE;
//
//	//obtengo la ruta correspondiente al vehiculo
//	ROUTE* ruta = manualVHC
//	
//}


