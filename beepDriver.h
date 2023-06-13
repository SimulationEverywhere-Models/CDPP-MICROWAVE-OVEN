/*******************************************************************
*
*  DESCRIPTION: Header File for the atomic model of beep driver
*  
*
*******************************************************************/

#ifndef __BEEPDRIVER_H
#define __BEEPDRIVER_H

#include <list>
#include "atomic.h"     // class Atomic

// BeepDrv class

class BeepDrv : public Atomic
{
public:
	// Constructor
	BeepDrv( const string &name = "BeepDrv" );

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

	// input ports
	const Port &beep_in;

	// output port
	Port &sound_out;

	const Time onesecond;

	int counter;



};	// class BeepDrv

// ** inline ** // 
inline
string BeepDrv::className() const
{
	return "BeepDrv" ;
}

#endif   //__BEEPDRIVER_H
