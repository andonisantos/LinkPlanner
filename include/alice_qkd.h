#ifndef ALICE_QKD_H_
#define ALICE_QKD_H

#include "netxpto.h"


class AliceQKD : public Block {
	
public:
	/* input parameters*/

	double RateOfPhotons{1e3};
	int StringPhotonsLength{ 12 };

	// Methods
	AliceQKD (vector <Signal*> &inputSignals, vector <Signal*> &outputSignals) : Block(inputSignals, outputSignals) {};

	void initialize(void);

	bool runBlock(void);

	void setRateOfPhotons(double RPhotons) { RateOfPhotons = RPhotons; };
	double const getRateOfPhotons(void) { return RateOfPhotons; };

	void setStringPhotonsLength(int pLength) { StringPhotonsLength = pLength; };
	int const getStringPhotonsLength(void) { return StringPhotonsLength; };


};

#endif
