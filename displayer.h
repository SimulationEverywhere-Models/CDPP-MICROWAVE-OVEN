#ifndef __DISPLAYER_H
#define __DISPLAYER_H

#include <list>
#include "atomic.h"     // class Atomic

//Displayer  class

class Displayer : public Atomic
{
public:
	// Constructor
   Displayer( const string &name = "Displayer" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &day_time;  //the current time of the day
	const Port &counter_time;  //the remaining time of a heating job

	// output ports
	Port &cur_time;  //the current time of the day
	Port &rem_time;  //the remaining time of a heating job

	// the time to be sent (current time or remaining time)
	Value out_time;
	const Time ten_sec;

};	// end of Displayerer

// ** inline ** // 
inline
string Displayer::className() const
{
	return "Displayer" ;
}

#endif   //__DISPLAYER_H

