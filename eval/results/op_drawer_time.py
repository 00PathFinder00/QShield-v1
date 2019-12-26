import pylab
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from matplotlib.pyplot import MultipleLocator
import numpy as np
import math

font1 = {'family' : 'Times New Roman',
'weight' : 'bold',
'size' : 5,
}

font2 = {'family' : 'Times New Roman',
'weight' : 'bold',
'size' : 12,
}

font3 = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 10,
}

font4 = {'family' : 'Times New Roman',
'weight' : 'bold',
'size' : 5,
}

def ms_data(x):
	y = float(x) * 1000
	return y

def throughput_data(x):
	y = 1/float(x)
	return y

def log_data(x):
	y = math.log(x, 10)
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
nai_p_exe_time_ms_log = list(map(log_data, nai_p_exe_time_ms))
nai_p_throught_put = list(map(throughput_data, nai_p_exe_time))
nai_p_throught_put_log = list(map(log_data, nai_p_throught_put))

(nai_s_file_num, nai_s_exe_time) = load_data('./nai_selector.txt')
nai_s_exe_time_ms = list(map(ms_data, nai_s_exe_time))
nai_s_exe_time_ms_log = list(map(log_data, nai_s_exe_time_ms))
nai_s_throught_put = list(map(throughput_data, nai_s_exe_time))
nai_s_throught_put_log = list(map(log_data, nai_s_throught_put))

(nai_j_file_num, nai_j_exe_time) = load_data('./nai_joiner.txt')
nai_j_exe_time_ms = list(map(ms_data, nai_j_exe_time))
nai_j_exe_time_ms_log = list(map(log_data, nai_j_exe_time_ms))
nai_j_throught_put = list(map(throughput_data, nai_j_exe_time))
nai_j_throught_put_log = list(map(log_data, nai_j_throught_put))

(nai_a_file_num, nai_a_exe_time) = load_data('./nai_aggregator.txt')
nai_a_exe_time_ms = list(map(ms_data, nai_a_exe_time))
nai_a_exe_time_ms_log = list(map(log_data, nai_a_exe_time_ms))
nai_a_throught_put = list(map(throughput_data, nai_a_exe_time))
nai_a_throught_put_log = list(map(log_data, nai_a_throught_put))

(sgx_p_file_num, sgx_p_exe_time) = load_data('./sgx_projector.txt')
sgx_p_exe_time_ms = list(map(ms_data, sgx_p_exe_time))
sgx_p_exe_time_ms_log = list(map(log_data, sgx_p_exe_time_ms))
sgx_p_throught_put = list(map(throughput_data, sgx_p_exe_time))
sgx_p_throught_put_log = list(map(log_data, sgx_p_throught_put))

(sgx_s_file_num, sgx_s_exe_time) = load_data('./sgx_selector.txt')
sgx_s_exe_time_ms = list(map(ms_data, sgx_s_exe_time))
sgx_s_exe_time_ms_log = list(map(log_data, sgx_s_exe_time_ms))
sgx_s_throught_put = list(map(throughput_data, sgx_s_exe_time))
sgx_s_throught_put_log = list(map(log_data, sgx_s_throught_put))

(sgx_j_file_num, sgx_j_exe_time) = load_data('./sgx_joiner.txt')
sgx_j_exe_time_ms = list(map(ms_data, sgx_j_exe_time))
sgx_j_exe_time_ms_log = list(map(log_data, sgx_j_exe_time_ms))
sgx_j_throught_put = list(map(throughput_data, sgx_j_exe_time))
sgx_j_throught_put_log = list(map(log_data, sgx_j_throught_put))

(sgx_a_file_num, sgx_a_exe_time) = load_data('./sgx_aggregator.txt')
sgx_a_exe_time_ms = list(map(ms_data, sgx_a_exe_time))
sgx_a_exe_time_ms_log = list(map(log_data, sgx_a_exe_time_ms))
sgx_a_throught_put = list(map(throughput_data, sgx_a_exe_time))
sgx_a_throught_put_log = list(map(log_data, sgx_a_throught_put))

(cdb_p_file_num, cdb_p_exe_time) = load_data('./cdb_projector.txt')
cdb_p_exe_time_ms = list(map(ms_data, cdb_p_exe_time))
cdb_p_exe_time_ms_log = list(map(log_data, cdb_p_exe_time_ms))
cdb_p_throught_put = list(map(throughput_data, cdb_p_exe_time))
cdb_p_throught_put_log = list(map(log_data, cdb_p_throught_put))

(cdb_s_file_num, cdb_s_exe_time) = load_data('./cdb_selector.txt')
cdb_s_exe_time_ms = list(map(ms_data, cdb_s_exe_time))
cdb_s_exe_time_ms_log = list(map(log_data, cdb_s_exe_time_ms))
cdb_s_throught_put = list(map(throughput_data, cdb_s_exe_time))
cdb_s_throught_put_log = list(map(log_data, cdb_s_throught_put))

(cdb_j_file_num, cdb_j_exe_time) = load_data('./cdb_joiner.txt')
cdb_j_exe_time_ms = list(map(ms_data, cdb_j_exe_time))
cdb_j_exe_time_ms_log = list(map(log_data, cdb_j_exe_time_ms))
cdb_j_throught_put = list(map(throughput_data, cdb_j_exe_time))
cdb_j_throught_put_log = list(map(log_data, cdb_j_throught_put))

(cdb_a_file_num, cdb_a_exe_time) = load_data('./cdb_aggregator.txt')
cdb_a_exe_time_ms = list(map(ms_data, cdb_a_exe_time))
cdb_a_exe_time_ms_log = list(map(log_data, cdb_a_exe_time_ms))
cdb_a_throught_put = list(map(throughput_data, cdb_a_exe_time))
cdb_a_throught_put_log = list(map(log_data, cdb_a_throught_put))

(e_size_l, e_exe_time_l) = load_data('./escheme_sgx_dec_1.txt')
e_exe_time_l_ms = list(map(ms_data, e_exe_time_l))

(sgx_size_l, sgx_exe_time_l) = load_data('./sgx_dec_1.txt')
sgx_exe_time_l_ms = list(map(ms_data, sgx_exe_time_l))


(e_size_h, e_exe_time_h) = load_data('./escheme_sgx_dec_2.txt')
e_exe_time_h_ms = list(map(ms_data, e_exe_time_h))
e_exe_time_h_ms_log = list(map(log_data, e_exe_time_h_ms))
e_throught_put_h = list(map(throughput_data, e_exe_time_h))
e_throught_put_h_log = list(map(log_data, e_throught_put_h))

(sgx_size_h, sgx_exe_time_h) = load_data('./sgx_dec_2.txt')
sgx_exe_time_h_ms = list(map(ms_data, sgx_exe_time_h))
sgx_exe_time_h_ms_log = list(map(log_data, sgx_exe_time_h_ms))
sgx_throught_put_h = list(map(throughput_data, sgx_exe_time_h))
sgx_throught_put_h_log = list(map(log_data, sgx_throught_put_h))

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
nai_p_y_data.append(nai_p_exe_time_ms_log[0])
nai_p_y_data.append(nai_p_exe_time_ms_log[1])
nai_p_y_data.append(nai_p_exe_time_ms_log[2])
sgx_p_y_data = []
sgx_p_y_data.append(sgx_p_exe_time_ms_log[0])
sgx_p_y_data.append(sgx_p_exe_time_ms_log[1])
sgx_p_y_data.append(sgx_p_exe_time_ms_log[2])
cdb_p_y_data = []
cdb_p_y_data.append(cdb_p_exe_time_ms_log[0])
cdb_p_y_data.append(cdb_p_exe_time_ms_log[1])
cdb_p_y_data.append(cdb_p_exe_time_ms_log[2])

ax1.set_title('(a). projection', font2)
ax1.grid(linestyle='--', zorder=1, axis='x')
ax1.barh(y=range(len(op_x_data)), width=nai_p_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax1.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_p_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax1.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_p_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
for y, x in enumerate(nai_p_y_data):
    ax1.text(x+0.4, y-0.17, '%s ; %s' % (float('%.2f' % x), float('%.2f' % nai_p_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(sgx_p_y_data):
    ax1.text(x+0.4, y+0.03, '%s ; %s' % (float('%.2f' % x), float('%.2f' % sgx_p_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(cdb_p_y_data):
    ax1.text(x+0.4, y+0.24, '%s ; %s' % (float('%.2f' % x), float('%.2f' % cdb_p_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
ax1.set_yticks(np.arange(len(op_x_data))+bar_width)
ax1.set_yticklabels(op_x_data)
x_minor_locator = MultipleLocator(0.2)
x_major_locator = MultipleLocator(1)
ax1.xaxis.set_minor_locator(x_minor_locator)
ax1.xaxis.set_major_locator(x_major_locator)
ax1.set(xlim=[-0.1,4])
ax1.tick_params(labelsize=10)
labels = ax1.get_xticklabels() + ax1.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax1.legend(loc='lower right', frameon=True, prop=font1)
ax1.set_xlabel('Logarithmic Time [ms]', font3)
ax1.set_ylabel('No. of Documents', font3)

nai_s_y_data = []
nai_s_y_data.append(nai_s_exe_time_ms_log[0])
nai_s_y_data.append(nai_s_exe_time_ms_log[1])
nai_s_y_data.append(nai_s_exe_time_ms_log[2])
sgx_s_y_data = []
sgx_s_y_data.append(sgx_s_exe_time_ms_log[0])
sgx_s_y_data.append(sgx_s_exe_time_ms_log[1])
sgx_s_y_data.append(sgx_s_exe_time_ms_log[2])
cdb_s_y_data = []
cdb_s_y_data.append(cdb_s_exe_time_ms_log[0])
cdb_s_y_data.append(cdb_s_exe_time_ms_log[1])
cdb_s_y_data.append(cdb_s_exe_time_ms_log[2])

ax2.set_title('(b). selection', font2)
ax2.grid(linestyle='--', zorder=1, axis='x')
ax2.barh(y=range(len(op_x_data)), width=nai_s_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax2.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_s_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax2.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_s_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
for y, x in enumerate(nai_s_y_data):
    ax2.text(x+0.4, y-0.17, '%s ; %s' % (float('%.2f' % x), float('%.2f' % nai_s_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(sgx_s_y_data):
    ax2.text(x+0.4, y+0.03, '%s ; %s' % (float('%.2f' % x), float('%.2f' % sgx_s_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(cdb_s_y_data):
    ax2.text(x+0.4, y+0.24, '%s ; %s' % (float('%.2f' % x), float('%.2f' % cdb_s_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
ax2.set_yticks(np.arange(len(op_x_data))+bar_width)
ax2.set_yticklabels(op_x_data)
x_minor_locator = MultipleLocator(0.2)
x_major_locator = MultipleLocator(1)
ax2.xaxis.set_minor_locator(x_minor_locator)
ax2.xaxis.set_major_locator(x_major_locator)
ax2.set(xlim=[-0.1,4])
ax2.tick_params(labelsize=10)
labels = ax2.get_xticklabels() + ax2.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax2.legend(loc='lower right', frameon=True, prop=font1)
ax2.set_xlabel('Logarithmic Time [ms]', font3)
ax2.set_ylabel('No. of Documents', font3)

nai_a_y_data = []
nai_a_y_data.append(nai_a_exe_time_ms_log[0])
nai_a_y_data.append(nai_a_exe_time_ms_log[1])
nai_a_y_data.append(nai_a_exe_time_ms_log[2])
sgx_a_y_data = []
sgx_a_y_data.append(sgx_a_exe_time_ms_log[0])
sgx_a_y_data.append(sgx_a_exe_time_ms_log[1])
sgx_a_y_data.append(sgx_a_exe_time_ms_log[2])
cdb_a_y_data = []
cdb_a_y_data.append(cdb_a_exe_time_ms_log[0])
cdb_a_y_data.append(cdb_a_exe_time_ms_log[1])
cdb_a_y_data.append(cdb_a_exe_time_ms_log[2])

ax3.set_title('(c). aggregation', font2)
ax3.grid(linestyle='--', zorder=1, axis='x')
ax3.barh(y=range(len(op_x_data)), width=nai_a_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax3.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_a_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax3.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_a_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
for y, x in enumerate(nai_a_y_data):
    ax3.text(x+0.4, y-0.17, '%s ; %s' % (float('%.2f' % x), float('%.2f' % nai_a_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(sgx_a_y_data):
    ax3.text(x+0.4, y+0.03, '%s ; %s' % (float('%.2f' % x), float('%.2f' % sgx_a_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(cdb_a_y_data):
    ax3.text(x+0.4, y+0.24, '%s ; %s' % (float('%.2f' % x), float('%.2f' % cdb_a_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
ax3.set_yticks(np.arange(len(op_x_data))+bar_width)
ax3.set_yticklabels(op_x_data)
x_minor_locator = MultipleLocator(0.2)
x_major_locator = MultipleLocator(1)
ax3.xaxis.set_minor_locator(x_minor_locator)
ax3.xaxis.set_major_locator(x_major_locator)
ax3.set(xlim=[-0.1,4])
ax3.tick_params(labelsize=10)
labels = ax3.get_xticklabels() + ax3.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax3.legend(loc='lower right', frameon=True, prop=font1)
ax3.set_xlabel('Logarithmic Time [ms]', font3)
ax3.set_ylabel('No. of Documents', font3)

nai_j_y_data = []
nai_j_y_data.append(nai_j_exe_time_ms_log[0])
nai_j_y_data.append(nai_j_exe_time_ms_log[1])
nai_j_y_data.append(nai_j_exe_time_ms_log[2])
sgx_j_y_data = []
sgx_j_y_data.append(sgx_j_exe_time_ms_log[0])
sgx_j_y_data.append(sgx_j_exe_time_ms_log[1])
sgx_j_y_data.append(sgx_j_exe_time_ms_log[2])
cdb_j_y_data = []
cdb_j_y_data.append(cdb_j_exe_time_ms_log[0])
cdb_j_y_data.append(cdb_j_exe_time_ms_log[1])
cdb_j_y_data.append(cdb_j_exe_time_ms_log[2])

ax4.set_title('(d). nested join', font2)
ax4.grid(linestyle='--', zorder=1, axis='x')
ax4.barh(y=range(len(op_j_x_data)), width=nai_j_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax4.barh(y=np.arange(len(op_j_x_data))+ 1*bar_width, width=sgx_j_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax4.barh(y=np.arange(len(op_j_x_data))+ 2*bar_width, width=cdb_j_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
for y, x in enumerate(nai_j_y_data):
    ax4.text(x+0.4, y-0.17, '%s ; %s' % (float('%.2f' % x), float('%.2f' % nai_j_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(sgx_j_y_data):
    ax4.text(x+0.4, y+0.03, '%s ; %s' % (float('%.2f' % x), float('%.2f' % sgx_j_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(cdb_j_y_data):
    ax4.text(x+0.4, y+0.24, '%s ; %s' % (float('%.2f' % x), float('%.2f' % cdb_j_exe_time_ms[y])), ha='center', va='bottom', fontdict=font4)
ax4.set_yticks(np.arange(len(op_j_x_data))+bar_width)
ax4.set_yticklabels(op_j_x_data)
x_minor_locator = MultipleLocator(0.2)
x_major_locator = MultipleLocator(1)
ax4.xaxis.set_minor_locator(x_minor_locator)
ax4.xaxis.set_major_locator(x_major_locator)
ax4.set(xlim=[-0.1,4])
ax4.tick_params(labelsize=10)
labels = ax4.get_xticklabels() + ax4.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax4.legend(loc='lower right', frameon=True, prop=font1)
ax4.set_xlabel('Logarithmic Time [ms]', font3)
ax4.set_ylabel('No. of Documents', font3)

x_data = ['10', '100', '1K','10K','100K','200K', '400K', '600K', '800K', '1M']
ax5.set_title('(e). decryption', font2)
ax5.grid(linestyle='--', axis='y', zorder=1)
ax5.bar(x=x_data, height=e_exe_time_h_ms_log, label='QShield', color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, zorder=2)
ax5.bar(x=x_data, height=sgx_exe_time_h_ms_log, label='Baseline', color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, zorder=3)
for x, y in enumerate(e_exe_time_h_ms_log):
    ax5.text(x, y + 0.1, '%s ; %s' % (float('%.2f' % y), float('%.2f' % e_exe_time_h_ms[x])), ha='center', va='bottom', fontdict=font4)
for x, y in enumerate(sgx_exe_time_h_ms_log):
    ax5.text(x, y - 0.2, '%s ; %s' % (float('%.2f' % y), float('%.2f' % sgx_exe_time_h_ms[x])), ha='center', va='top', fontdict=font4)
ax5.set_xlabel('Data Size (Bytes)', font3)
ax5.set_ylabel('Logarithmic Time [ms]', font3)
y_minor_locator = MultipleLocator(0.2)
y_major_locator = MultipleLocator(1)
ax5.yaxis.set_minor_locator(y_minor_locator)
ax5.yaxis.set_major_locator(y_major_locator)
ax5.set(ylim=[-2, 1])
labels = ax5.get_xticklabels() + ax5.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax5.legend(loc='lower right', frameon=True, prop=font1)

plt.tight_layout()
plt.show()
