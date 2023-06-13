/*******************************************************************
*
*  DESCRIPTION: Header File for the atomic Model of time cook counter 
* 
*
*******************************************************************/
#ifndef __TIMECOOKCOUNTER_H
#define __TIMECOOKCOUNTER_H

#include <list>
#include "atomic.h"     // class Atomic

// TimeCookCounter class

class TimeCookCounter : public Atomic
{
public:
	// Constructor
	TimeCookCounter( const string &name = "TimeCookCounter" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &time_minutes;
	const Port &time_seconds;
	const Port &phase_set;
	const Port &start;
	const Port &stop;
	const Port &clear;


	// output port
	Port &time_of_cook;
	Port &power_switch;
	Port &beep;


	const Time one_second;
	const int idle;
	const int ready;	
	const int busy;
	int status ; //(passive): status=0: idle, status=1:ready; (active):status=2: busy




	Time time;

	// value of the time variable converted for output.
	Value outTime;

	// value of the time variable converted for output.
	int remainingTime;

};	// class TimeCookCounter

// ** inline ** // 
inline
string TimeCookCounter::className() const
{
	return "TimeCookCounter" ;
}

#endif   //__TIMECOOKCOUNTER_H
