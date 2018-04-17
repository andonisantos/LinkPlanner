# ifndef PULSE_SHAPER_FD_20180306_H_
# define PULSE_SHAPER_FD_20180306_H_

# include "filter_20180306.h"
# include "fft_20180208.h"

using namespace std;

enum PulseShaperFilterTF { RaisedCosineTF, RootRaisedCosineTF, GaussianTF };

// Raised-cosine filter frequency implementation. // 2018-03-06 //
class PulseShaperFd : public FD_Filter {

	// Input Parameters
	PulseShaperFilterTF filterType{ RaisedCosineTF };
	int transferFunctionFrequencyLength{ 16 };
	double rollOffFactor{ 0.9 };	
	double BTs{ 0.5 };									// Bandwidth-symbol time product of gaussian filter
	bool passiveFilterMode{ false };

public:

	// Methods 
	PulseShaperFd() : FD_Filter() {};
	PulseShaperFd(vector<Signal *> &InputSig, vector<Signal *> OutputSig):FD_Filter(InputSig, OutputSig) {};

	void initialize(void);
	
	void setTransferFunctionFrequencyLength(int transFunctionLength) { transferFunctionFrequencyLength = transFunctionLength; };
	int const getTransferFunctionFrequencyLength(void) { return transferFunctionFrequencyLength; };

	void setFilterType(PulseShaperFilterTF fType) { filterType = fType; };
	PulseShaperFilterTF const getFilterType(void) { return filterType; };

	void setRollOffFactor(double rOffFactor) { rollOffFactor = rOffFactor; };
	double const getRollOffFactor() { return rollOffFactor; };

	void setBTs(double bandwidthSymbolTimeProduct) { BTs = bandwidthSymbolTimeProduct; }; // This term controls the bandwidth of the gaussian filter
	double const getBTs() { return BTs; };

	void usePassiveFilterMode(bool pFilterMode) { passiveFilterMode = pFilterMode; };
};

# endif


