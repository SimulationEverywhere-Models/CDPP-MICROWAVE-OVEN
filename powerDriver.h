/*******************************************************************
*
*  DESCRIPTION: Header File for the atomic Model of power driver 
* 
*
*******************************************************************/

#ifndef __POWERDRIVER_H
#define __POWERDRIVER_H

#include <list>
#include "atomic.h"     // class Atomic

// PowerDrv class

class PowerDrv : public Atomic
{
public:
	// Constructor
	PowerDrv( const string &name = "PowerDrv" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &power_set;
	const Port &powerlevel_in;

	// output port
	Port &heatlevel_out;

	// value of the heat level
	Value heatlevel;

};	// class PowerDrv

// ** inline ** // 
inline
string PowerDrv::className() const
{
	return "PowerDrv" ;
}

#endif   //__POWERDRIVER_H
