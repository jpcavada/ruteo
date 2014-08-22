#pragma once
#include "programmer.h"
#include "Route.h"
#include <vector>
#include "RouteStop.h"


class manualVHC {
	
public:
	VEHICLE* vehicle;								//Puntero al Vehiculo de Paramics
	ROUTE* rutaBase;								//Puntero al inicio de la ruta asociada al vehiculo.

	std::vector <RouteStop*> detenciones;			//vector de detenciones (dentro de la ruta)
	
	int id;											//id de Paramics del Vehiculo
	int original_lowerLaneRange;					//Rango de pista inicial inferior
	int original_high_LaneRange;					//Rango de pista inicial supererior
	int original_destination_zone;					//Zona de Destino Inicial

	
	manualVHC(VEHICLE* vehicle);					//Constructor
	~manualVHC(void);								//Destructor

	void buildRouteInformation();							//Usar este metodo para cargar una nueva ruta.
	void buildRouteStopInformation();						//Usar metodo para construir la información de Detenciones
	
	//FUNCIONES ASOCIADAS AL RUTEO
	void clearRoute();											//Elimina la ruta actual asignada al vehiculo.
	void routeListAdd(LINK* link);								//Agrega un Link al final de la ruta actual. (No revisa que la ruta sea valida).
	bool isStartOfFixedReRoute(LINK* link);						// is the given link at the *start* of a re-routing section
	bool isEndOfFixedReRoute(LINK* link);						// is the given link at the *end* of a re-routing section
	ROUTE* getRoute();											// return a route that's start link matches the given link
	bool isOnFixedReRoute(LINK* link);							// is the given link part of a re-routing section
	LINK* nextFixedReRouteLink(LINK* link);						// find the next link on the route, follwoing the given one
	int checkForcedRouteChoice(LINK *link);
	
	//FUNCIONES ASOCIADAS A LAS DETENDIONES
	void addRouteStop(LINK* linkParada, float PosicionParada, int TiempoParada);	//Agrega una detención a la lista de detenciones, solo si el linkParada 
	bool isStopLink(LINK* link);													//Pregunta si el link tiene una detencion asociada
	int manualVHC::getStopIndex(LINK* link);										//Devuelve el indice de la detencion asociada al link (-1 si no existe)
	float getStopSpot(LINK* link);													//Devuelve la fraccion (de 0 a 1) del link donde debe detenerse
	int getStopTime(LINK* link);													//Devuelve el tiempo restante (en timeSteps) de detencion en la parada asociada al link
	//int getTimeStopped(LINK* link);													//Devuelvel el tiempo que ha estado detenido el vehiculo en el link
	//void setTimeStopped(LINK* link, int newTime);										//Modifica el tiempo que ha estado de detenido el vehiculo en la parada asociada al LINK
	void changeToFirstLaneOnStop(LINK* link);										//(Usar con qpx_VHC_timeStepLink)Si el link corresponde a un link de parada, incita (no fuerza) a que se detenga en la primera linea.
	void updateRouteStopStatus(LINK* link);											//(Usar con qpx_VHC_timeStepLink)Actualiza el tiempo de parada en una detención o lo pone en movimiento si la detencion terminó.
};
