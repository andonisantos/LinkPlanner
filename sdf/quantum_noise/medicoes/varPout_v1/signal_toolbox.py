# Versão simplificada apenas de input/output

import numpy as np
import struct


def signal_filename(dirname, code):
	return dirname + code + ".sgn"


def read_signal_file(filename):
    
    # O return tem que ser um vector do numpy, para poder fazer contas
    # com o output.
    
    fp = open(filename, "rb")
    
    txt = fp.readline()
    data_t_str = txt[13:-2].decode()
    
    # Flag para assinalar se é complexo
    # Tenho de rever a questão de poderem sinais complexos
    f_complex = False
    
    if data_t_str == 'Binary':
        data_t = 'i'
        data_t_s = 4
    elif data_t_str == 'BandpassSignal':
        f_complex = True
        data_t = 'd'
        data_t_s = 8
    elif data_t_str == 'TimeDiscreteAmplitudeDiscreteReal':
        data_t = 'd'
        data_t_s = 8
    elif data_t_str == 'TimeDiscreteAmplitudeContinuousReal':
        data_t = 'd'
        data_t_s = 8
    elif data_t_str == 'TimeContinuousAmplitudeDiscreteReal':
        data_t = 'd'
        data_t_s = 8
    elif data_t_str == 'TimeContinuousAmplitudeContinuousReal':
        data_t = 'd'
        data_t_s = 8
    else:
        print("[ERR] Have no idea of format")
        return ()
    
    # Faltam as outra informações sobre o sinal
    txt = fp.read()
    txt_size = len(txt)
    i = -1
    for k in range(3):
        i+=1
        i = txt.find(0x0a,i)
    
    data_size = (txt_size - i)//data_t_s
    x = struct.unpack_from(data_t*data_size, txt, i+1)
    y = np.asarray(x)
    
    if f_complex:
        z = y[0::2] + 1j*y[1::2]
        return z
    else:
        return y