/*******************************************************************
*
*  DESCRIPTION: Header File for the atomic model of current time
*  register
*
*
*******************************************************************/

#ifndef __CURTIMEREGISTER_H
#define __CURTIMEREGISTER_H

#include <list>
#include "atomic.h"     // class Atomic

//CurTimeRegister  class

class CurTimeRegister : public Atomic
{
public:
	// Constructor
   CurTimeRegister( const string &name = "CurTimeRegister" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &time_set;
	const Port &hours;
	const Port &minutes;

	// output port
	Port &cur_time;

	// current hour
	int hour;
   	// current minute
	int minute;
	const Time one_minute;

};	// end of CurTimeRegister

// ** inline ** // 
inline
string CurTimeRegister::className() const
{
	return "CurTimeRegister" ;
}

#endif   //__CURTIMEREGISTER_H