// Transmissão de um sinal binário usando apenas 1 base.

#include "netxpto.h"

#include "m_qam_transmitter.h"
#include "local_oscillator.h"
#include "optical_hybrid.h"
#include "photodiode.h"
#include "difference.h"
#include "sampler.h"
#include "real_to_complex.h"
//#include "ti_amplifier.h"
#include "ideal_amplifier.h"
#include "sink.h"



//# include "i_homodyne_receiver.h"
//# include "bit_error_rate.h"
//# include "balanced_beam_splitter.h"
//# include "testblock.h"
//# include "bit_decider.h"



int main()
{	

	// #########################################################################
	// ######################## System Input Parameters ########################
	// #########################################################################

	int numberOfBitsGenerated(100);

	int samplesPerSymbol(16);
	double bitPeriod = 1.0E-9;

	// powerUnit = PLANCK_CONSTANT * SPEED_OF_LIGHT / (bitPeriod*wavelength)
	// We will assume: wavelength = 1.550E-6
	//double powerUnit = 6.4078e-13;
	double wavelength = 1.55e-6;
	double samplePeriod = bitPeriod / samplesPerSymbol;  // Talvez isto não seja preciso


	double powerUnit = PLANCK_CONSTANT*SPEED_OF_LIGHT / (samplePeriod*wavelength);
	// Correcção da potência. Quem é que está correcto?
	//double powerUnit = PLANCK_CONSTANT*SPEED_OF_LIGHT / (bitPeriod*wavelength);

	double photonNumber1 = 10;
	double photonNumber2 = 1e4;

	
	double localOscillatorPower1 = powerUnit * photonNumber1;
	double localOscillatorPower2 = powerUnit * photonNumber2;

	// Configuração para lidar com argumentos de entrada.
	//double localOscillatorPower2 = powerUnit * n2_in;

	double localOscillatorPhase = 0;
	//array<t_complex, 4> transferMatrix = { { 1 / sqrt(2), 1 / sqrt(2), 1 / sqrt(2), -1 / sqrt(2) } };
	double responsivity = 1;

	//double amplification = 1e6;
	//double electricalNoiseAmplitude = 0;// 0.0022*0.0022;

	int bufferLength = 512;
	bool shotNoise(true);

	double thermalNoiseAmplitude = 4.7626e-06 * 0;
	bool thermalNoise(false);


	// Escolha da constelação
	
	// Constelação sempre com o mesmo estado
	//vector<t_iqValues> iqAmplitudeValues = { { 1, 1 },{ 1, 1 } };
	
	// Constelação com 2 estados
	//vector<t_iqValues> iqAmplitudeValues = { { -1, 0 },{ 1, 0 } };
	
	// Constelação com 4 estados
	vector<t_iqValues> iqAmplitudeValues = { { 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 } };

	double SNR = 0;

	// Number of samples to avoid the delay created in the MQAM
	int samplesToSkip = samplesPerSymbol * 8;

	// Amplification after detection
	double amplifierGain = 1.0e6;




	// #########################################################################
	// ################ Signals Declaration and Inicialization #################
	// #########################################################################




	// %%%%%%%%%%%%%%%% ALICE SIGNAL GENERATION %%%%%%%%%%%%%%%%

	// Geração dos sinais binários
	Binary S0("S0.sgn");
	S0.setBufferLength(bufferLength);

	// Sinal óptico 
	OpticalSignal S1("S1.sgn");
	S1.setBufferLength(bufferLength);




	// %%%%%%%%%%%%%%%%   BOB SIGNAL DETECTION   %%%%%%%%%%%%%%%%

	OpticalSignal S2("S2.sgn");
	S2.setBufferLength(bufferLength);

	OpticalSignal S3("S3.sgn");
	S3.setBufferLength(bufferLength);

	OpticalSignal S4("S4.sgn");
	S4.setBufferLength(bufferLength);

	OpticalSignal S5("S5.sgn");
	S3.setBufferLength(bufferLength);

	OpticalSignal S6("S6.sgn");
	S6.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S7("S7.sgn");
	S7.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S8("S8.sgn");
	S8.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S9("S9.sgn");
	S9.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S10("S10.sgn");
	S10.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S11("S11.sgn");
	S11.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S12("S12.sgn");
	S12.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S13("S13.sgn");
	S13.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S14("S14.sgn");
	S14.setBufferLength(bufferLength);

	TimeDiscreteAmplitudeContinuousReal S15("S15.sgn");
	S15.setBufferLength(bufferLength);

	TimeDiscreteAmplitudeContinuousReal S16("S16.sgn");
	S16.setBufferLength(bufferLength);

	OpticalSignal S17("S17.sgn");
	S17.setBufferLength(bufferLength);




	// #########################################################################
	// ################# Blocks Declaration and Inicialization #################
	// #########################################################################

	// BEGIN ALICE

	MQamTransmitter B1{ vector<Signal*> {}, vector<Signal*> {&S1, &S0} };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower(localOscillatorPower1);

	B1.setMode(PseudoRandom);

	B1.setBitPeriod(bitPeriod);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setPulseShaperFilter(Gaussian);

	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setSaveInternalSignals(true);
	B1.setSeeBeginningOfImpulseResponse(true);

	// END ALICE




	// BEGIN BOB.

	LocalOscillator B2{ vector<Signal*> {}, vector<Signal*> {&S2} };
	B2.setOpticalPower(localOscillatorPower2);
	B2.setPhase(localOscillatorPhase);
	B2.setSamplingPeriod(bitPeriod / samplesPerSymbol);
	B2.setSymbolPeriod(bitPeriod);
	B2.setSignaltoNoiseRatio(SNR);

	OpticalHybrid B3{ vector<Signal*> {&S1, &S2}, vector<Signal*> {&S3, &S4, &S5, &S6} };

	Photodiode B4{ vector<Signal*> {&S3}, vector<Signal*> {&S7} };
	/*B4.useNoise(shotNoise);
	B4.useThermalNoise(thermalNoise);
	B4.setThermalNoiseAmplitude(thermalNoiseAmplitude);*/
	B4.setResponsivity(responsivity);

	//Sink B100{ vector<Signal*> {&S7}, vector<Signal*> {} };

	Photodiode B5{ vector<Signal*> {&S4}, vector<Signal*> {&S8} };
	/*B5.useNoise(shotNoise);
	B5.useThermalNoise(thermalNoise);
	B5.setThermalNoiseAmplitude(thermalNoiseAmplitude);*/
	B5.setResponsivity(responsivity);

	Photodiode B6{ vector<Signal*> {&S5}, vector<Signal*> {&S9} };
	/*B6.useNoise(shotNoise);
	B6.useThermalNoise(thermalNoise);
	B6.setThermalNoiseAmplitude(thermalNoiseAmplitude);*/
	B6.setResponsivity(responsivity);

	Photodiode B7{ vector<Signal*> {&S6}, vector<Signal*> {&S10} };
	/*B7.useNoise(shotNoise);
	B7.useThermalNoise(thermalNoise);
	B7.setThermalNoiseAmplitude(thermalNoiseAmplitude);*/
	B7.setResponsivity(responsivity);

	Difference B8{ vector<Signal*> {&S7, &S8}, vector<Signal*> {&S11} };

	Difference B9{ vector<Signal*> {&S9, &S10}, vector<Signal*> {&S12} };



	IdealAmplifier B10{ vector<Signal*> {&S11}, vector<Signal*> {&S13} };
	B10.setGain(amplifierGain);

	IdealAmplifier B11{ vector<Signal*> {&S12}, vector<Signal*> {&S14} };
	B11.setGain(amplifierGain);



	Sampler B12{ vector<Signal*> { &S13 }, vector<Signal*> { &S15 } };
	B12.setSamplesToSkip(samplesToSkip);

	Sampler B13{ vector<Signal*> { &S14 }, vector<Signal*> { &S16 } };
	B13.setSamplesToSkip(samplesToSkip);

	// Conjugação dos dois sinais vindos dos samplers para criar um sinal complexo
	// de modo a poder ver-se a constelação.
	// Estou a usar a função RealToComplex2, para evitar um conflito com uma função
	// RealToComplex existente no netxpto.
	RealToComplex2 B14{ vector<Signal*> { &S15, &S16 }, vector<Signal*> { &S17 } };

	// END BOB



	Sink B15{ vector<Signal*> {&S17}, vector<Signal*> {} };
	B15.setNumberOfSamples(samplesPerSymbol*numberOfBitsGenerated);
	B15.setDisplayNumberOfSamples(true);

	Sink B16{ vector<Signal*> {&S0}, vector<Signal*> {} };
	B16.setNumberOfSamples(samplesPerSymbol*numberOfBitsGenerated);
	B16.setDisplayNumberOfSamples(true);




	// #########################################################################
	// ################# System Declaration and Inicialization #################
	// #########################################################################

	System MainSystem{ vector<Block*> {&B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8,
		&B9, &B10, &B11, &B12, &B13, &B14, &B15, &B16} };




	// #########################################################################
	// ############################## System Run ###############################
	// #########################################################################

	MainSystem.run();



	return 0;
}