import pylab
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np
import math

font1 = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 5.5,
}

font2 = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 5.5,
}

def ms_data(x):
	y = float(x) * 1000
	return y

def throughput_data(x):
	y = 1/float(x)
	return y

def log_data(x):
	y = math.log(x)
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

(nai_p_file_num, nai_p_exe_time) = load_data('./nai_projector.txt')
nai_p_exe_time_ms = list(map(ms_data, nai_p_exe_time))
nai_p_throught_put = list(map(throughput_data, nai_p_exe_time))
nai_p_throught_put_log = list(map(log_data, nai_p_throught_put))

(nai_s_file_num, nai_s_exe_time) = load_data('./nai_selector.txt')
nai_s_exe_time_ms = list(map(ms_data, nai_s_exe_time))
nai_s_throught_put = list(map(throughput_data, nai_s_exe_time))
nai_s_throught_put_log = list(map(log_data, nai_s_throught_put))

(nai_j_file_num, nai_j_exe_time) = load_data('./nai_joiner.txt')
nai_j_exe_time_ms = list(map(ms_data, nai_j_exe_time))
nai_j_throught_put = list(map(throughput_data, nai_j_exe_time))
nai_j_throught_put_log = list(map(log_data, nai_j_throught_put))

(nai_a_file_num, nai_a_exe_time) = load_data('./nai_aggregator.txt')
nai_a_exe_time_ms = list(map(ms_data, nai_a_exe_time))
nai_a_throught_put = list(map(throughput_data, nai_a_exe_time))
nai_a_throught_put_log = list(map(log_data, nai_a_throught_put))

(sgx_p_file_num, sgx_p_exe_time) = load_data('./sgx_projector.txt')
sgx_p_exe_time_ms = list(map(ms_data, sgx_p_exe_time))
sgx_p_throught_put = list(map(throughput_data, sgx_p_exe_time))
sgx_p_throught_put_log = list(map(log_data, sgx_p_throught_put))

(sgx_s_file_num, sgx_s_exe_time) = load_data('./sgx_selector.txt')
sgx_s_exe_time_ms = list(map(ms_data, sgx_s_exe_time))
sgx_s_throught_put = list(map(throughput_data, sgx_s_exe_time))
sgx_s_throught_put_log = list(map(log_data, sgx_s_throught_put))

(sgx_j_file_num, sgx_j_exe_time) = load_data('./sgx_joiner.txt')
sgx_j_exe_time_ms = list(map(ms_data, sgx_j_exe_time))
sgx_j_throught_put = list(map(throughput_data, sgx_j_exe_time))
sgx_j_throught_put_log = list(map(log_data, sgx_j_throught_put))

(sgx_a_file_num, sgx_a_exe_time) = load_data('./sgx_aggregator.txt')
sgx_a_exe_time_ms = list(map(ms_data, sgx_a_exe_time))
sgx_a_throught_put = list(map(throughput_data, sgx_a_exe_time))
sgx_a_throught_put_log = list(map(log_data, sgx_a_throught_put))

(cdb_p_file_num, cdb_p_exe_time) = load_data('./cdb_projector.txt')
cdb_p_exe_time_ms = list(map(ms_data, cdb_p_exe_time))
cdb_p_throught_put = list(map(throughput_data, cdb_p_exe_time))
cdb_p_throught_put_log = list(map(log_data, cdb_p_throught_put))

(cdb_s_file_num, cdb_s_exe_time) = load_data('./cdb_selector.txt')
cdb_s_exe_time_ms = list(map(ms_data, cdb_s_exe_time))
cdb_s_throught_put = list(map(throughput_data, cdb_s_exe_time))
cdb_s_throught_put_log = list(map(log_data, cdb_s_throught_put))

(cdb_j_file_num, cdb_j_exe_time) = load_data('./cdb_joiner.txt')
cdb_j_exe_time_ms = list(map(ms_data, cdb_j_exe_time))
cdb_j_throught_put = list(map(throughput_data, cdb_j_exe_time))
cdb_j_throught_put_log = list(map(log_data, cdb_j_throught_put))

(cdb_a_file_num, cdb_a_exe_time) = load_data('./cdb_aggregator.txt')
cdb_a_exe_time_ms = list(map(ms_data, cdb_a_exe_time))
cdb_a_throught_put = list(map(throughput_data, cdb_a_exe_time))
cdb_a_throught_put_log = list(map(log_data, cdb_a_throught_put))

(e_size_l, e_exe_time_l) = load_data('./escheme_sgx_dec_1.txt')
e_exe_time_l_ms = list(map(ms_data, e_exe_time_l))

(sgx_size_l, sgx_exe_time_l) = load_data('./sgx_dec_1.txt')
sgx_exe_time_l_ms = list(map(ms_data, sgx_exe_time_l))


(e_size_h, e_exe_time_h) = load_data('./escheme_sgx_dec_2.txt')
e_exe_time_h_ms = list(map(ms_data, e_exe_time_h))
e_throught_put_h = list(map(throughput_data, e_exe_time_h))
e_throught_put_h_log = list(map(log_data, e_throught_put_h))

(sgx_size_h, sgx_exe_time_h) = load_data('./sgx_dec_2.txt')
sgx_exe_time_h_ms = list(map(ms_data, sgx_exe_time_h))
sgx_throught_put_h = list(map(throughput_data, sgx_exe_time_h))
sgx_throught_put_h_log = list(map(log_data, sgx_throught_put_h))

#fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2,2)

fig = plt.figure()
gs = gridspec.GridSpec(nrows=3, ncols=2, height_ratios=[1,1,1])
ax1 = fig.add_subplot(gs[0,0])
ax2 = fig.add_subplot(gs[0,1])
ax3 = fig.add_subplot(gs[1,0])
ax4 = fig.add_subplot(gs[1,1])
ax5 = fig.add_subplot(gs[2, :])

bar_width=0.2
op_x_data = ['1K', '10K', '50K']
op_j_x_data = ['50', '150', '250']

nai_p_y_data = []
nai_p_y_data.append(nai_p_throught_put_log[2])
nai_p_y_data.append(nai_p_throught_put_log[3])
nai_p_y_data.append(nai_p_throught_put_log[7])
sgx_p_y_data = []
sgx_p_y_data.append(sgx_p_throught_put_log[2])
sgx_p_y_data.append(sgx_p_throught_put_log[3])
sgx_p_y_data.append(sgx_p_throught_put_log[7])
# sgx_pure_p_y_data = [900, 870, 700]
cdb_p_y_data = []
cdb_p_y_data.append(cdb_p_throught_put_log[0])
cdb_p_y_data.append(cdb_p_throught_put_log[1])
cdb_p_y_data.append(cdb_p_throught_put_log[2])

ax1.set(title='(a). projection')
ax1.grid(linestyle='--', zorder=1)
ax1.barh(y=range(len(op_x_data)), width=nai_p_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='black', alpha=1, height=bar_width)
ax1.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_p_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='black', alpha=1, height=bar_width)
ax1.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_p_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='black', alpha=1, height=bar_width)
ax1.set_yticks(np.arange(len(op_x_data))+bar_width)
ax1.set_yticklabels(op_x_data)
ax1.set(xlim=[-0.6,10])
ax1.legend(loc='upper right', frameon=False, fontsize=5.5)
ax1.set(xlabel="Logarithmic Throughput", ylabel="Doc Numbers")

nai_s_y_data = []
nai_s_y_data.append(nai_s_throught_put_log[2])
nai_s_y_data.append(nai_s_throught_put_log[3])
nai_s_y_data.append(nai_s_throught_put_log[7])
sgx_s_y_data = []
sgx_s_y_data.append(sgx_s_throught_put_log[2])
sgx_s_y_data.append(sgx_s_throught_put_log[3])
sgx_s_y_data.append(sgx_s_throught_put_log[7])
# sgx_pure_s_y_data = [900, 870, 700]
cdb_s_y_data = []
cdb_s_y_data.append(cdb_s_throught_put_log[0])
cdb_s_y_data.append(cdb_s_throught_put_log[1])
cdb_s_y_data.append(cdb_s_throught_put_log[2])

ax2.set(title='(b). selection')
ax2.grid(linestyle='--', zorder=1)
ax2.barh(y=range(len(op_x_data)), width=nai_s_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='black', alpha=1, height=bar_width)
ax2.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_s_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='black', alpha=1, height=bar_width)
ax2.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_s_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='black', alpha=1, height=bar_width)
ax2.set_yticks(np.arange(len(op_x_data))+bar_width)
ax2.set_yticklabels(op_x_data)
ax2.set(xlim=[-0.6,10])
ax2.legend(loc='upper right', frameon=False, fontsize=5.5)
ax2.set(xlabel="Logarithmic Throughput", ylabel="Doc Numbers")

nai_a_y_data = []
nai_a_y_data.append(nai_a_throught_put_log[2])
nai_a_y_data.append(nai_a_throught_put_log[3])
nai_a_y_data.append(nai_a_throught_put_log[7])
sgx_a_y_data = []
sgx_a_y_data.append(sgx_a_throught_put_log[2])
sgx_a_y_data.append(sgx_a_throught_put_log[3])
sgx_a_y_data.append(sgx_a_throught_put_log[7])
# sgx_pure_a_y_data = [900, 870, 700]
cdb_a_y_data = []
cdb_a_y_data.append(cdb_a_throught_put_log[0])
cdb_a_y_data.append(cdb_a_throught_put_log[1])
cdb_a_y_data.append(cdb_a_throught_put_log[2])

ax3.set(title='(c). aggregation')
ax3.grid(linestyle='--', zorder=1)
ax3.barh(y=range(len(op_x_data)), width=nai_a_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='black', alpha=1, height=bar_width)
ax3.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_a_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='black', alpha=1, height=bar_width)
ax3.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_a_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='black', alpha=1, height=bar_width)
ax3.set_yticks(np.arange(len(op_x_data))+bar_width)
ax3.set_yticklabels(op_x_data)
ax3.set(xlim=[-0.6,10])
ax3.legend(loc='upper right', frameon=False, fontsize=5.5)
ax3.set(xlabel="Logarithmic Throughput", ylabel="Doc Numbers")

nai_j_y_data = []
nai_j_y_data.append(nai_j_throught_put_log[1])
nai_j_y_data.append(nai_j_throught_put_log[3])
nai_j_y_data.append(nai_j_throught_put_log[5])
sgx_j_y_data = []
sgx_j_y_data.append(sgx_j_throught_put_log[1])
sgx_j_y_data.append(sgx_j_throught_put_log[3])
sgx_j_y_data.append(sgx_j_throught_put_log[5])
cdb_j_y_data = []
cdb_j_y_data.append(cdb_j_throught_put_log[0])
cdb_j_y_data.append(cdb_j_throught_put_log[1])
cdb_j_y_data.append(cdb_j_throught_put_log[2])

ax4.set(title='(d). nested join')
ax4.grid(linestyle='--', zorder=1)
ax4.barh(y=range(len(op_j_x_data)), width=nai_j_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='black', alpha=1, height=bar_width)
ax4.barh(y=np.arange(len(op_j_x_data))+ 1*bar_width, width=sgx_j_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='black', alpha=1, height=bar_width)
ax4.barh(y=np.arange(len(op_j_x_data))+ 2*bar_width, width=cdb_j_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='black', alpha=1, height=bar_width)
ax4.set_yticks(np.arange(len(op_j_x_data))+bar_width)
ax4.set_yticklabels(op_j_x_data)
ax4.set(xlim=[-0.6,10])
ax4.legend(loc='upper right', frameon=False, fontsize=5.5)
ax4.set(xlabel="Logarithmic Throughput", ylabel="Doc Numbers")


# style_list = ["g+-", "b*-", "c.-", "yo-", "k+-", "k*-", "k.-", "ko-"]
# ax1.set(title='(a). projection')
# l11, = ax1.plot(list(map(int, sgx_p_file_num)), sgx_p_exe_time_ms, style_list[0])
# l12, = ax1.plot(list(map(int, nai_p_file_num)), nai_p_exe_time_ms, style_list[4])
# l12.set_dashes((1,1))
# ax1.set(xlabel="Doc numbers", ylabel="avg exe time (ms)")
# ax1.grid(linestyle='--')
# ax1.set_xscale('log')
# ax1.set(ylim=[-2, 35])

# ax2.set(title='(b). selection')
# l21, = ax2.plot(list(map(int, sgx_s_file_num)), sgx_s_exe_time_ms, style_list[1])
# l22, = ax2.plot(list(map(int, nai_s_file_num)), nai_s_exe_time_ms, style_list[5])
# l22.set_dashes((1,1))
# ax2.set(xlabel="Doc numbers", ylabel="avg exe time (ms)")
# ax2.grid(linestyle='--')
# ax2.set_xscale('log')
# ax2.set(ylim=[-2, 35])
#
# ax3.set(title='(c). aggregation')
# l31, = ax3.plot(list(map(int, sgx_a_file_num)), sgx_a_exe_time_ms, style_list[2])
# l32, = ax3.plot(list(map(int, nai_a_file_num)), nai_a_exe_time_ms, style_list[6])
# l32.set_dashes((1,1))
# ax3.set(xlabel="Doc numbers", ylabel="avg exe time (ms)")
# ax3.grid(linestyle='--')
# ax3.set_xscale('log')
# ax3.set(ylim=[-2, 35])
#
# ax4.set(title='(d). join')
# l41, = ax4.plot(list(map(int, sgx_j_file_num)), sgx_j_exe_time_ms, style_list[3])
# l42, = ax4.plot(list(map(int, nai_j_file_num)), nai_j_exe_time_ms, style_list[7])
# l42.set_dashes((1,1))
# ax4.set(xlabel="Doc numbers", ylabel="avg exe time (ms)")
# ax4.grid(linestyle='--')
# ax4.set_xscale('log')
# ax4.set(ylim=[-2, 35])


x_data = ['10', '100', '1K','10K','100K','200K', '400K', '600K', '800K', '1M']
ax5.set(title='(e). decryption')
ax5.grid(linestyle='--', zorder=1)
ax5.bar(x=x_data, height=e_throught_put_h_log, label='E-scheme', color='chocolate', edgecolor='black', alpha=1, zorder=3)
ax5.bar(x=x_data, height=sgx_throught_put_h_log, label='SGX', color='forestgreen', edgecolor='black', alpha=1, zorder=2)
for x, y in enumerate(e_throught_put_h_log):
    ax5.text(x, y - 1, '%s' % float('%.2f' % y), ha='center', va='top')
for x, y in enumerate(sgx_throught_put_h_log):
    ax5.text(x, y, '%s' % float('%.2f' % y), ha='center', va='bottom')
ax5.set(xlabel="Data size (Bytes)", ylabel="Logarithmic\nThroughput")
ax5.set(ylim=[0, 20])
ax5.legend(loc='best', frameon=False, fontsize=5.5)

plt.tight_layout()
plt.show()
