/*******************************************************************
*
* DESCRIPTION: The Atomic Model of Current time register.
* It keeps the current time of the day that is displayed on the panel
* when the microwave oven is not working.
* This atomic model has the following three inputs:
* <time_set> is used to adjust the current time.
* <hours> is used to adjust the current hour of the day, which takes effect
* only when the <time_set> is pressed. It increases the hours by 1 per time.
* <minutes> is used to adjust the current time of minute, which increments the
* current minutes by 1 per event.
* There is one output generated from this atomic model.
* <cur_time> the current time that is generated from the model. It has the
* following format: hours*100 + minutes. Therefore, 10:23AM will be sent as
* 1023.
* Note: the hours and minutes are wrapped appropriately when necessary.
*
*
*******************************************************************/

/** include files **/
#include "curTimeRegister.h" //header file of CurTimeRegister
#include "message.h"    // header file of ExternalMessage, InternalMessage
#include "mainsimu.h"   // header file of the main simulator

/** public functions **/

/*******************************************************************
* constructor
* Description: creates an initial atomic model of CurTimeRegister
********************************************************************/
CurTimeRegister::CurTimeRegister( const string &name )
: Atomic( name )
, time_set( addInputPort( "time_set" ) )
, hours( addInputPort( "hours" ) )
, minutes( addInputPort( "minutes" ) )
, cur_time( addOutputPort( "cur_time" ) )
, one_minute(0,1,0,0)
{
}

/*******************************************************************
* initFunction
* Description: starts the simulation. Initialize the current time
* to 00:00
********************************************************************/
Model &CurTimeRegister::initFunction()
{
	this->hour = 0;
        this->minute=0;
// Invoke the output function so that the current time is displayed immediately
	holdIn( passive, Time::Zero );

	return *this ;
}

/*******************************************************************
* externalFunction
* Description: This method handles external events coming from
* any of the three input ports.
********************************************************************/
Model &CurTimeRegister::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == time_set )
	{

	   if( msg.value() == true )
		{
		// time_set was pressed.  Change to active state. Keep active until
		// another external event comes in.
		 holdIn( active, Time::Inf );
		}
	   else {
		 // time_set was released. Change to passive state until
	  	 // another external event comes in.
		holdIn( passive, one_minute );
		}
	}
	else if( msg.port() == hours)
	{
	   // Only increment the hour if the model is in the
	   // active phase.
	   if( state() == active )
		{
		if ( this->hour == 23 )
		   this->hour = 0;
		else
		  ++(this->hour);

		// Invoke the output function so that the new time 
		// can be seen immediately.
		holdIn( active, Time::Zero );
		}
	   }
 	else if( msg.port() == minutes)
	   {
	   // Simply increase the minute by one when the model is 
	   //in active state
	   if( state() == active )
		{
		if ( this->minute == 59 )
		   this->minute = 0;
		else
		  ++(this->minute);

   		// Invoke the output function so that the new time 
		//can be seen immediately.
		holdIn( active, Time::Zero );
		}
 
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: The internal method increments the minute
* if the model is in the passive state. In the active state we
* simply wait for the next external event.
********************************************************************/
Model &CurTimeRegister::internalFunction( const InternalMessage & )
{
  //	holdIn ( state(), Time::Inf );
	if ( state() == passive )
	   {

	   if( this->minute == 59)
		{
   		 this->minute = 0;
                 this->hour++;
                 if (this->hour==24)
                 this->hour=0;
		}
	   else
		++(this->minute);

	   // schedule the next incrementation of the minute
	   // value one minute from now
	   holdIn( passive, one_minute );
	   }
	else
	   // wait for the next external event
	   holdIn( active, Time::Inf );

	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This method sends the value of current time
* to the <cur_time> output port.
********************************************************************/
Model &CurTimeRegister::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), cur_time, this->hour*100+this->minute ) ;
	return *this ;
}
