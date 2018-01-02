#include "netxpto.h"
#include "hilbert_transform.h"



using namespace std;

void HilbertTransform::initialize(void)
{
	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
	outputSignals[0]->samplesPerSymbol = inputSignals[0]->samplesPerSymbol;
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}

bool HilbertTransform::runBlock(void)
{

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();
	int process = min(ready, space);

	if (process <= 0) return false;

	t_real S8;
	vector<double> inputBufferTimeDomain(process);
	vector <complex<double>> IN(process);
	vector <complex<double>> inputSignalFreqencyDomain(process);
	vector <complex<double>> hilbertTransformed(process);
	complex<double> imaginary{ (0,-1) };
	
	for (int i = 0; i < process; i++)									// Get the Input signal as a vector of size "n"
	{
		inputSignals[0]->bufferGet(&S8);
		inputBufferTimeDomain.at(i)=S8;
	}
	
	/*Here we have to convert the vector of REAL value into COMPLEX value because our function acccepts only complex value*/

	ComplexMult C;
	vector<double> re(process);
	vector<double> im(process);							// Imaginary part as "0"

	for (int i = 0; i < process; i++)
	{
		re[i] = inputBufferTimeDomain.at(i);			// Real part
	}

	C.ReImVect2ComplexVect(re, im, IN);					// Time domain complex form signal
	inputSignalFreqencyDomain = transform(IN,1);		// Frequency domain complex form signal

	double zero{ 0 };

	for (int i = 0; i < process; i++)
	{
		if (i < process/2)
		{
			vector <double> a;
			vector <double> b;
			double c;
			double d;
			vector <double> ac;
			vector <double> bd;
			vector <double> bc;
			vector <double> ad;
			vector <double> re;
			vector <double> im;

			a.at(i) = inputSignalFreqencyDomain[i].real();
			b.at(i) = inputSignalFreqencyDomain[i].imag();
			c = imaginary.real();
			d = imaginary.imag();

			ac.at(i) = a.at(i)*c;	// ac
			bd.at(i) = b.at(i)*d;	// bd
			bc.at(i) = b.at(i)*c;	// bc
			ad.at(i) = a.at(i)*d;	// ad

			re.at(i) = ac.at(i) - bd.at(i);	// ac-bd REAL PART
			im.at(i) = bc.at(i) + ad.at(i);	// bc+ad IMAG PART

			for (int i = 0; i < re.size(); i++)
			{
				hilbertTransformed[i] = (re[i],im[i]);
			}
		}

		if (i > process/2)
		{
			vector <double> a;
			vector <double> b;
			double c;
			double d;
			vector <double> ac;
			vector <double> bd;
			vector <double> bc;
			vector <double> ad;
			vector <double> re;
			vector <double> im;

			a.at(i) = inputSignalFreqencyDomain[i].real();
			b.at(i) = inputSignalFreqencyDomain[i].imag();
			c = imaginary.real();
			d = imaginary.imag();

			ac.at(i) = a.at(i)*c;	// ac
			bd.at(i) = b.at(i)*d;	// bd
			bc.at(i) = b.at(i)*c;	// bc
			ad.at(i) = a.at(i)*d;	// ad

			re.at(i) = ac.at(i) - bd.at(i);	// ac-bd REAL PART
			im.at(i) = bc.at(i) + ad.at(i);	// bc+ad IMAG PART

			for (int i = 0; i < re.size(); i++)
			{
				hilbertTransformed[i] = (re[i], im[i]);
			}
		}

		if (i == 0)
		{
			hilbertTransformed[i] = (zero, zero);
		}

	}

	vector<complex<double>> hilbertTransformedTD(hilbertTransformed.size());

	
	hilbertTransformedTD = transform(hilbertTransformed, 1);



	for (int i = 0; i < process; i++)									// put the data using bufferput
	{
		t_real S9;
	}


	return true;
	}




