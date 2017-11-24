#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>
#include <string>

#include "netxpto.h"
#include "sampler_20171116.h"


void Sampler::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSymbolPeriod());
}


bool Sampler::runBlock(void) {

	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSymbolPeriod());
	numberOfInputSignals = inputSignals.size();

	bool alive{ false };

	// Sampler with only one input signal (internal clock), only works with an integer number of samplesPerSynbol
	if (numberOfInputSignals == 1) {
		int ready = inputSignals[0]->ready();
		if (getSamplesToSkip() > 0) {
			if (getSamplesToSkip() > inputSignals[0]->getBufferLength()) {
				cout << "samplesPerSymbol>bufferLength" << endl;
				inputSignals[0]->setInPosition(inputSignals[0]->getOutPosition());
				setSamplesToSkip(getSamplesToSkip() % inputSignals[0]->getBufferLength());
			}
			else {
				int process = min(ready, getSamplesToSkip());
				for (int k = 0; k < process; k++) {
					t_real in;
					inputSignals[0]->bufferGet(&in);
				}
				setSamplesToSkip(0);
				alive = true;
			}

		}

		ready = inputSignals[0]->ready();
		int space = outputSignals[0]->space();
		int process = min(ready, space);

		if (process == 0) return alive;

		int samplesPerSymbol = (int)inputSignals[0]->getSamplesPerSymbol();
		for (int k = 0; k < process; k++) {
			t_real in;
			inputSignals[0]->bufferGet(&in);
			if (count % samplesPerSymbol == 0) {
				outputSignals[0]->bufferPut((t_real)in);
			}
			count++;
		}
	}
	/*	//Sampler with external clock
		else {

			int ready = inputSignals[0]->ready();
			int space = outputSignals[0]->space();
			int process = min(ready, space);

			if (process <= 0) return false;

			t_real inClock;
			t_real inSignal;

			for (int k = 0; k < process; k++) {

				inputSignals[1]->bufferGet(&inClock);
				inputSignals[0]->bufferGet(&inSignal);

				if (inClock == 1.0) {

					outputSignals[0]->bufferPut((t_real)inSignal);
				}

			}

			return true;
		}*/
	return alive;
}
