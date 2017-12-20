#ifndef ALICE_QKD_H_
#define ALICE_QKD_H

#include "netxpto.h"
#include "binary_source.h"
#include "m_qam_mapper.h"
#include "discrete_to_continuous_time.h"
#include "pulse_shaper.h"
#include "clock_20171219.h"
#include "sink.h"
#include "super_block_interface.h"

class AliceQKD : public SuperBlock {
	/* State Variables */

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	//Binary S1{ "NUM_A.sgn" };

	TimeDiscreteAmplitudeDiscreteReal S1{ "Alice_1.sgn" };

	TimeDiscreteAmplitudeDiscreteReal S2{ "Alice_2.sgn" };

	TimeContinuousAmplitudeDiscreteReal S3{ "Alice_3.sgn" };

	TimeContinuousAmplitudeDiscreteReal S4{ "Alice_4.sgn" };

	TimeContinuousAmplitudeContinuousReal CLK_A{ "Alice_5.sgn" };

	TimeContinuousAmplitudeDiscreteReal S5{ "Alice_6.sgn" };

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	MQamMapper B1;

	DiscreteToContinuousTime B2;

	PulseShaper B3;

	Sink B4;

	SuperBlockInterface B5;




public:
	/* input parameters*/

	double RateOfPhotons{1e3};
	int StringPhotonsLength{ 12 };

	// Methods
	AliceQKD (vector <Signal*> &inputSignals, vector <Signal*> &outputSignals);

	// Set methods
	void set(int opt);

	void setM(int mValue) { B1.m = mValue; };
	int const getM(void) { return B1.m; };

	void setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues) { B1.m = (t_integer) iqAmplitudesValues.size(); B1.iqAmplitudes.resize(B1.m); B1.iqAmplitudes = iqAmplitudesValues; };
	vector<t_iqValues> const getIqAmplitudes(void) { return B1.iqAmplitudes; };

	void setNumberOfSamplesPerSymbol(int n) { B2.setNumberOfSamplesPerSymbol(n); };
	int const getNumberOfSamplesPerSymbol(void) { return B2.getNumberOfSamplesPerSymbol(); };

	void setRollOffFactor(double rOffFactor) { B3.setRollOffFactor(rOffFactor); };
	double const getRollOffFactor(void) { return B3.getRollOffFactor(); };

	void setSeeBeginningOfImpulseResponse(bool sBeginningOfImpulseResponse) { B3.setSeeBeginningOfImpulseResponse(sBeginningOfImpulseResponse); };
	double const getSeeBeginningOfImpulseResponse(void) { return B3.getSeeBeginningOfImpulseResponse(); };

	void setPulseShaperFilter(PulseShaperFilter fType) { B3.setFilterType(fType); };

	void setNumberOfSamples(long int nOfSamples) { B4.setNumberOfSamples(nOfSamples); };

	void setDisplayNumberOfSamples(bool opt) { B4.setDisplayNumberOfSamples(opt); };

	
};

#endif
