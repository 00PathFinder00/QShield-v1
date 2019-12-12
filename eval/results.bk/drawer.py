import pylab
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np

def ms_data(x):
	y = float(x) * 1000
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

(p_file_num, p_exe_time) = load_data('./projector.txt')
p_exe_time_ms = list(map(ms_data, p_exe_time))

(s_file_num, s_exe_time) = load_data('./selector.txt')
s_exe_time_ms = list(map(ms_data, s_exe_time))

(j_file_num, j_exe_time) = load_data('./joiner.txt')
j_exe_time_ms = list(map(ms_data, j_exe_time))

(a_file_num, a_exe_time) = load_data('./aggregator.txt')
a_exe_time_ms = list(map(ms_data, a_exe_time))

(e_size_l, e_exe_time_l) = load_data('./escheme_sgx_dec_1.txt')
e_exe_time_l_ms = list(map(ms_data, e_exe_time_l))

(size_l, exe_time_l) = load_data('./sgx_dec_1.txt')
exe_time_l_ms = list(map(ms_data, exe_time_l))


(e_size_h, e_exe_time_h) = load_data('./escheme_sgx_dec_2.txt')
e_exe_time_h_ms = list(map(ms_data, e_exe_time_h))


(size_h, exe_time_h) = load_data('./sgx_dec_2.txt')
exe_time_h_ms = list(map(ms_data, exe_time_h))

#fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2,2)

fig = plt.figure()
gs = gridspec.GridSpec(nrows=3, ncols=2, height_ratios=[1,1,1.5])
ax1 = fig.add_subplot(gs[0,0])
ax2 = fig.add_subplot(gs[0,1])
ax3 = fig.add_subplot(gs[1,0])
ax4 = fig.add_subplot(gs[1,1])
ax5 = fig.add_subplot(gs[2, :])

style_list = ["g+-", "b*-", "c.-", "yo-", "k,-", "r,-"]
ax1.set(title='(a). projection')
ax1.plot(p_file_num, p_exe_time_ms, style_list[0])
ax1.set(xlabel="Doc numbers", ylabel="avg exe time (ms)")
ax1.grid(linestyle='--')
ax1.set(ylim=[1, 7])
ax1.set(xlim=[0, 5])

ax2.set(title='(b). selection')
ax2.plot(s_file_num, s_exe_time_ms, style_list[1])
ax2.set(xlabel="Doc numbers", ylabel="avg exe time (ms)")
ax2.grid(linestyle='--')
ax2.set(ylim=[1, 7])
ax2.set(xlim=[0, 5])

ax3.set(title='(c). aggregation')
ax3.plot(a_file_num, a_exe_time_ms, style_list[2])
ax3.set(xlabel="Doc numbers", ylabel="avg exe time (ms)")
ax3.grid(linestyle='--')
ax3.set(ylim=[1, 7])
ax3.set(xlim=[0, 5])

ax4.set(title='(d). join')
ax4.plot(j_file_num, j_exe_time_ms, style_list[3])
ax4.set(xlabel="Doc numbers", ylabel="avg exe time (ms)")
ax4.grid(linestyle='--')
ax4.set(ylim=[1, 7])
ax4.set(xlim=[0, 5])

#ax5.set(title='(e). decryption (SGX)')
#ax5.plot(e_size_l, e_exe_time_l_ms, style_list[5], label="e-scheme")
#ax5.plot(size_l, exe_time_l_ms, style_list[4], label="baseline")
#ax5.set(xlabel="Data size (KBytes)", ylabel="avg exe time (ms)")
#ax5.grid()
#ax5.set(ylim=[0, 1.5])
#ax5.set(xlim=[0, 5])
#ax5.set_xticklabels([0, 20, 40, 60, 80, 100])

x_data = ['10','1K','10K','100K','200K', '400K', '600K', '800K', '1M']
ax5.grid(linestyle='--', zorder=1)
ax5.bar(x=x_data, height=e_exe_time_h_ms, label='echeme dec', color='steelblue', alpha=1, zorder=2)
ax5.bar(x=x_data, height=exe_time_h_ms, label='sgx dec', color='indianred', alpha=1, zorder=3)
for x, y in enumerate(e_exe_time_h_ms):
    ax5.text(x, y, '%s' % y, ha='center', va='bottom')
for x, y in enumerate(exe_time_h_ms):
    ax5.text(x, y, '%s' % y, ha='center', va='bottom')
ax5.set(xlabel="Data size (KBytes)", ylabel="avg exe time (ms)")
ax5.set(ylim=[0, 3])
ax5.legend(loc='upper left', frameon=False, fontsize=8)

plt.tight_layout()
plt.show()
