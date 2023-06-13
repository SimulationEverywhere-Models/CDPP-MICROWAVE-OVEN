/*******************************************************************
*
*  DESCRIPTION: Header File for the atomic Model of powerlevel 
*  register.
*
*******************************************************************/

#ifndef __POWLVLREGISTER_H
#define __POWLVLREGISTER_H

#include <list>
#include "atomic.h"     // class Atomic

// PowLvlReg class

class PowLvlReg : public Atomic
{
public:
	// Constructor
	PowLvlReg( const string &name = "PowLvlReg" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &phase_set;
	const Port &powerlevel_in;

	// output port
	Port &powerlevel_out;

	// value of the powerlevel register
	int powerlevel;

};	// class PowLvlReg

// ** inline ** // 
inline
string PowLvlReg::className() const
{
	return "PowLvlReg" ;
}

#endif   //__POWLVLREGISTER_H
