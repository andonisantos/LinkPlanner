# Automation
# Execução do simulador e obtenção da variância da corrente de saída
# em função da potência do oscilador local.
# O output deste conjunto de simulações está em formatado para obter
# Ampéres^2 e Watts.

import numpy as np
import os
from signal_toolbox import *

def run_exe():
	dir_run = "C:\\Users\\diamantinosilva\\git\\"\
	          "LinkPlanner.Diamantino\\sdf\\quantum_noise"
	
	dirname="C:\\Users\\diamantinosilva\\git\\"\
	        "LinkPlanner.Diamantino\\sdf\\quantum_noise\\signals\\"
	
#	wl = 1.55e-6
#	c = 299792458
#	h = 6.626070040e-34
#
#	bitPeriod = 1.0e-9;
#	samplesPerSymbol = 16;
#	
#	n2 = 1e4;
#
#	P=c*h/(wl*bitPeriod/samplesPerSymbol)
	
	decades = 5
	n_pts_per_decade = 5
	l_n1 = np.logspace(0, decades, decades*n_pts_per_decade + 1)
	
	str_out = ""
	
	for i in range(len(l_n1)):
		n1 = l_n1[i]
		
		dir0 = os.getcwd()
		os.chdir(dir_run)
		os.system(".\\x64\\Debug\\quantum_noise.exe " + str(n1))
		os.chdir(dir0)
		
		# S15 é um dos sinais após os sampling.
		yI = read_signal_file(signal_filename(dirname,"S15"))
		var_yI = np.var(yI)
		
		str_tmp = "%g\t%g"%(n1, var_yI)
		str_out += str_tmp + "\n";
		print(str_tmp)
	
	return str_out

str_out = run_exe()


with open("out.txt", "w") as fp:
	fp.write(str_out)
	fp.close()