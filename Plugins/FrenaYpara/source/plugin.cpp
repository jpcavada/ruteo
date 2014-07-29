
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "programmer.h"

using namespace std;

#define MAX(a,b)        ((a) > (b) ? (a) : (b))

#define START_TIME			300.0
#define END_TIME			400.0
#define SLOW_DOWN_LINK		"2:5"
#define SLOW_DOWN_LOCATION	0.50

static float slowDownSpeed(LINK* link, VEHICLE* v);

// sample plugin showing how slow down and stop a vehicle at a specific point on 
// a link eas - 11/4/05


// override lead speed
float qpo_CFM_leadSpeed(LINK* link, VEHICLE* v,  VEHICLE* ahead[])
{
	float vDist		= qpg_VHC_distance(v);							// distance to the end of the link
	float stopPoint = qpg_LNK_length(link) * SLOW_DOWN_LOCATION;	// xx% of link length from the end
	float vSafeStop = qpg_CFM_stoppingDistance(v);					// distance the v needs to stop safely
	
	//if already stopped skip 
	if(qpg_VHC_stopped(v)) return 0.0; 

	// implament after x seconds of sim, and cancel after y seconds, could also be 
	// checking a bool state for this
	if(qpg_CFG_simulationTime() < START_TIME || qpg_CFG_simulationTime() > END_TIME)
		return qpg_CFM_leadSpeed(link, v, ahead);	

	// check if this is the right link
	if(strcmp(qpg_LNK_name(qpg_VHC_link(v)),SLOW_DOWN_LINK) != 0) 
		return qpg_CFM_leadSpeed(link, v, ahead);

	// apply to the first vehicle that is upstream of the stoping point, could 
	// be lead vehicle or not so need to check both clauses. 
	// the vehicle needs to be far enough upstream of the stoping point to stop
	// safely, no point trying to stop one a few meters away, we 
	// want to stop it...not crash it!
	
	if(vDist < stopPoint)
	{
		// too close to stop safely
		return qpg_CFM_leadSpeed(link, v, ahead);
	}
	else if(vDist > (stopPoint + vSafeStop))
	{
		// too far away to care
		return qpg_CFM_leadSpeed(link, v, ahead);
	}
	else 
	{
		// right time
		// right link
		// not stoped
		// upstream of the stoping point a safe stopable distence
		// so...... slow it down
		return slowDownSpeed(link,v);	
	}
}

// override *follow* speed, comments as above
float qpo_CFM_followSpeed(LINK* link, VEHICLE* v,  VEHICLE* ahead[])
{
	float vDist		= qpg_VHC_distance(v); 
	float stopPoint = qpg_LNK_length(link) * SLOW_DOWN_LOCATION; 
	float vSafeStop = qpg_CFM_stoppingDistance(v); 
	
	if(qpg_VHC_stopped(v)) return 0.0; 

	if(qpg_CFG_simulationTime() < START_TIME || qpg_CFG_simulationTime() > END_TIME)
		return qpg_CFM_followSpeed(link, v, ahead);	

	
	if(strcmp(qpg_LNK_name(qpg_VHC_link(v)),SLOW_DOWN_LINK) != 0) 
		return qpg_CFM_followSpeed(link, v, ahead);	

	if(vDist < stopPoint)
	{	
		return qpg_CFM_followSpeed(link, v, ahead);	
	}
	else if(vDist > stopPoint + vSafeStop)
	{		
		return qpg_CFM_followSpeed(link, v, ahead);	
	}
	else 
	{
		return slowDownSpeed(link,v);	
	}
}


// new function to slow down and stop the vehcicle
float slowDownSpeed(LINK* link, VEHICLE* v)
{
	float speed		= qpg_VHC_speed(v);
	float timeStep	= qpg_CFG_timeStep();
    float acc;
    float toStop;

	float vDist		= qpg_VHC_distance(v); // distance to the end of the link
	float stopPoint = qpg_LNK_length(link) * SLOW_DOWN_LOCATION; // 50% down the link
	
    
	// how far left to travel
	toStop = MAX(0.5F, vDist - stopPoint);
    
	// acceleration to apply to stop at this point
    acc  = qpg_CFM_constrainedAcceleration(v, link, 0.0, toStop);

	//forzar a detenerce en la pista de mas a la derecha
	qps_VHC_laneChange (v, -1);


	// change in speed to apply to current speed 
    speed = MAX(0.5, speed + timeStep * acc);
    
	// if at the stoping point mark the vehicle as stopped
    if ((toStop <= 0.5F || toStop < speed * timeStep) )
    {
		qps_VHC_stopped(v, PTRUE); 
		speed = 0.0;
	}
    
    return speed;
}


// check for stoped vehicles and restartthem at a given time or
// when a fag is set/un set etc. lots of ways to do this, lots of 
// differnet qpx you can use, be aware this fucntion is quite slow  	
/*void  qpx_LNK_vehicleTimeStep(LINK* link, VEHICLE* vehicle)
{
	// check link
	if(strcmp(qpg_LNK_name(qpg_VHC_link(vehicle)),SLOW_DOWN_LINK) != 0) return;
	
	// check time bounds 
	if(qpg_CFG_simulationTime() <= END_TIME) return;

	// un-stop the vehicle
	if(qpg_VHC_stopped(vehicle)) 
	{
		qps_VHC_stopped(vehicle, PFALSE);  
	}
}
*/