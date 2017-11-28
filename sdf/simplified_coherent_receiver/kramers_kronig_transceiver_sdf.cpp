# include "netxpto.h"
# include "local_oscillator.h"
# include "binary_source.h"
# include "m_qam_mapper.h"	
# include "discrete_to_continuous_time.h"
# include "pulse_shaper.h"
# include "rf_oscillator.h"								
# include "mixer.h"
# include "fork_20171119.h"
# include "hilbert_transform.h"
# include "iq_modulator.h"
# include "sink.h"

int main() {

	// #####################################################################################################
	// ################################### System Input Parameters #########################################
	// #####################################################################################################

	BinarySourceMode sourceMode{ PseudoRandom };
	int patternLength{ 5 };
	double bitPeriod{ 1.0 / 10e9 };
	vector<t_iqValues> iqAmplitudes{ { { 0,0 },{ 1,0 },{ 2,0 },{ 3,0 },{ 4,0 } } };
	//vector<t_iqValues> iqAmplitudes{ { { 0,0 },{ 1,0 },{ 2,0 },{ 3,0 },{ 4,0 },{ 5,0 },{ 6,0 },{ 7,0 },{ 8,0 },{ 9,0 },{ 10,0 },{ 11,0 },{ 12,0 },{ 13,0 },{ 14,0 },{ 15,0 } } };
	int numberOfBits{ 1000 };				                                        // For value of {-1}, it'll generate long bit sequence.
	int numberOfSamplesPerSymbol{ 16 };
	double rollOffFactor{ 0.3 };
	int impulseResponseTimeLength{ 16 };
	double rfFrequency{500E6};														// It depends on the bandwidth of the signal
	double rfAmplitude{ 1.0 };
	double rfInitialPhase{ 0.0 };
	double samplingPeriod{ bitPeriod / numberOfSamplesPerSymbol };
	double opticalPower{ 1e-3 };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S1{ "S1.sgn" };										// Binary Sequence
	TimeDiscreteAmplitudeDiscreteReal S2{ "S2.sgn" };			// MPAM Signal
	TimeDiscreteAmplitudeDiscreteReal S2b{ "S2b.sgn" };			// Not used (Q signal)
	TimeContinuousAmplitudeDiscreteReal S3{ "S3.sgn" };			// Discrete to continious time
	TimeContinuousAmplitudeContinuousReal S4{ "S4.sgn" };		// Pulse Shapping filter
	TimeContinuousAmplitudeContinuousReal S5{ "S5.sgn" };		// Oscillator
	TimeContinuousAmplitudeContinuousReal S6{ "S6.sgn" };		// Mixer	
	TimeContinuousAmplitudeContinuousReal S7{ "S7.sgn" };		// Fork_s7
	TimeContinuousAmplitudeContinuousReal S8{ "S8.sgn" };		// Fork_s8
	TimeContinuousAmplitudeContinuousReal S9{ "S9.sgn" };		// Hilbert Transformer
	OpticalSignal S10{ "S10.sgn" };							    // IQ Modulator

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	BinarySource B1{ vector<Signal*> {}, vector<Signal*> { &S1} };						
	B1.setMode(sourceMode);
	B1.setPatternLength(patternLength);
	B1.setBitPeriod(bitPeriod);
	B1.setNumberOfBits(numberOfBits);

	MQamMapper B2{ vector<Signal*> { &S1 }, vector<Signal*> { &S2, &S2b } };				
	B2.setIqAmplitudes(iqAmplitudes);

	Sink B3{ vector<Signal*> { &S2b }, vector<Signal*> {} };
	
	DiscreteToContinuousTime B4{ vector<Signal*> { &S2 }, vector<Signal*> { &S3 } };
	B4.setNumberOfSamplesPerSymbol(numberOfSamplesPerSymbol);

	PulseShaper B5{ vector<Signal*> { &S3}, vector<Signal*> { &S4 } };
	B5.setRollOffFactor(rollOffFactor);
	B5.setImpulseResponseTimeLength(impulseResponseTimeLength);
	B5.setSeeBeginningOfImpulseResponse(false);
		
	RfOscillator B6{ vector<Signal*> {}, vector<Signal*> { &S5 } };							
	B6.setSamplingPeriod(2*samplingPeriod);
	B6.setSymbolPeriod(2*bitPeriod);
	B6.setrfFrequency(rfFrequency);
	B6.setrfAmplitude(rfAmplitude);
	B6.setrfPhase(rfInitialPhase);

	Mixer B7{ vector<Signal*> { &S4,&S5 }, vector<Signal*> { &S6 } };

	Fork B8{ vector<Signal*> { &S6 }, vector<Signal*> { &S7,&S8 } };					    

	/*HilbertTransform B9{ vector<Signal*> {&S8}, vector<Signal*> { &S9 } };	

	IqModulator B10{ vector<Signal*> {&S7, &S9}, vector<Signal*> { &S10 } };

	Sink B11{ vector<Signal*> { &S10 }, vector<Signal*> {} };
	B11.setDisplayNumberOfSamples(true);*/


	Sink B_7{ vector<Signal*> { &S7 }, vector<Signal*> {} };			// Fork output S7
	B_7.setDisplayNumberOfSamples(true);

	Sink B_8{ vector<Signal*> { &S8 }, vector<Signal*> {} };			// Fork output S8

	

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	//System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4, &B5, &B6, &B78, &B9, &B10, &B11 } };
	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8,  &B_7, &B_8} };
	//System MainSystem{ vector<Block*> { &B5, &B11} };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################

	MainSystem.run();
	getchar();
	return 0;

}