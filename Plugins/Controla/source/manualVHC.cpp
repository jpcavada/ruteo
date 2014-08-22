#include "manualVHC.h"

manualVHC::manualVHC(VEHICLE* vehicle){
	this->vehicle = vehicle;
	this->id = qpg_VHC_uniqueID(vehicle);
	this->rutaBase = NULL;
	this->original_destination_zone = qpg_VHC_destination(vehicle);
	this->original_high_LaneRange = qpg_VHC_laneHigh(vehicle);
	this->original_lowerLaneRange = qpg_VHC_laneLow(vehicle);
	qps_VHC_usertag(vehicle, PTRUE);							//Lo marcamos como TAG
	
	//PINTAR EN GUI
	int colour = 12582912;
	int type = 10;
	float size = 12;
	char *format = "";
	qps_DRW_vehicleTag(vehicle, colour, type, size, format);	//Dibujamos un indicador en la simulación.
	
	buildRouteInformation();
	buildRouteStopInformation();
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
	//--INICIO RUTA DE PRUEBA RED CC-----
	routeListAdd(qpg_NET_link("118:71"));
	routeListAdd(qpg_NET_link("71:110"));
	routeListAdd(qpg_NET_link("110:48"));
	routeListAdd(qpg_NET_link("48:86"));
	routeListAdd(qpg_NET_link("86:41"));
	routeListAdd(qpg_NET_link("41:73"));
	routeListAdd(qpg_NET_link("73:85"));
	routeListAdd(qpg_NET_link("85:63"));
	routeListAdd(qpg_NET_link("63:54"));
	routeListAdd(qpg_NET_link("54:113"));
	routeListAdd(qpg_NET_link("113:114"));
	routeListAdd(qpg_NET_link("114:31"));
	routeListAdd(qpg_NET_link("31:32"));
	routeListAdd(qpg_NET_link("32:25"));
	routeListAdd(qpg_NET_link("25:142"));
	routeListAdd(qpg_NET_link("142:33"));
	routeListAdd(qpg_NET_link("33:57"));
	routeListAdd(qpg_NET_link("57:17"));
	routeListAdd(qpg_NET_link("17:37"));
	routeListAdd(qpg_NET_link("37:2"));
	routeListAdd(qpg_NET_link("2:145"));
	routeListAdd(qpg_NET_link("145:22"));
	routeListAdd(qpg_NET_link("22:21"));
	routeListAdd(qpg_NET_link("21:20"));
	routeListAdd(qpg_NET_link("20:18"));
	routeListAdd(qpg_NET_link("18:17"));
	routeListAdd(qpg_NET_link("17:37"));
	routeListAdd(qpg_NET_link("37:87"));
	routeListAdd(qpg_NET_link("87:20"));
	routeListAdd(qpg_NET_link("20:130"));
	routeListAdd(qpg_NET_link("130:75"));
	//--FIN RUTA DE PRUEBA RED CC-----

	/*	RUTA DE PRUEBA RED CHECKERS
	routeListAdd(qpg_NET_link("18:19"));
	routeListAdd(qpg_NET_link("19:27"));
	routeListAdd(qpg_NET_link("27:28"));
	routeListAdd(qpg_NET_link("28:36"));
	routeListAdd(qpg_NET_link("36:37"));
	routeListAdd(qpg_NET_link("37:29"));
	routeListAdd(qpg_NET_link("29:21"));
	routeListAdd(qpg_NET_link("21:49"));
	routeListAdd(qpg_NET_link("49:20"));
	routeListAdd(qpg_NET_link("20:12"));
	routeListAdd(qpg_NET_link("12:13"));
	routeListAdd(qpg_NET_link("13:21"));
	*/
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
		if(route->link == link && !route->passed) {
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
		//if(route->passed) continue;
		route->passed = true;
		return route->next->link;
    }
    return NULL;
}
	void manualVHC::addRouteStop(LINK* linkParada, float PosicionParada, int TiempoParada) {
		RouteStop* nuevaParada;
		float pos = PosicionParada;
		if (linkParada == 0) return;
		if (PosicionParada > 1 || PosicionParada < 0) 
			pos = 0.5;
		if (TiempoParada < 0 ) return;
		if (isOnFixedReRoute(linkParada) == 0) return;
		if (isStopLink(linkParada) != 0) return;
		nuevaParada = new RouteStop(linkParada, pos, TiempoParada);
		detenciones.push_back(nuevaParada);	
	}
	bool  manualVHC::isStopLink(LINK* link) {
		for(std::vector<int>::size_type i = 0; i != detenciones.size(); i++) {
			if (link ==  detenciones.at(i)->link)
				return true;
		}
		return false;
	}
	int manualVHC::getStopIndex(LINK* link) {
		for(std::vector<int>::size_type i = 0; i != detenciones.size(); i++) {
			if (link ==  detenciones.at(i)->link)
				return i;
		}
		return -1;
	}

	void manualVHC::buildRouteStopInformation() {
		//addRouteStop(qpg_NET_link("36:37"), 0.7F, 100);
		//addRouteStop(qpg_NET_link("21:49"), 0.5F, 100);
		//addRouteStop(qpg_NET_link("36:37"), 0.1F, 5);
		//addRouteStop(qpg_NET_link("30:31"), 0.1F, 5);
	}

	float manualVHC::getStopSpot(LINK* link) {
		if(!isStopLink(link)) return 0;
		int index = getStopIndex(link);
		if (index == -1) return 0;
		return detenciones.at(index)->spot;
	}
	int manualVHC::getStopTime(LINK* link) {
		if(!isStopLink(link)) return 0;
		int index = getStopIndex(link);
		if (index == -1) return 0;
		return detenciones.at(index)->stopTime;
	}
/*	void manualVHC::setTimeStopped(LINK* link, int newTime) {
		int index = getStopIndex(link);
		if (index ==-1) return;
		detenciones.at(index)->timeStopped = newTime;
	}
	int manualVHC::getTimeStopped(LINK* link) {
		if(!isStopLink(link)) return 0;
		int index = getStopIndex(link);
		if (index == -1) return 0;
		return detenciones.at(index)->timeStopped;
	}
*/
	void manualVHC::changeToFirstLaneOnStop(LINK* link) {	
		if (getStopTime(link) > 0) {
				qps_VHC_laneRange (this->vehicle, 1, 1);
			}
			//si ya me detuve regreso a los valores iniciales.
			else {
				qps_VHC_laneRange (this->vehicle, this->original_lowerLaneRange, this->original_high_LaneRange);
			}
	}
	void manualVHC::updateRouteStopStatus(LINK* link) {
		if (qpg_VHC_stopped(vehicle)) {
				//veo si ya lo tengo que soltar
				if(getStopTime(link) == 0) {
					qps_VHC_stopped(vehicle, PFALSE);
					qps_GUI_printf("Vehicula %i. Suelto (%f)",qpg_VHC_uniqueID(vehicle),qpg_CFG_simulationTime()); 
	
				}
				//si nó, entoces aumento el tiempo que lleva detenido en 1 seg.
				else {
					int index_of_stop = getStopIndex(link);
					int tiempo_pendiente = detenciones.at(index_of_stop)->stopTime;
					int nuevo_tiempo_pendiente = tiempo_pendiente - 1;
					detenciones.at(index_of_stop)->stopTime = nuevo_tiempo_pendiente;
					qps_GUI_printf("Vehicula %i. Le quedan (%i)",qpg_VHC_uniqueID(vehicle),detenciones.at(index_of_stop)->stopTime);
				}
			}
	}
	int manualVHC::checkForcedRouteChoice(LINK *link){
		//Obtengo el vehiculo original, para rutearlo.
		VEHICLE* trueV = qpg_VHC_original(vehicle);
		//Revisar si la llamada la hace un VHC dummy
		bool dummyV = FALSE;
		if(trueV != vehicle) 
			dummyV = TRUE;

		//obtengo la ruta correspondiente al vehiculo
		ROUTE* ruta = this->getRoute();

		if(!ruta) return 0;
		if(this->isOnFixedReRoute(link)==NULL) return 0;
		LINK* target = this->nextFixedReRouteLink(link);
		if(target==NULL) return 0;
		int n_connected_links = qpg_LNK_links(link);
		bool turn_found = false;
		// exit links in the range 1 - n_conected_links
		int exit_link = 0;
		int i = 1;
		while ((i <= n_connected_links) && (!turn_found)) { 
			// compare the target against the next exit option
			if (target == qpg_LNK_link(link, i)) {
				turn_found = TRUE;
				exit_link = i;
				break;
				}
			else {
				// move to next exit link
				i++;
			}
		}
		if(turn_found) return exit_link;
		
		return 0;
	}

	void manualVHC::clearRoute() {
		this->rutaBase = NULL;
	}
