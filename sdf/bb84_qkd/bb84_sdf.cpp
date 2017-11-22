// bb84.cpp : Defines the entry point for the console application.
//

#include "netxpto.h"

#include "binary_source.h"
#include "qrng_decision_circuit.h"
#include "single_photon_detector.h"
#include "single_photon_source.h"
#include "optical_switch.h"
#include "clock.h"
#include "polarization_beam_splitter.h"
#include "fiber.h"
#include "bit_error_rate.h"



int main()
{
	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	// Alice Implementation
	Binary NUM_A{ "NUM_A.sgn" };
	EletricalSignal CLK_A{ "CLK_A.sgn" };
	EletricalSignal S_A1{ "S_A1.sgn" };
	PhotonStream S_A3{"S_A3.sgn"};
	PhotonStream Q_C_1{ "Q_C_1.sgn" };
	EletricalSignal S_A2{ "S_A2.sgn" };
	Messages C_C_1{ "C_C_1.sgn" };
	Messages C_C_6{ "C_C_1.sgn" };
	Binary Data_A{ "Data_A.sgn" };



    return 0;
}

