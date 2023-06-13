The file is explaining the detailed information for assignment 1.

We compiled the source code on Linux with gcc 2.95.3. The <makefile> and <register.cpp> are included in this package.

Source code (.cpp/.h files) for each of atomic models in microwave oven system:
minCookRegister.h		minCookRegister.cpp	class MinCookReg
secCookRegister.h		secCookRegister.cpp	class SecCookReg
timeCookCounter.h		timeCookCounter.cpp	class TimeCookCounter
powLvlRegister.h		powLvlRegister.cpp	class PowLvlReg
powerDriver.h			powerDriver.cpp		class PowerDrv
displayer.h			displayer.cpp		class Displayer
curTimeRegister.h		curTimeRegister.cpp	class CurTimeRegister
beepDriver.h			beepDriver.cpp		class BeepDrv

The atomic models defined in this assignment (.ma) and related input file(.ev)
minCookRegTest.ma		minCookRegTest.ev 	class MinCookReg
secCookRegTest.ma		secCookRegTest.ev	class SecCookReg
powerLvlTest.ma			powerLvlTest.ev		class PowLvlReg
timeCounterTest.ma 		timeCounterTest.ev	class TimeCookCounter
beepTest.ma			beepTest.ev		class BeepDrv
powerDrvTest.ma 		powerDrvTest.ev		class PowerDrv
curTimeRegTest.ma		curTimeRegTest.ev	class CurTimeRegister
displayTest.ma			displayTest.ev		class Displayer

The coupled models defined in this assignment (.ma) and related input file(.ev)
cookTimeTest.ma			cookTimeTest.ev
phaseRegTest.ma			phaseRegTest.ev

The system model for microwave oven including all model describe above:
microwaveoven.ma		microwaveoven.ev

The execTests.bat file includes all the atomic and coupled models test. Different testing strategies have been represented in .ev input files listed above.

To compile the source code and run tests for each model (atomic or coupled model):

1. copy the .cpp and .h files to the directory of CD++.

2. copy makefile to the directory of CD ++; edit the directory of gcc and g++ in makefile to make sure that variables are associated to the directory of gcc 2.95.3. (at least I know it does not work well under gcc 2.96)

3. type command "make" to compile them and link the object files.

4. copy execTests.bat to the same directory as file simu.exe.

5. run execTests.bat so that you can make any test for all models. 

6. You also can edit .ev file and change the input of model. Pay attention that any changes should be consistent with the definition in source code.

7. Afer you run execTests.bat, you can get the following files:
minCookRegTest.out		minCookRegTest.log
secCookRegTest.out		secCookRegTest.log
cookTimeTest.out		cookTimeTest.log
powerLvlTest.out		powerLvlTest.log
phaseRegTest.out		phaseRegTest.log
timeCounterTest.out		timeCounterTest.log
beepTest.out			beepTest.log
powerDrvTest.out		powerDrvTest.log
curTimeRegTest.out		curTimeRegTest.log
displayTest.out			displayTest.log
microwaveoven.out		microwaveoven.log
but they are not included in the package.

To indicate our testing is successully, we put the output of screen as file testingOUT into the package as well as the output file and log file of the system model, microwaveovenout,microwaveovenlog.
