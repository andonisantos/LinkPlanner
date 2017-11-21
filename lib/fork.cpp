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
	int process = min(ready, space);

	if (process <= 0) return false;

	signal_value_type type = inputSignals[0]->getType();

	switch(type) {
		case BinaryValue:
			for (int i = 0; i < process; i++)
			{
				t_binary inSignal;
				inputSignals[0]->bufferGet(&inSignal);
				outputSignals[0]->bufferPut((t_real)(inSignal));
				outputSignals[1]->bufferPut((t_real)(inSignal));
			}
			break;
		case RealValue:
			for (int i = 0; i < process; i++)
			{
				t_real inSignal;
				inputSignals[0]->bufferGet(&inSignal);
				outputSignals[0]->bufferPut((t_real)(inSignal));
				outputSignals[1]->bufferPut((t_real)(inSignal));
			}
			break;
		default: std::cout << "Fork: Invalid Input Signal\n";
	}
	return true;
}

