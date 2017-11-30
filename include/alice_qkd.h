#ifndef ALICE_QKD_H_
#define ALICE_QKD_H

#include "netxpto.h"


class alice_qkd : public Block {
	/* input parameters*/


public:
	alice_qkd(vector <Signal*> &inputSignals, vector <Signal*> &outputSignals) : Block(inputSignals, outputSignals) {};

	void initialize(void);

	bool runBlock(void);

};

#endif
