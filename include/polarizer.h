#ifndef POLARIZE_H_
#define POLARIZER_H_

#include "netxpto.h"

class polarizer: public Block{

public:
	polarizer(vector <Signal*> &inputSignals, vector <Signal*> &outputSignals) : Block(inputSignals, outputSignals) {};

	void initialize(void);

	bool runBlock(void);
};
#endif // !POLARIZE_H_

