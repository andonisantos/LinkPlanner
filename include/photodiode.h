# ifndef PROGRAM_INCLUDE_PHOTODIODE_H_
# define PROGRAM_INCLUDE_PHOTODIODE_H_

# include "netxpto.h"
#include <random>

// Simulates a photodiode
class Photodiode : public Block {

	bool firstTime{ true };
	int aux = 0;
	double t = 0;

	double responsivity{ 1 };

	bool shotNoise{ false };

	t_real thermalNoiseAmplitude{ 0.0 };


public:

	Photodiode() {};
	Photodiode(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setResponsivity(double Responsivity) { responsivity = Responsivity; }
	double const getResponsivity(void) { return responsivity; }
	
	void setShotNoise(bool sNoise) { shotNoise = sNoise; }
	bool getShotNoise(void) { return shotNoise; }

	void setThermalNoiseAmplitude(double amplitude) { thermalNoiseAmplitude = amplitude; }
	double getThermalNoiseAmplitude(void) { return thermalNoiseAmplitude; };

};

#endif // !PROGRAM_INCLUDE_PHOTODIODE_H_
