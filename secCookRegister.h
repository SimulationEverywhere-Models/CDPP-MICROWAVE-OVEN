/*******************************************************************
*
*  DESCRIPTION: Header File for the atomic Model of cooking second 
*  register.
*
*******************************************************************/

#ifndef __SECCOOKREGISTER_H
#define __SECCOOKREGISTER_H

#include <list>
#include "atomic.h"     // class Atomic

// SecCookReg class

class SecCookReg : public Atomic
{
public:
	// Constructor
	SecCookReg( const string &name = "SecCookReg" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &time_set;
	const Port &seconds;

	// output port
	Port &time_seconds;

	// one minute
	const Time one_second;

	// value of the seconds register
	int second;



};	// class SecCookReg

// ** inline ** // 
inline
string SecCookReg::className() const
{
	return "SecCookReg";
}

#endif   //__SECCOOKREGISTER_H
