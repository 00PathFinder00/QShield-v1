import pylab
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

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

(s_file_num, s_exe_time) = load_data('./selector.txt')

(j_file_num, j_exe_time) = load_data('./joiner.txt')

(a_file_num, a_exe_time) = load_data('./aggregator.txt')

(e_size_l, e_exe_time_l) = load_data('./escheme_sgx_dec_1.txt')

(size_l, exe_time_l) = load_data('./sgx_dec_1.txt')

(e_size_h, e_exe_time_h) = load_data('./escheme_sgx_dec_2.txt')

(size_h, exe_time_h) = load_data('./sgx_dec_2.txt')

#fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2,2)

fig = plt.figure()
gs = gridspec.GridSpec(nrows=3, ncols=2, height_ratios=[1,1,1])
ax1 = fig.add_subplot(gs[0,0])
ax2 = fig.add_subplot(gs[0,1])
ax3 = fig.add_subplot(gs[1,0])
ax4 = fig.add_subplot(gs[1,1])
ax5 = fig.add_subplot(gs[2, :])

style_list = ["g+-", "b*-", "c.-", "yo-", "k,-", "r,-"]
ax1.set(title='(a). projection')
ax1.plot(p_file_num, p_exe_time, style_list[0])
ax1.set(xlabel="Doc numbers", ylabel="avg exe time (s)")
ax1.grid()
ax1.set(ylim=[0.00100, 0.00750])
ax1.set(xlim=[0, 260])

ax2.set(title='(b). selection')
ax2.plot(s_file_num, s_exe_time, style_list[1])
ax2.set(xlabel="Doc numbers", ylabel="avg exe time (s)")
ax2.grid()
ax2.set(ylim=[0.00100, 0.00750])
ax2.set(xlim=[0, 260])

ax3.set(title='(c). aggregation')
ax3.plot(a_file_num, a_exe_time, style_list[2])
ax3.set(xlabel="Doc numbers", ylabel="avg exe time (s)")
ax3.grid()
ax3.set(ylim=[0.00100, 0.00750])
ax3.set(xlim=[0, 260])

ax4.set(title='(d). join')
ax4.plot(j_file_num, j_exe_time, style_list[3])
ax4.set(xlabel="Doc numbers", ylabel="avg exe time (s)")
ax4.grid()
ax4.set(ylim=[0.00100, 0.00750])
ax4.set(xlim=[0, 260])

ax5.set(title='(e). decryption (SGX)')
ax5.plot(e_size_l, e_exe_time_l, style_list[5], label="e-scheme")
ax5.plot(size_l, exe_time_l, style_list[4], label="baseline")
ax5.set(xlabel="Data size (KBytes)", ylabel="avg exe time (s)")
ax5.grid()
ax5.set(ylim=[0.000010, 0.00250])
ax5.set(xlim=[0, 100000])
ax5.set_xticklabels([0, 20, 40, 60, 80, 100])

plt.legend(loc='upper right', frameon=False, fontsize=10)
plt.tight_layout()
plt.show()
