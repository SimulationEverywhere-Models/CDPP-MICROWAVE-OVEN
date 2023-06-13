/*******************************************************************
*
* DESCRIPTION: The Atomic Model of power driver.
* It keeps the power (heat) on the configured level during cooking
* This atomic model has the following two inputs:
* <power_set> is used to turn on/off the heating system.
* <powerlevel_in> is used to adjust the level of the power, 
* indicated as 1, 2, 3 ( low, medium, high)
* There is one output generated from this atomic model.
* <heatlevel_out> indicate the level of the power during it is cooking, 
* but if it is not cooking, it is shown zero. All heat level is generated 
* from the model as 0 (uncooking) and 1,2,3(cooking)
* 
*
*******************************************************************/

/** include files **/
#include "powerDriver.h" // class PowerDrv
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* PowerDrv constructor
* Description: creates an initial atomic model of the PowerDrv 
********************************************************************/
PowerDrv::PowerDrv( const string &name )
: Atomic( name )
, power_set( addInputPort( "power_set" ) )
, powerlevel_in( addInputPort( "powerlevel_in" ) )
, heatlevel_out( addOutputPort( "heatlevel_out" ) )
{
}

/*******************************************************************
* PowerDrv init function
* Description: This method is invoked when simulation starts.  It 
* simply sets heatlevel to 1.
********************************************************************/
Model &PowerDrv::initFunction()
{
	this->heatlevel = 1;

	// Activate the output function so the minute is displayed
	// right away
	holdIn( passive, Time::Zero );

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method handles external events coming from
* any of the three input ports.
********************************************************************/
Model &PowerDrv::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == power_set )
	   {

	   if( msg.value() == true ) 
		{
		// time_set was pressed.  Go active until 
		// an external event comes in.
		holdIn( active, Time::Inf );
		holdIn( this->state(), Time::Zero); 
		}
	   else {
		// time_set was released.  Go passive
		// until an external event comes in.

		passivate();
		holdIn( this->state(), Time::Zero); 
		}
	   }
	else if( msg.port() == powerlevel_in )
	   {
		if (this->state() == passive)
 			this->heatlevel = msg.value();
	   }

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: The internal function simply consists in keeping the
* model in the current state until an external event comes in. 
********************************************************************/
Model &PowerDrv::internalFunction( const InternalMessage & )
{
	holdIn ( state(), Time::Inf );
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This routine sens the value of the minute variable
* to the <time_minutes> output port.
********************************************************************/
Model &PowerDrv::outputFunction( const InternalMessage &msg )
{
	if (this->state ()== active)
	{
	// cooking state, output the powerlevel)
		sendOutput( msg.time(), heatlevel_out, this->heatlevel ) ;
	}
	else 
	{
	//uncooking state
		sendOutput( msg.time(), heatlevel_out, 0) ;
	}


	return *this ;
}
