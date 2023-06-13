/*******************************************************************
*
* DESCRIPTION: The Atomic Model of cooking time counter.
* It keeps the cooking time that is displayed on the panel
* when the microwave oven is under the configuration of cook time and
* output the remaining time during it is cooking. It also accept the 
* the interrupt events such as stop and clear so that we can stop and cancel 
* the cooking transaction.
* This atomic model has the following six inputs:
* <phase_set> is used to adjust the cooking time.
* <time_minutes> is used to indicate the minute of the cooking time 
* (from 0 to 59)
* <time_seconds> is used to indicate the second of the cooking time
* (from 0 to 59)
* <start> is used to start cooking
* <stop> is used to stop cooking
* <clear> is used to clear all information and cancel the current cooking task 
* There are three output generated from this atomic model.
* <time_of_cook> is used to tell the remaining time of the cooking session
* <power_switch> is used to tell the power driver should be on or off
* <beep> is used to tell beep when cooking is finished or cancelled
*
*******************************************************************/

/** include files **/
#include "timeCookCounter.h"  // class TimeCookCounter
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* TimeCookCounter constructor
* Description: This method creats an initial TimeCookCounter model
********************************************************************/
TimeCookCounter::TimeCookCounter( const string &name )
: Atomic( name )
, time_minutes( addInputPort( "time_minutes" ) )
, time_seconds( addInputPort( "time_seconds" ) )
, phase_set ( addInputPort( "phase_set" ) )
, start ( addInputPort( "start" ) )
, stop ( addInputPort( "stop" ) )
, clear ( addInputPort( "clear" ) )
, time_of_cook( addOutputPort( "time_of_cook" ) )
, power_switch( addOutputPort( "power_switch" ) )
, beep( addOutputPort( "beep" ) )
, one_second( 0, 0, 1, 0 )
, idle ( 0 )
, ready ( 1 )
, busy ( 2 )
{
}

/*******************************************************************
* TimeCookCounter init function
* Description: This method is invoked when simulation starts.
* This method initate the variables and state (passive).
********************************************************************/
Model &TimeCookCounter::initFunction()
{
	this->time.seconds( 0 );
	this->time.minutes( 0 );
	this ->remainingTime = 0;
	this->state( passive );
	this->status = 0;
	holdIn( passive, Time::Zero );
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method handles external events coming from any
* of the six input ports. There are three state: idle, ready, and busy
* Events for state transition from idle to ready: phase_set
* Events for state transition from ready to busy: start
* Events for state transition from busy to ready: stop
* Events for state transition from busy/ready to idle: clear
* Events for remaining state for ready to ready: time_seconds and 
* time_minutes
********************************************************************/
Model &TimeCookCounter::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == time_seconds )
	   {
		if (this->status == ready)
		  {
			this->time.seconds( msg.value() );
			this->remainingTime = this->time.minutes()*60 + this->time.seconds();
			holdIn( this->state(), Time::Zero );
		  }
	   }
	else if( msg.port() == time_minutes )// the port is time_minutes
	   {
		if (this->status == ready)
		  {
			this->time.minutes( msg.value() );
			this->remainingTime = this->time.minutes()*60 + this->time.seconds();
			holdIn( this->state(), Time::Zero );
		  }	   
	   }
	else if ( msg.port() == start )
	   {
		if ((this->status == ready) && (this->remainingTime > 0))
		  {
			this->status = busy;
			this->state(active);
			sendOutput( msg.time(), power_switch, 1 );
			holdIn( this->state(), Time::Zero );
		  }
		
	   }
	else if ( msg.port() == stop )
	   {
		if ((this->status == busy) && (this->remainingTime > 0))
		  {
			this->status = ready;
			this->state(passive);
			holdIn( this->state(), Time::Zero );
			sendOutput( msg.time(), power_switch, 0 );
		  } 
		else this->status = idle;
	   }
	else if ( msg.port() == clear )
	   {
		this->status = idle;
		this ->remainingTime = 0;
		this->state(passive);
		holdIn( this->state(), Time::Zero );
	   }
	else if ( msg.port() == phase_set )
	   {
		if (msg.value() == true)
		{
		if (this->status == idle)
		  {
			this->status = ready;
			this ->remainingTime = 0;
			this->time.seconds( 0 );
			this->time.minutes( 0 );
			holdIn( this->state(), Time::Zero );
		  } 
            } 
		else 	
		{
		this ->remainingTime = 0;
		this->time.seconds( 0 );
		this->time.minutes( 0 );
		}
	   }

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: The internal function descreases one second the cooking time
* if the model is in the busy state. In the other states we
* simply wait for the next external event.
********************************************************************/
Model &TimeCookCounter::internalFunction( const InternalMessage & )
{
	if (this->status == busy)
	   {
	   if (this->remainingTime > 0)
		{
		   holdIn( this->state(), one_second );
	   	   this->remainingTime --;
		   if (this->remainingTime == 0)
			{
				this->state(passive);
				this->status = idle;
				holdIn( this->state(), Time::Zero );
			}		

		   }
	   } 
	else holdIn( this->state(), Time::Inf );
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This method outputs the remaining time to the <time_of_cook>
* port and beep on the <beep> port when the cooking is finished and cancelled
********************************************************************/
Model &TimeCookCounter::outputFunction( const InternalMessage &msg )
{

	this->outTime = 100 * (this->remainingTime - this->remainingTime %60)/60 + this->remainingTime %60;
 	sendOutput( msg.time(), time_of_cook, this->outTime );

	if ((this->state() == passive)&&(this->status == idle)) 
	  {
		sendOutput( msg.time(), power_switch, 0 );
		sendOutput( msg.time(), beep, 1 );		
	  }

	return *this ;
}
