/*******************************************************************
*
* DESCRIPTION: The Atomic Model of beep driver.
* It keeps the beep sound for two seconds when there is event from
* external. It won't accept any outside event during it is beeping
* This atomic model has the following one input:
* <beep_in> is used to indicate the beeper should beep.
* There is one output generated from this atomic model.
* <sound_out> is used to express the start and end of duration of beeping
* 1 is for the beginning of beeping and 0 means beeping is finished.
*
*******************************************************************/

/** include files **/
#include "beepDriver.h" // class BeepDrv
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* BeepDrv constructor
* Description: This method creats an atomic BeepDrv model
********************************************************************/
BeepDrv::BeepDrv( const string &name )
: Atomic( name )
, beep_in( addInputPort( "beep_in" ) )
, sound_out( addOutputPort( "sound_out" ) )
, onesecond( 0, 0, 1, 0 )
{
}

/*******************************************************************
* BeepDrv init function
* Description: This method is invoked when simulation starts.   
* the beeping time is zero seconds
********************************************************************/
Model &BeepDrv::initFunction()
{
	// Activate the output function so the minute is displayed
	// right away
	holdIn( passive, Time::Zero );
	counter = 0;

	return *this ;
}

/*******************************************************************
* externalFunction
* Description: This method handles external events coming from
* one input port.
********************************************************************/
Model &BeepDrv::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == beep_in)
	   {
		if (this->state () == passive)
		{
			counter=3;
			this->state(active);
			holdIn( this->state(), Time::Zero );
			sendOutput( msg.time(), sound_out, 1 ) ;
		}

	   }

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: The internal function simply consists in keeping the
* model in the active state for beeping time. 
********************************************************************/
Model &BeepDrv::internalFunction( const InternalMessage & )
{
	if (this->state() == active)
	   {
	  
		holdIn( this->state(), onesecond);
		counter --;
		if (counter == 0)
			{
		            this->state(passive);
				holdIn( this->state(), Time::Zero );
			}	
	   } 
	else holdIn( this->state(), Time::Inf );
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This routine sends 0 to the <sound_out> output port 
* to indicate the beep is off.
********************************************************************/
Model &BeepDrv::outputFunction( const InternalMessage &msg )
{
	if (this->state() == passive)
	{
		sendOutput( msg.time(), sound_out, 0 ) ;
	}

	return *this ;
}
