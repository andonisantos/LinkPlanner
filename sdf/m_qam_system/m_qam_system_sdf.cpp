# include "netxpto_20180118.h"

# include "m_qam_transmitter_20180118.h"
# include "homodyne_receiver_20171203.h"
# include "bit_error_rate_20171810.h"
# include "sink_20180118.h"

int main(){

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	t_integer numberOfBitsGenerated(100000);
	t_integer samplesPerSymbol(16);
	t_integer pLength = 5;
	t_real bitPeriod = 1.0 / 50e9;
//	t_real bitPeriod = 20e-12;
	t_real rollOffFactor_shp = 0.3;
	t_real rollOffFactor_out = 0.3;
	//vector<t_iqValues> iqAmplitudeValues = { { -1, 0 },{ 1, 0 } };
	t_real signalOutputPower = -50;
	PulseShaperFilter shaperFilter = RootRaisedCosine;
	PulseShaperFilter outputFilter = RootRaisedCosine;


	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	int numberOfBitsReceived(-1);
	//int numberOfBitsGenerated = 10;
	//double bitPeriod = 1.0 / 50e9;

	int prbsPatternLength = 5;

	//vector<t_iqValues> iqAmplitudeValues = { { 1.0, 1.0 },{ -1.0, 1.0 },{ 1.0, -1.0 },{ -1.0, -1.0 } };
	vector<t_iqValues> iqAmplitudeValues = { { -3.0, -3.0 },{ -3.0, -1.0 },{ -3.0, 1.0 },{ -3.0, 3.0 },{ -1.0, -3.0 },{ -1.0, -1.0 },{ -1.0, 3.0 },{ -1.0, 1.0 },{ 3.0, -3.0 },{ 3.0, -1.0 },{ 3.0, 3.0 },{ 3.0, 1.0 },{ 1.0, -3.0 },{ 1.0, -1.0 },{ 1.0, 3.0 },{ 1.0, 1.0 } };
	
	t_iqValues maxAmplitude = iqAmplitudeValues[0].real();
	for (unsigned int i = 1; i < iqAmplitudeValues.size(); i++)
	{
		if (iqAmplitudeValues[i].real() > maxAmplitude.real()) { maxAmplitude = iqAmplitudeValues[i]; };
	}
	
	for (unsigned int i = 0; i < iqAmplitudeValues.size(); i++)
	{
		iqAmplitudeValues[i] = iqAmplitudeValues[i]/maxAmplitude.real();
	}


	//int m = 4;
	
	//double rollOffFactor = 0.3;

	//int samplesPerSymbol = 16;
	double symbolPeriod = bitPeriod / samplesPerSymbol;

	//t_real signalOutputPower_dBm = -20; 
	t_real localOscillatorPower_dBm = 0; 
	t_real localOscillatorPhase = 0;
	//array<t_complex, 4> transferMatrix = { { 1 / sqrt(2), 1 / sqrt(2), 1 / sqrt(2), -1 / sqrt(2)} };
	t_real responsivity = 1;
	t_real amplification = 1e3;
	t_real noiseAmplitude = 1e-6;
	SeedType seedType = RandomDevice;
	array<int, 2> seedArray = { 1, 2 };
	double amplitude = amplification * sqrt(pow(10, localOscillatorPower_dBm/10)*1e-3*pow(10, signalOutputPower/10)*1e-3);

//	INITIAL SAMPLES TO IGNORE IN THE SAMPLER
//	Required to set this value due to the Pulse Shaper influence
	t_integer samplesToSkip = 2 * 8 * samplesPerSymbol; //+ floor(samplesPerSymbol / 2);
//	t_integer samplesToSkip = 8*samplesPerSymbol;	//+ floor(samplesPerSymbol / 2);
//	8 is the number of samples used by the filter


	t_real confidence = 0.95;
	t_integer midReportSize = 0;

	// The bufferLength was initially set to 13.
	// The decoder block currently malfunctions if this buffer is set to
	// a number lower than the number of ignore samples.
	t_integer bufferLength = 512;
	
	//double clockPeriod = symbolPeriod;
	//double samplingPeriod = 16;
	
	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S0{ "S0.sgn" };
	S0.setBufferLength(bufferLength);

	OpticalSignal S1("S1.sgn");
	S1.setBufferLength(bufferLength);

	Binary S2{ "S2.sgn" };
	S2.setBufferLength(bufferLength);

	Binary S3{ "S3.sgn" };
	S3.setBufferLength(bufferLength);

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	MQamTransmitter B1{ vector<Signal*> { }, vector<Signal*> { &S1, &S0 } };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower_dBm(signalOutputPower);
	B1.setMode(Random);
	//B1.setMode(PseudoRandom);
	//B1.setMode(DeterministicAppendZeros);
	B1.setBitStream("01001011");
	B1.setBitPeriod(bitPeriod);
	B1.setPatternLength(prbsPatternLength);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setRollOffFactor(rollOffFactor_shp);
	B1.setSaveInternalSignals(true);
	B1.setSeeBeginningOfImpulseResponse(false);
	B1.setPulseShaperFilter(shaperFilter);
//	B1.usePassiveFilterMode(true);
	B1.setImpulseResponseFilename("pulse_shaper.imp");
	B1.setIqAmplitudes(iqAmplitudeValues);
	//B1.setM(m);

	HomodyneReceiver B2{ vector<Signal*> {&S1}, vector<Signal*> {&S2} };
	B2.setIqAmplitudes(iqAmplitudeValues);
	B2.setLocalOscillatorOpticalPower_dBm(localOscillatorPower_dBm);
	B2.setLocalOscillatorPhase(localOscillatorPhase);
	//B2.setSamplerOpticalPower_dBm(signalOutputPower_dBm);
	//B2.setTransferMatrix(transferMatrix);
	B2.setResponsivity(responsivity);
	B2.setAmplification(amplification);
	B2.setNoiseAmplitude(noiseAmplitude);
	B2.setSeedType(seedType);
	B2.setSeeds(seedArray);
	B2.setSamplesToSkip(samplesToSkip);
	//B2.setPosReferenceValue(0);
	//B2.setNegReferenceValue(0);
	B2.setSaveInternalSignals(true);
	//B2.setCutoffFrequency(cutoffFrequency);
	B2.setSamplingPeriod(symbolPeriod/samplesPerSymbol);
//	B2.setClockPeriod(symbolPeriod);
	B2.setRollOffFactor(rollOffFactor_out);
	B2.setFilterType(outputFilter);
	B2.usePassiveFilterMode(true);
	B2.setImpulseResponseFilename("out_filter.imp");
	B2.setFirstFilteredValueToBeSaved(samplesToSkip);
	B2.setAmplitude(amplitude);




	//With BER measurement
	BitErrorRate B3{ vector<Signal*> { &S2, &S0 }, vector<Signal*> { &S3 } };
	B3.setConfidence(confidence);
	B3.setMidReportSize(midReportSize);

	Sink B4{ vector<Signal*> { &S3 }, vector<Signal*> {} };
	B4.setNumberOfSamples(numberOfBitsReceived*samplesPerSymbol);
	B4.setDisplayNumberOfSamples(true);

	/*MQamTransmitter B1{ vector<Signal*> {}, vector<Signal*> { &S1, &S2 } };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower_dBm(signalOutputPower_dBm);
	//B1.setMode(PseudoRandom);
	B1.setMode(DeterministicAppendZeros);
	B1.setBitStream("010");
	B1.setBitPeriod(bitPeriod);
	B1.setPatternLength(pLength);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setRollOffFactor(rollOffFactor);
	B1.setSaveInternalSignals(true);
	B1.setSeeBeginningOfImpulseResponse(true);

	//Without BER measurement
	//Sink B3{ vector<Signal*> { &S0 }, vector<Signal*> {} };
	//B3.setNumberOfSamples(numberOfBitsReceived*samplesPerSymbol);
	//B3.setDisplayNumberOfSamples(true);


	//Sink B4{ vector<Signal*> { &S2 }, vector<Signal*> {} };
	//B4.setNumberOfSamples(numberOfBitsReceived*samplesPerSymbol);
	//B4.setDisplayNumberOfSamples(true);

	Sink B3{ vector<Signal*> { &S2 }, vector<Signal*> {} };
	//B3.setDisplayNumberOfSamples(true);*/

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}
