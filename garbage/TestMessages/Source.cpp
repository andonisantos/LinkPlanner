# include "netxpto.h"
# include <string.h>

void main() {
	Messages S1("M1.sgn");
	S1.setFirstValueToBeSaved(1000);

	S1.writeHeader();

	t_message m1(4);
	t_message m2(4);

	for (int aux = 1; aux <= 1000; aux++) {

/*		ostringstream convert;
		convert << aux;
		string result = convert.str();*/

		string result = to_string(aux);

		m1[0].fieldName = "Campo1";
		m1[0].fieldValue = result;
		m1[1].fieldName = "Campo2";
		m1[1].fieldValue = result;
		m1[2].fieldName = "Campo3";
		m1[2].fieldValue = result;
		m1[3].fieldName = "Campo4";
		m1[3].fieldValue = result;

		if (aux == 512) {
			cout << to_string(aux) + "\n";
		}

		S1.bufferPut(m1);
	}

	S1.bufferGet(&m2);

	S1.close();




}