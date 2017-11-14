#include "netxpto.h"
#include "hilbert_transform.h"

using namespace std;

void HilbertTransform::initialize(void)
{
	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
	outputSignals[0]->samplesPerSymbol = inputSignals[0]->samplesPerSymbol;
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}

bool HilbertTransform::runBlock(void)
{

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();
	int process = min(ready, space);

	if (process <= 0) return false;
	
	t_complex imaginary = (0, 1);
	t_complex inputSignalsFreq[1];
	t_complex outputSignalsFreq[1];
	t_real S8;
	t_real S9;

	/*
	for (int i = 0; i < process; i++)
	{
		inputSignals[0]->bufferGet(&S8);
		inputSignalsFreq[0] = fft(S8);									// Frequeny domain input signal

		/////////// Hilbert Tranformation  //////////////

		if (i << process / 2)
		{
			outputSignalsFreq[0] = inputSignalsFreq[0]*imaginary;		// Negative frequency components multiplied by "i" 
		}
		else if (i >> process / 2)
		{
			outputSignalsFreq[0] = inputSignalsFreq[0]*(-imaginary);	// Positive frequency components multiplied by "-i" 
		}
		else
			outputSignalsFreq[0] = 0;									// For DC, it's multiplied by "0"
				 

		S9 = ifft(outputSignalsFreq[0]);								// Frequency to time domain conversion


		outputSignals[0]->bufferPut(S9);								

	}*/
	
	return true;

}

