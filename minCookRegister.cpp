/*******************************************************************
*
* DESCRIPTION: The Atomic Model of cooking minute register.
* It keeps the minute of the cooking time that is displayed on the panel
* when the microwave oven is under the configuration of cooking time.
* This atomic model has the following two inputs:
* <time_set> is used to adjust the cooking time.
* <minutes> is used to adjust the minute of the cooking time, which increments the
* current minutes by 1 per event. 
* The minute of the cooking time should be less than 60, If it reaches 60, then turn 
* to be zero
* There is one output generated from this atomic model.
* <time_minutes> indicate the minute of the cooking time that is generated 
* from the model
* 
*
*******************************************************************/

/** include files **/
#include "minCookRegister.h" // class MinCookReg
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* MinCookReg constructor
* Description: creates an initial atomic model of MinCookReg
********************************************************************/
MinCookReg::MinCookReg( const string &name )
: Atomic( name )
, time_set( addInputPort( "time_set" ) )
, minutes( addInputPort( "minutes" ) )
, time_minutes( addOutputPort( "time_minutes" ) )
{
}

/*******************************************************************
* MinCookReg init function
* Description: starts the simulation. Initialize the minute of cooking
* time to 0
********************************************************************/
Model &MinCookReg::initFunction()
{
	this->minute = 0;

	// Activate the output function so the minute is displayed
	// right away
	holdIn( passive, Time::Zero );

	return *this ;
}

/*******************************************************************
* externalFunction
* Description: This method handles external events coming from
* any of the two input ports.
********************************************************************/
Model &MinCookReg::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == time_set )
	   {

	   if( msg.value() == true ) 
		{
		// time_set was pressed.  Go active until 
		// an external event comes in.
		this->minute = 0;

		holdIn( active, Time::Inf );
		holdIn( this->state(), Time::Zero );
		}
	   else {
		// time_set was released.  Go passive
		// until an external event comes in.
		passivate();
		}
	   }
	else if( msg.port() == minutes )
	   {
	   // Only increment the minute if the model is in the 
	   // active phase.
	   if( state() == active )
		{
		if ( this->minute == 59 )
		   this->minute = 0;
		else
		  ++(this->minute);

		// Activate the output function immediately
		// so the new minute can be seen.
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
Model &MinCookReg::internalFunction( const InternalMessage & )
{
	holdIn ( state(), Time::Inf );
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This method sends the value of the minute variable
* to the <time_minutes> output port.
********************************************************************/
Model &MinCookReg::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), time_minutes, this->minute ) ;
	return *this ;
}
