
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "programmer.h"
#include "manualVHC_list.h"

using namespace std;

bool control = false;
manualVHC_list lista_manual = manualVHC_list();

void qpx_VHC_release(VEHICLE* v) {
	//vamos a rutear el primer vehiculo que sale del link 17:18
	if (qpg_LNK_index(qpg_VHC_link(v)) == qpg_LNK_index(qpg_NET_link("17:18")) ) {
		if (control == false) {
			lista_manual.startManualVHC(v);
			control = true;	
		}
	}
	
}

void qpx_TGV_transfer(VEHICLE* vehicle, LINK* link1, LINK* link2){
	//revisamos si el vehiculo debería ser controlado manualmente.	
 	int linkno = qpg_LNK_index(qpg_VHC_link(vehicle));
	manualVHC* mVHC = lista_manual.getManualVHC(vehicle);
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
		*/
			qps_VHC_destination (vehicle, 0,0);
		}
			
}



int checkForcedRouteChoice(LINK *link, VEHICLE *vehicle){
	//Obtengo el vehiculo original, para rutearlo.
	VEHICLE* trueV = qpg_VHC_original(vehicle);
	//REVISAR SI ES NECESARIO O SI PASA ALGUNA VEZ
	bool dummyV = FALSE;
	if(trueV != vehicle) dummyV = TRUE;

	manualVHC* mVHC = lista_manual.getManualVHC(trueV);
	if(!mVHC) return 0;

	//obtengo la ruta correspondiente al vehiculo
	ROUTE* ruta = mVHC->getRoute();

	if(!ruta) return 0;
	if(!mVHC->isOnFixedReRoute(link)) return 0;
	LINK* target = mVHC->nextFixedReRouteLink(link);
	if(!target) return 0;
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

Bool qpo_RTM_enable() 
{
	return PTRUE;
}

int qpo_RTM_decision(LINK *linkp, VEHICLE *Vp) {
	return checkForcedRouteChoice(linkp, Vp);
}

