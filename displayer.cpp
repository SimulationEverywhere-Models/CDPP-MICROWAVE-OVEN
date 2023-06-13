/*******************************************************************
*
* DESCRIPTION: The Atomic Model of Displayer.
* It accepts the current time of the day or the remaining time of a heating job
* and then send them to the appropriate output ports.
* The time that is going to be sent is in the format of HHMM. E.g., 12:23 will
* be sent as 1223.
* There are two input ports which are discribed as follows:
* <day_time> The time of the day which is also in the format of HHMM.
* <counter_time> the remaing time of a heating job which in the format as
* MMSS. E.g. 8 minutes and 20 seconds will be represented as 820.
* There are two output ports as follows:
* <cur_time> the current time that is generated from the model. It has the
* following format: hours*100 + minutes. Therefore, 10:23AM will be sent as
* 1023.
* <rem_time> the remaining time of a heating job. the same format as 
*<counter_time>
*
*
*******************************************************************/

/** include files **/
#include "displayer.h" // The header file
#include "message.h"    // header file of ExternalMessage, InternalMessage
#include "mainsimu.h"   // header file of the main simulator

/** public functions **/

/*******************************************************************
* constructor
* Description: creates an initial atomic model of Displayer
********************************************************************/
Displayer::Displayer( const string &name )
: Atomic( name )
, day_time( addInputPort( "day_time" ) )
, counter_time( addInputPort( "counter_time" ) )
, cur_time( addOutputPort( "cur_time" ) )
, rem_time( addOutputPort( "rem_time" ) )
, ten_sec(0,0,10,0)
{
}

/*******************************************************************
* initFunction
* Description: starts the simulation.
********************************************************************/
Model &Displayer::initFunction()
{
	this->out_time = 0;
	//Stay in passive state until an external event comes
	holdIn( passive, Time::Inf );
	return *this ;
}

/*******************************************************************
* externalFunction
* Description: This method handles external events coming from
* any of the two input ports.
********************************************************************/
Model &Displayer::externalFunction( const ExternalMessage &msg )
{
      out_time=msg.value();
	if( msg.port() == day_time )
	   {
        if (state()==passive) //only display the current time when in passive state
        {
          this->sendOutput( msg.time(), cur_time, this->out_time );
        }
	   }
	else if( msg.port() == counter_time)
	   {
        if (out_time>0)
        {
          holdIn(active, Time::Zero); //change to active immediately
          this->sendOutput( msg.time(), rem_time, this->out_time );
        }  
        else //the heating job is finished or cleared
          holdIn(passive, ten_sec); //change to passive for 10 seconds
		}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: The internal function simply consists in keeping the
* model in the current state until an external event comes in.
********************************************************************/
Model &Displayer::internalFunction( const InternalMessage & )
{
	holdIn ( state(), Time::Inf );
	return *this;
}

Model &Displayer:: outputFunction( const InternalMessage &msg)
{
	return *this;
}

