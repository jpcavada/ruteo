
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "programmer.h"

using namespace std;

#define MAX(a,b)        ((a) > (b) ? (a) : (b))

//metodo que frena un vehiculo en un link 
static float ruteo_Detencion(LINK* link, VEHICLE* v, float posicion)	{
	float speed		= qpg_VHC_speed(v);		//velocidad actual del vehiculo
	float timeStep	= qpg_CFG_timeStep();	//Timestep actual (para calcular cuanto frenar)
    float acc;								//desaceleración que debe aplicarse
    float toStop;							//distancia restante al punto de detención.

	float vDist		= qpg_VHC_distance(v);	// distancia del vehiculo al final del link
	float stopPoint = qpg_LNK_length(link) * posicion; // Posición del punto de detención (en metros)
	
    
	// calculamos cuanto falta el punto de detencon.
	toStop = MAX(0.5F, vDist - stopPoint);
    
	// acceleration to apply to stop at this point
    acc  = qpg_CFM_constrainedAcceleration(v, link, 0.0, toStop);

	// change in speed to apply to current speed 
    speed = MAX(0.5, speed + timeStep * acc);
    
	// if at the stoping point mark the vehicle as stopped
    if (toStop <= 0.5F || toStop < speed * timeStep)
    {
		qps_VHC_stopped(v, PTRUE); 
		speed = 0.0;
	}
    
    return speed;
}

