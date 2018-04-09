// Currently mostly copied from BER
# ifndef PROGRAM_INCLUDE_SRN_ESTIMATOR_
# define PROGRAM_INCLUDE_SRN_ESTIMATOR_

# include "netxpto_20180118.h"
# include <vector>

enum WindowType{ Hanning, Hamming };

// Estimates the SNR of a signal
class SNREstimator : public Block {

	bool firstTime{ true };

public:
	SNREstimator() {};
	SNREstimator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setMeasuredIntervalSize(int misz) { measuredIntervalSize= misz; }
	int getMeasuredIntervalSize(void) { return measuredIntervalSize; }

	void setSegmentSize(int sz) { segmentSize = sz; }
	int getSegmentSize(void) { return segmentSize; }

	void setOverlapCount(int olp) { overlapCount = olp; }
	int getOverlapCount(void) { return overlapCount; }

	void setConfidence(double P) { alpha = 1-P; }
	double getConfidence(void) { return 1 - alpha; }

	void setWindowType(WindowType wd) { windowType = wd; }
	WindowType getWindowType(void) { return windowType; }

	void setFilename(string fname) { filename = fname; }
	string getFilename(void) { return filename; }

	vector<double> getWindow(WindowType windowType, int windowSize);
	vector<complex<double>> fftshift(vector<complex<double>> &vec);

private:
	vector <double> measuredInterval;
	WindowType windowType = Hamming;
	vector<double> window;
	vector<double> frequencies;
	vector <double> allSNR;
	bool firstPass = true;
	int measuredIntervalSize = 2048;
	int currentSize = 0;
	int segmentSize = 1024;
	int overlapCount = 256;
	double alpha = 0.05;
	double z;
	double U;
	string filename = "SNR.txt";
};


#endif // !PROGRAM_INCLUDE_SRN_ESTIMATOR_