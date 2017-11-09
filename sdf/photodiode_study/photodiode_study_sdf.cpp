
#include<iostream>

#include "netxpto.h"

#include "local_oscillator.h"
#include "photodiode.h"
#include "sink.h"

using namespace std;


int main()
{
	// #########################################################################
	// ######################## System Input Parameters ########################
	// #########################################################################

	// General Configuration
	int numberOfBitsGenerated(100);
	int samplesPerSymbol(16);
	double bitPeriod = 1.0E-9;
	//double wavelength = 1.55e-6;
	int bufferLength = 512;

	// Local Oscillator
	double localOscillatorPhase = 0;
	double localOscillatorPower = 1e-3;




	// #########################################################################
	// ################ Signals Declaration and Inicialization #################
	// #########################################################################

	OpticalSignal S0("S0.sgn");
	S0.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S1("S1.sgn");
	S1.setBufferLength(bufferLength);




	// #########################################################################
	// ################# Blocks Declaration and Inicialization #################
	// #########################################################################

	LocalOscillator B0{ vector<Signal*> {}, vector<Signal*> {&S0} };
	B0.setOpticalPower(localOscillatorPower);
	B0.setPhase(localOscillatorPhase);
	B0.setSamplingPeriod(bitPeriod / samplesPerSymbol);
	B0.setSymbolPeriod(bitPeriod);

	Photodiode B1{ vector<Signal*> {&S0}, vector<Signal*> {&S1} };

	Sink B2{ vector<Signal*> {&S1}, vector<Signal*> {} };
	B2.setNumberOfSamples(samplesPerSymbol*numberOfBitsGenerated);
	B2.setDisplayNumberOfSamples(true);




	// #########################################################################
	// ################# System Declaration and Inicialization #################
	// #########################################################################
	
	System MainSystem{ vector<Block*> {&B0, &B1, &B2} };




	// #########################################################################
	// ############################## System Run ###############################
	// #########################################################################

	MainSystem.run();


    return 0;
}