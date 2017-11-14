#include "netxpto.h"
#include "fork.h"

using namespace std;

void Fork::initialize(void)
{
	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
	outputSignals[0]->samplesPerSymbol = inputSignals[0]->samplesPerSymbol;
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[1]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[1]->samplingPeriod = inputSignals[0]->samplingPeriod;
	outputSignals[1]->samplesPerSymbol = inputSignals[0]->samplesPerSymbol;
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}



bool Fork::runBlock(void)
{

	int ready = inputSignals[0]->ready();
	int space1 = outputSignals[0]->space();
	int space2 = outputSignals[1]->space();

	int space = min(space1, space2);
	int process = min(ready,space);

	/* The following is an alternative way of finding minimum:
	int space = (space1 <= space2) ? space1 : space2;													
	int process = (ready <= (2 * space)) ? ready : space; // equivalent to min(ready, 2 * space);*/

	if (process <= 0) return false;
	

	for (int i = 0; i < process; i++)
	{
		t_real inSignal;
		inputSignals[0]->bufferGet(&inSignal);
		outputSignals[0]->bufferPut((t_real)(inSignal));
		outputSignals[1]->bufferPut((t_real)(inSignal));
	}

	return true;

}

