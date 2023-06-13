/*******************************************************************
*
*  DESCRIPTION: Header File for the atomic Model of cooking minute 
*  register.
*
*
*******************************************************************/

#ifndef __MINCOOKREGISTER_H
#define __MINCOOKREGISTER_H

#include <list>
#include "atomic.h"     // class Atomic

// MinCookReg class

class MinCookReg : public Atomic
{
public:
	// Constructor
	MinCookReg( const string &name = "MinCookReg" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &time_set;
	const Port &minutes;

	// output port
	Port &time_minutes;

	// value of the minutes register
	int minute;

};	// class MinCookReg

// ** inline ** // 
inline
string MinCookReg::className() const
{
	return "MinCookReg" ;
}

#endif   //__MINCOOKREGISTER_H
