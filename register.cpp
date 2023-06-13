/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico

#include "minCookRegister.h" // class MinCookReg
#include "secCookRegister.h" // class SecCookReg
#include "timeCookCounter.h" 	// class TimeCookCounter
#include "powLvlRegister.h" 	// class PowLvlReg
#include "powerDriver.h" 	// class PowerDrv
#include "displayer.h" 	// class Displayer
#include "curTimeRegister.h" 	// class CurTimeRegister
#include "beepDriver.h" 	// class BeepDrv



void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;

	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<MinCookReg>() , "MinCookReg" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<SecCookReg>() , "SecCookReg" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<TimeCookCounter>() , "TimeCookCounter" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<PowLvlReg>() , "PowLvlReg" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<PowerDrv>() , "PowerDrv" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Displayer>() , "Displayer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CurTimeRegister>() , "CurTimeRegister" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BeepDrv>() , "BeepDrv" ) ;


}
