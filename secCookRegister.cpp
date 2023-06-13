/*******************************************************************
*
* DESCRIPTION: The Atomic Model of cooking second register.
* It keeps the second of the cooking time that is displayed on the panel
* when the microwave oven is under the configuration of cook time.
* This atomic model has the following two inputs:
* <time_set> is used to adjust the cooking time.
* <seconds> is used to adjust the second of the cooking time, which increments the
* current seconds by 1 per event. 
* The second of the cooking time should be less than 60, If it reaches 60, then turn 
* to be zero
* There is one output generated from this atomic model.
* <time_seconds> indicate the second of the cooking time that is generated 
* from the model
* 
*
*******************************************************************/

/** include files **/
#include "secCookRegister.h"// class SecCookReg
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* SecCookReg constructor
* Description: creates an initial atomic model of SecCookReg
********************************************************************/
SecCookReg::SecCookReg( const string &name )
: Atomic( name )
, time_set( addInputPort( "time_set" ) )
, seconds( addInputPort( "seconds" ) )
, time_seconds( addOutputPort( "time_seconds" ) )
{
}

/*******************************************************************
* SecCookReg init function
* Description: starts the simulation. Initialize the second of cooking
* time to 0
********************************************************************/
Model &SecCookReg::initFunction()
{
	this->second = 0;

	// Activate the output function so the second value is 
	// displayed right away
	holdIn( passive, Time::Zero );

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method handles external events coming from
* any of the two input ports.
********************************************************************/
Model &SecCookReg::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == time_set )
	   {

	   if( msg.value() == true ) 
		{
		// <time_set> was pressed
		this->second = 0;

		holdIn( active, Time::Inf );
		holdIn( this->state(), Time::Zero );
		}
	   else {
		// <time_set> was released.  Activate the internal
		// transition function in one second.
		passivate();
		}
	   }
	else if( msg.port() == seconds )
	   {
	   // Only increment the second if the model is in the 
	   // active phase.
	   if( state() == active )
		{
		if( this->second == 59 )
		   this->second = 0;
		else
		  ++(this->second);

		// Activate the output function immediately
		// so the new second can be seen.
		holdIn( active, Time::Zero );
		}
	   }
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: The internal function simply consists in keeping the
* model in the current state until an external event comes in.
********************************************************************/
Model &SecCookReg::internalFunction( const InternalMessage & )
{
	holdIn ( state(), Time::Inf );
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This method sends the value of the second variable
* to the <time_seconds> output port.
********************************************************************/
Model &SecCookReg::outputFunction( const InternalMessage &msg )
{
	// send the second value
	sendOutput( msg.time(), time_seconds, this->second ) ;
	return *this ;
}
