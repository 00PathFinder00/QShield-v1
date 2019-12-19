import pylab
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np

def ms_data(x):
	y = float(x) * 1000
	return y

def throughput_data(x):
	y = int(1/float(x))
	return y

def load_data(file_name):
	data_file = open(file_name, 'r')

	file_num = []
	exe_time = []

	for line in data_file:
		tmp = line.split(',')
		file_num.append(tmp[0])
		exe_time.append(tmp[1])

	return (file_num, exe_time)


(e_size_l, e_exe_time_l) = load_data('./escheme_sgx_dec_1.txt')
e_exe_time_l_ms = list(map(ms_data, e_exe_time_l))

(sgx_size_l, sgx_exe_time_l) = load_data('./sgx_dec_1.txt')
sgx_exe_time_l_ms = list(map(ms_data, sgx_exe_time_l))


(e_size_h, e_exe_time_h) = load_data('./escheme_sgx_dec_2.txt')
e_exe_time_h_ms = list(map(ms_data, e_exe_time_h))


(sgx_size_h, sgx_exe_time_h) = load_data('./sgx_dec_2.txt')
sgx_exe_time_h_ms = list(map(ms_data, sgx_exe_time_h))

#fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2,2)

x_data = ['10','1K','10K','100K','200K', '400K', '600K', '800K', '1M']
plt.grid(linestyle='--', zorder=1)
plt.bar(x=x_data, height=e_exe_time_h_ms, label='echeme dec', color='steelblue', alpha=1, zorder=2)
plt.bar(x=x_data, height=sgx_exe_time_h_ms, label='sgx dec', color='brown', alpha=1, zorder=3)
for x, y in enumerate(e_exe_time_h_ms):
    plt.text(x, y, '%s' % y, ha='center', va='bottom')
for x, y in enumerate(sgx_exe_time_h_ms):
    plt.text(x, y, '%s' % y, ha='center', va='bottom')
plt.xlabel("Data size (KBytes)")
plt.ylabel("avg exe time (ms)")
plt.ylim([0, 3])
plt.legend(loc='upper left', frameon=False, fontsize=12)

plt.tight_layout()
plt.show()
