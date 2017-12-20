#include "netxpto.h"
#include "alice_qkd.h"

AliceQKD::AliceQKD(vector<Signal*> &inputSignal, vector <Signal*> &outputSignal) : SuperBlock(inputSignal, outputSignal) {

	//t_real clock_value;
	//inputSignal[0]->bufferGet(&clock_value);
	//outputSignal[0]->bufferPut(clock_value);

	numberOfInputSignals = (int) inputSignal.size();
	numberOfOutputSignals = (int) outputSignal.size();

	//signal_value_type sType = outputSignals[0]->getValueType();

	B1.initializeBlock(vector<Signal*>{inputSignals[1]}, vector<Signal*>{&S1, &S2});
	B2.initializeBlock(vector<Signal*>{&S1}, vector<Signal*>{&S3});
	B4.initializeBlock(vector<Signal*>{&S2}, vector<Signal*>{});
	B3.initializeBlock(vector<Signal*>{&S3}, vector<Signal*>{&S4});
	B5.initializeBlock(vector<Signal*>{inputSignal[0], &S4}, vector<Signal*>{&CLK_A, &S5});

	setModuleBlocks({ &B1 , &B2, &B4, &B3 , &B5});

}

//Basic configuration
void AliceQKD::set(int opt) {

	if (opt == 0) {
		setNumberOfSamplesPerSymbol(16);
		setIqAmplitudes({ { -45.0,0.0 },{ 0.0,0.0 },{ 45.0,0.0 },{ 90.0,0.0 } });
		setSaveInternalSignals(true);
		setNumberOfSamples(1000);
	}

	return;
}