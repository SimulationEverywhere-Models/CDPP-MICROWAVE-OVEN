/*******************************************************************
*
* DESCRIPTION: The Atomic Model of powerlevel register.
* It keeps the current time of the day that is displayed on the panel
* when the microwave oven is not working.
* This atomic model has the following two inputs:
* <phase_set> is used to adjust the cooking time.
* <powerlevel_in> is used to adjust the powerlevel of micrwave oven, which increments the
* current powerlevel by 1 per event. 
* The powerlevel of micrwave oven could be 1, 2, 3. If it reaches 4, then turn 
* to be 1. 1, 2, 3 indicate the powerlelvel as low, medium, and high.
* There is one output generated from this atomic model.
* <powerlevel_out> indicate the powerlevel of micrwave oven that is generated 
* from the model
* 
*
*******************************************************************/

/** include files **/
#include "powLvlRegister.h" // class PowLvlReg
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* PowLvlReg constructor
* Description: create an initial automatic PowLvlReg model
********************************************************************/
PowLvlReg::PowLvlReg( const string &name )
: Atomic( name )
, phase_set( addInputPort( "phase_set" ) )
, powerlevel_in( addInputPort( "powerlevel_in" ) )
, powerlevel_out( addOutputPort( "powerlevel_out" ) )
{
}

/*******************************************************************
* PowLvlReg init function
* Description: This method is invoked when simulation starts.   
* the default powerlevel of microwave oven is 1( low)
********************************************************************/
Model &PowLvlReg::initFunction()
{
	this->powerlevel = 1;

	// Activate the output function so the minute is displayed
	// right away
	holdIn( passive, Time::Zero );

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method handles external events coming from
* any of the two input ports.
********************************************************************/
Model &PowLvlReg::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == phase_set )
	   {

	   if( msg.value() == true ) 
		{
		// time_set was pressed. set to default level of power. 
		//  Go active until an external event comes in.
		this->powerlevel = 1;
		holdIn( active, Time::Inf );
		}
	   else {
		// time_set was released.  Go passive
		// until an external event comes in.
		passivate();
		}
	   }
	else if( msg.port() == powerlevel_in )
	   {
	   // Only increment the powerlevel if the model is in the 
	   // active phase.
	   if( state() == active )
		{
		if ( this->powerlevel == 3 )
		   this->powerlevel = 1;
		else
		  ++(this->powerlevel);

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
Model &PowLvlReg::internalFunction( const InternalMessage & )
{
	holdIn ( state(), Time::Inf );
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This method sends the value of the minute variable
* to the <powerlevel_out> output port.
********************************************************************/
Model &PowLvlReg::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), powerlevel_out, this->powerlevel ) ;
	return *this ;
}
