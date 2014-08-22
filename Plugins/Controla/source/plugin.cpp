
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "programmer.h"
#include "manualVHC_list.h"

using namespace std;

#define MAX(a,b)        ((a) > (b) ? (a) : (b))

bool control = false;
manualVHC_list lista_manual = manualVHC_list();


int checkForcedRouteChoice(LINK *link, VEHICLE *vehicle);
static float slowDownSpeed(LINK* link, manualVHC* mVHC);

//**********************ESTRUCTURA TEMPORAL**********************
/*struct LINK_TEMP{
	int id;
	LINK* link_pointer;
	string link_name;
	int link_cost;
	int number_of_exits;
	LINK_TEMP() {};
	int turn_cost_by_exit[];
};
*/
//***************************************************************

void qpx_NET_postOpen() {
/*	int number_of_links_in_net = qpg_NET_links();
	vector <LINK_TEMP> link_list;
	for (int i = 1; i <= number_of_links_in_net; i++) {
		LINK_TEMP tmp;
		tmp.id = i;
		tmp.link_pointer = qpg_NET_linkByIndex(i);
		tmp.link_name = qpg_LNK_name(tmp.link_pointer);
		tmp.link_cost = qpg_LNK_cost(tmp.link_pointer,1);
		tmp.number_of_exits = qpg_LNK_exitLinks(tmp.link_pointer);
	//	turn_cost_by_exit[]
		link_list.push_back(tmp);
	}
*/
}

void qpx_VHC_release(VEHICLE* v) {
	//vamos a rutear el primer vehiculo que sale del link 17:18
	//CONTROL RED CHECKERS if (qpg_LNK_index(qpg_VHC_link(v)) == qpg_LNK_index(qpg_NET_link("17:18")) ) {
	if (qpg_LNK_index(qpg_VHC_link(v)) == qpg_LNK_index(qpg_NET_link("118:71")) ) {
	
		if (control == false) {
			lista_manual.startManualVHC(v);
			control = true;	
		}
	}
	
}

void qpx_VHC_transfer(VEHICLE* vehicle, LINK* link1, LINK* link2) {
	manualVHC* mVHC = lista_manual.getManualVHC(qpg_VHC_original(vehicle));
	if(mVHC != 0) {	
		bool    startOfRoute= FALSE;
		bool    endOfRoute	= FALSE;
		bool    onRoute	= FALSE;
		ROUTE*  route = NULL;

		//PARA DEBUG VOY A CANTAR CADA GIRO
		qps_GUI_printf("Vehiculo %i Paso de %s al %s", qpg_VHC_uniqueID(vehicle), qpg_LNK_name(link1),qpg_LNK_name(link2));

		//busco en que fase estamos
		startOfRoute= mVHC->isStartOfFixedReRoute(link2);
		endOfRoute	= mVHC->isEndOfFixedReRoute(link2);
		onRoute	= mVHC->isOnFixedReRoute(link2);

		// at some point on route do nothing
		if(onRoute && !endOfRoute && !startOfRoute) 
			qps_VHC_destination (vehicle, 0,0);

		if(endOfRoute) {

			qps_VHC_destination (vehicle, mVHC->original_destination_zone,mVHC->original_destination_zone);
			}
		else if(startOfRoute)
			{ 

 			qps_VHC_destination (vehicle, 0,0);
		}
	}
	
}

/*void qpx_TGV_transfer(VEHICLE* vehicle, LINK* link1, LINK* link2){
	//revisamos si el vehiculo debería ser controlado manualmente.	
 	int linkno = qpg_LNK_index(qpg_VHC_link(vehicle));
	manualVHC* mVHC = lista_manual.getManualVHC(qpg_VHC_original(vehicle));
	//if (lista_manual.isInList(vehicle)) {
 	if(mVHC != NULL) {	
			//Mensajes para ver que esta pasando
			
		int a = qpg_VHC_usertag(vehicle);
		int id_vhc = qpg_VHC_uniqueID(vehicle);	
		qps_GUI_printf("lo encontre (ID = %i) y su tag es %i ",id_vhc, a);
			
		//le asigno la ruta
		bool    startOfRoute= FALSE;
		bool    endOfRoute	= FALSE;
		bool    onRoute	= FALSE;
		ROUTE*  route = NULL;

		// where are we moveing to
		startOfRoute= mVHC->isStartOfFixedReRoute(link2);
		endOfRoute	= mVHC->isEndOfFixedReRoute(link2);
		onRoute	= mVHC->isOnFixedReRoute(link2);

		//qps_VHC_nextlink(vehicle, checkForcedRouteChoice(link2, vehicle));
		// at some point on route do nothing
		/*
		if(onRoute && !endOfRoute && !startOfRoute) return;

		if(endOfRoute)
			{
			// leaving route moving to last link so route 
			// choice has already been made can just clear 
			// the route
			//qps_VHC_userdata(vehicle,NULL);

			// ask the vehicle to re-evaluate its route choice.
			qps_VHC_destination (vehicle, 0,0);
			}
		else if(startOfRoute)
			{
			// vehicle is joining route, start is link2
			// assgin route info to vehicle 
			//mVHC->buildRouteInformation();
			//route = getRouteFromStart();
			//qps_VHC_userdata(vehicle,(VHC_USERDATA*)route);    

			// now ask vehicle to re-evaluate its route choice
			// as next and nextnext will have already been set
			qps_VHC_destination (vehicle, 0,0);
		}
		
		qps_VHC_destination (vehicle, 0,0);
		
	}
			
}*/



/*int checkForcedRouteChoice(LINK *link, VEHICLE *vehicle){
	//Obtengo el vehiculo original, para rutearlo.
	VEHICLE* trueV = qpg_VHC_original(vehicle);
	//REVISAR SI ES NECESARIO O SI PASA ALGUNA VEZ
	bool dummyV = FALSE;
	if(trueV != vehicle) 
		dummyV = TRUE;

	manualVHC* mVHC = lista_manual.getManualVHC(trueV);
	if(mVHC==0) 
		return 0;

	//obtengo la ruta correspondiente al vehiculo
	ROUTE* ruta = mVHC->getRoute();

	if(!ruta) return 0;
	if(mVHC->isOnFixedReRoute(link)==NULL) return 0;
	LINK* target = mVHC->nextFixedReRouteLink(link);
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
*/
Bool qpo_RTM_enable() 
{
	return PTRUE;
}

int qpo_RTM_decision(LINK *linkp, VEHICLE* vehicle) {
	
	VEHICLE* trueV = qpg_VHC_original(vehicle);
	/*//REVISAR SI ES NECESARIO O SI PASA ALGUNA VEZ
	bool dummyV = FALSE;
	if(trueV != vehicle) 
		dummyV = TRUE;
	*/
	//Reviso si es vehiculo bajo control manual
	manualVHC* mVHC = lista_manual.getManualVHC(trueV);
	if(mVHC==0) 
		return 0;
	else
		return mVHC->checkForcedRouteChoice(linkp);
}

float qpo_CFM_leadSpeed(LINK* link, VEHICLE* vehicle,  VEHICLE* ahead[]) {
	//Si el vehiculo esta detenido, skip.
	if(qpg_VHC_stopped(vehicle)) 
		return 0.0; 
	//reviso si el vehiculo esta bajo control manual
	manualVHC* mVHC = lista_manual.getManualVHC(qpg_VHC_original(vehicle));
	if(mVHC == 0) 
		return qpg_CFM_leadSpeed(link, vehicle, ahead);
	//reviso si el link corresponde a una parada
	bool isStop = mVHC->isStopLink(link);
	if(!isStop) 
		return qpg_CFM_leadSpeed(link, vehicle, ahead);
	//reviso que no halla parado ya en este link
	if(mVHC->getStopTime(link)==0)
		return qpg_CFM_leadSpeed(link, vehicle, ahead);
	
	//Tengo que detener este auto en este link
	//calculamos la distancia disponible para frenar, el punto de frenado y la distancia mínima de frenado
	float vDist		= qpg_VHC_distance(vehicle); 
	float stopPoint = qpg_LNK_length(link) * (1-mVHC->getStopSpot(link)); 
	float vSafeStop = qpg_CFM_stoppingDistance(vehicle); 
	
	//Si ya se pasó...se pasó.
	if (vDist < stopPoint )
		return qpg_CFM_leadSpeed(link, vehicle, ahead);
	//si no es seguro detener, no lo hago y aviso en la GUI
	else if(vDist > (stopPoint + vSafeStop)) {
		// too far away to care
		return qpg_CFM_leadSpeed(link, vehicle, ahead);
	}
	else {
		return slowDownSpeed(link,mVHC);	
	}
}
float qpo_CFM_followSpeed(LINK* link, VEHICLE* vehicle,  VEHICLE* ahead[]) {
	//Si el vehiculo esta detenido, skip.
	if(qpg_VHC_stopped(vehicle)) 
		return 0.0; 
	//reviso si el vehiculo esta bajo control manual
	manualVHC* mVHC = lista_manual.getManualVHC(qpg_VHC_original(vehicle));
	if(mVHC == 0) 
		return qpg_CFM_followSpeed(link, vehicle, ahead);
	//reviso si el link corresponde a una parada
	bool isStop = mVHC->isStopLink(link);
	if(!isStop) 
		return qpg_CFM_followSpeed(link, vehicle, ahead);
	//reviso que no halla parado ya en este link
	if(mVHC->getStopTime(link)==0)
		return qpg_CFM_followSpeed(link, vehicle, ahead);
	//Tengo que detener este auto en este link
	//calculamos la distancia disponible para frenar, el punto de frenado y la distancia mínima de frenado
	float vDist		= qpg_VHC_distance(vehicle); 
	float stopPoint = qpg_LNK_length(link) *(1- mVHC->getStopSpot(link)); 
	float vSafeStop = qpg_CFM_stoppingDistance(vehicle); 
	
	//Si ya se pasó...se pasó.
	if (vDist < stopPoint )
		return qpg_CFM_followSpeed(link, vehicle, ahead);
	//si no es seguro detener, no lo hago y aviso en la GUI
	else if(vDist > (stopPoint + vSafeStop)) {
		// too far away to care
		return qpg_CFM_followSpeed(link, vehicle, ahead);
	}
	else {
		return slowDownSpeed(link,mVHC);	
	}
}
float slowDownSpeed(LINK* link, manualVHC* mVHC)
{
	VEHICLE* v = mVHC->vehicle;
	float speed		= qpg_VHC_speed(v);
	float timeStep	= qpg_CFG_timeStep();
    float acc;
    float toStop;

	float vDist		= qpg_VHC_distance(v); // distance to the end of the link
	float e = 1-(mVHC->getStopSpot(link));
	float stopPoint = qpg_LNK_length(link) *e;
	
	// how far left to travel
	toStop = MAX(0.5F, vDist - stopPoint);
    
	// acceleration to apply to stop at this point
    acc  = qpg_CFM_constrainedAcceleration(v, link, 0.0, toStop);

	// change in speed to apply to current speed 
    speed = MAX(0.5F, speed + timeStep * acc);
    
	// if at the stoping point mark the vehicle as stopped
    if ((toStop <= 1 || toStop < speed * timeStep) )
    {
		qps_VHC_stopped(v, PTRUE); 
		speed = 0.0;
		//qps_GUI_printf("Vehicula %i. detenido (%f)",qpg_VHC_uniqueID(v),qpg_CFG_simulationTime()); 
	}
    
    return speed;
}
void qpx_LNK_vehicleTimeStep(LINK* link, VEHICLE* vehicle) {
	//reviso si el vehiculo está en control manual
	manualVHC* mVHC = lista_manual.getManualVHC(qpg_VHC_original(vehicle));
	if(mVHC != 0) {
		//Reviso si me encuentro en un LINK de parada
		if (mVHC->isStopLink(link)) {
			//Forzar el cambiar al lane de más derecha antes de la detención.
			mVHC->changeToFirstLaneOnStop(link);

			//Actualizo el la situación del vehiculo (diminuye el stopTime o lo libera si StopTime == 0
			mVHC->updateRouteStopStatus(link);
		}
	}
}