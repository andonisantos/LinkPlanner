
#include "netxpto.h"
#include "binary_source.h"
#include "single_photon_source.h"
#include "polarization_beam_splitter.h"
#include "single_photon_detector.h"
#include "discrete_to_continuous_time.h"


int main()
{
	// #########################################################################
	// ######################## System Input Parameters ########################
	// #########################################################################
	int symbolRate(100 * 10 ^ 3);
	int messageSize(4);
	int blockLenght(16);

	int bufferLengt(512);

	int numberOfBits(10000);
	int samplesPerSymbol(4);

	vector <t_real> polarizationDegree(45);
	
	vector<t_iqValues> iqAmplitudeValues = { { 1, 1 },{ -1, 1 },{ -1, -1 },{ 1, -1 } };


	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	// %%%%%%%%%%%%%%%% ALICE SIGNAL GENERATION %%%%%%%%%%%%%%%%
	Binary S0("NUM_A.sgn" );
	S0.setBufferLength(bufferLengt);

	PhotonStream Q_A_B{};
	PhotonStream SA_3{};

	TimeContinuousAmplitudeContinuousReal CLK_A("CLK_A.sgn");
	CLK_A.setBufferLength(bufferLengt);

	TimeContinuousAmplitudeContinuousReal SA_1("SA_1.sgn");
	SA_1.setBufferLength(bufferLengt);

	TimeDiscreteAmplitudeContinuousReal SA_2("SA_2.sgn");
	SA_2.setBufferLength(bufferLengt);

	//Message ??

	// %%%%%%%%%%%%%%%% ALICE SIGNAL GENERATION %%%%%%%%%%%%%%%%
	Binary S1("NUM_B.sgn");
	S1.setBufferLength(bufferLengt);

	TimeContinuousAmplitudeContinuousReal CLK_B("CLK_B.sgn");
	CLK_B.setBufferLength(bufferLengt);

	TimeContinuousAmplitudeContinuousReal SB_1("SB_1.sgn");
	SB_1.setBufferLength(bufferLengt);

	TimeContinuousAmplitudeContinuousReal SB_2("SB_2.sgn");
	SB_2.setBufferLength(bufferLengt);

	//Message??

	// #########################################################################
	// ################# Blocks Declaration and Inicialization #################
	// #########################################################################
	//Random Number generation Alice
	BinarySource A0{ vector <Signal*> {},vector <Signal*> {&S0} };
	A0.setMode(PseudoRandom);
	A0.setNumberOfBits(numberOfBits);

	DiscreteToContinuousTime A2{ vector <Signal*> {&S0}, vector <Signal*> {&SA_2} };
	A2.setNumberOfSamplesPerSymbol(samplesPerSymbol);

	SinglePhotonSource A3{ vector <Signal*> {&SA_2},vector <Signal*> {&SA_3} };
	A3.setPolarization(polarizationDegree);

	PolarizationBeamSplitter A4{ vector <Signal*> {&SA_3}, vector <Signal*> {&Q_A_B} };

	//Bob side
	BinarySource B0{ vector <Signal*> {}, vector <Signal*> {&S1} };
	B0.setMode(PseudoRandom);
	B0.setNumberOfBits(numberOfBits);

	DiscreteToContinuousTime B1{ vector <Signal*> {&S1}, vector <Signal*> {&SB_2} };
	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);


	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem {};
	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################

	MainSystem.run();

    return 0;
}

