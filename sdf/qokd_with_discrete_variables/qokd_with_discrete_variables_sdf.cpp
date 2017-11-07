# include "netxpto.h"

# include "random_number_generator.h"
# include "m_qam_transmitter.h"
# include "homodyne_receiver.h"
# include "bit_error_rate.h"
# include "sink.h"

int main(){

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	int symbolRate(100*10^(3));
	int messageSize(4);
	int blockLength(16);
	
	
	//4 possible encode states
	vector<t_iqValues> iqAmplitudeValues = { { 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 } };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	
// %%%%%%%%%%%%%%%% ALICE SIGNAL GENERATION %%%%%%%%%%%%%%%%

	Binary S0{ "NUM_A.sgn" };
	S0.setBufferLength(blockLength);
	
	//Optical signal 
	OpticalSignal S1("Q_A_B.sgn");
	S1.setBufferLength(blockLength);
	
	OpticalSignal SA_3("SA_3.sgn");
	SA_3.setBufferLength(blockLength);
	
	TimeContinuousReal CLK_A ("CLK_A.sgn");
	CLK_A.setBufferLength(blockLength);
	
	TimeContinuousReal SA_1("SA_1.sgn");
	SA_1.setBufferLength(blockLength);
	
	TimeDiscreteReal SA_2 ("SA_2.sgn");
	SA_2.setBufferLength(blockLength);
	
	Message C_A_B("C_A_B.sgn");
	C_A_B.setBufferLength(blockLength);
	
	
	
// %%%%%%%%%%%%%%%%   BOB SIGNAL DETECTION   %%%%%%%%%%%%%%%%
	Binary S1("NUM_B.sgn");
	S1.setBufferLength(blockLength);
	
	TimeContinuousReal CLK_B ("CLK_B.sgn");
	CLK_B.setBufferLength(blockLength);
	
	TimeContinuousReal SB_1("SB_1.sgn");
	SB_1.setBufferLength(blockLength);
	
	TimeContinuousReal SB_2 ("SB_2.sgn");
	SB_2.setBufferLength(blockLength);

	

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################



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