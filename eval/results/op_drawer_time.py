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
'size' : 8.5,
}

font3 = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 8.5,
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

fig = plt.figure(figsize=(7.5,4))
gs = gridspec.GridSpec(nrows=2, ncols=2, height_ratios=[1,1])
ax1 = fig.add_subplot(gs[0,0])
ax2 = fig.add_subplot(gs[0,1])
ax3 = fig.add_subplot(gs[1,0])
ax4 = fig.add_subplot(gs[1,1])

bar_width=0.2
op_x_data = ['1K', '10K', '100K', '1M']
op_j_x_data = ['50', '100', '150', '250']

nai_p_y_data = []
nai_p_y_data.append(nai_p_exe_time_ms_log[0])
nai_p_y_data.append(nai_p_exe_time_ms_log[1])
nai_p_y_data.append(nai_p_exe_time_ms_log[2])
nai_p_y_data.append(nai_p_exe_time_ms_log[3])
sgx_p_y_data = []
sgx_p_y_data.append(sgx_p_exe_time_ms_log[0])
sgx_p_y_data.append(sgx_p_exe_time_ms_log[1])
sgx_p_y_data.append(sgx_p_exe_time_ms_log[2])
sgx_p_y_data.append(sgx_p_exe_time_ms_log[3])
cdb_p_y_data = []
cdb_p_y_data.append(cdb_p_exe_time_ms_log[0])
cdb_p_y_data.append(cdb_p_exe_time_ms_log[1])
cdb_p_y_data.append(cdb_p_exe_time_ms_log[2])
cdb_p_y_data.append(cdb_p_exe_time_ms_log[3])

ax1.set_title(r'Projector $\pi$', font2)
ax1.grid(linestyle='--', zorder=1, axis='x', alpha=0.5, which='minor')
ax1.barh(y=range(len(op_x_data)), width=nai_p_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax1.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_p_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax1.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_p_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
for y, x in enumerate(nai_p_y_data):
    ax1.text(x+0.25 if (x >= 0) else x-0.2, y-0.17 if (x >= 0) else y-0.14, '%s' % float('%.3f' % nai_p_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(sgx_p_y_data):
    ax1.text(x+0.3 if (x >= 0) else x-0.2, y+0.02 if (x >= 0) else y+0.08, '%s' % float('%.3f' % sgx_p_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(cdb_p_y_data):
    ax1.text(x+0.35, y+0.26, '%s' % float('%.3f' % cdb_p_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
ax1.set_yticks(np.arange(len(op_x_data))+bar_width)
ax1.set_yticklabels(op_x_data)
x_minor_locator = MultipleLocator(0.5)
x_major_locator = MultipleLocator(1)
ax1.xaxis.set_minor_locator(x_minor_locator)
ax1.xaxis.set_major_locator(x_major_locator)
ax1.set(xlim=[-1.8,4.8])
ax1.tick_params(labelsize=8.5)
labels = ax1.get_xticklabels() + ax1.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax1.legend(loc='lower right', frameon=True, prop=font1)
ax1.set_xlabel('Logarithmic Time (ms)', font3)
ax1.set_ylabel('No. of Documents', font3)

nai_s_y_data = []
nai_s_y_data.append(nai_s_exe_time_ms_log[0])
nai_s_y_data.append(nai_s_exe_time_ms_log[1])
nai_s_y_data.append(nai_s_exe_time_ms_log[2])
nai_s_y_data.append(nai_s_exe_time_ms_log[3])
sgx_s_y_data = []
sgx_s_y_data.append(sgx_s_exe_time_ms_log[0])
sgx_s_y_data.append(sgx_s_exe_time_ms_log[1])
sgx_s_y_data.append(sgx_s_exe_time_ms_log[2])
sgx_s_y_data.append(sgx_s_exe_time_ms_log[3])
cdb_s_y_data = []
cdb_s_y_data.append(cdb_s_exe_time_ms_log[0])
cdb_s_y_data.append(cdb_s_exe_time_ms_log[1])
cdb_s_y_data.append(cdb_s_exe_time_ms_log[2])
cdb_s_y_data.append(cdb_s_exe_time_ms_log[3])

ax2.set_title(r'Selector $\sigma$', font2)
ax2.grid(linestyle='--', zorder=1, axis='x', alpha=0.5, which='minor')
ax2.barh(y=range(len(op_x_data)), width=nai_s_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax2.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_s_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax2.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_s_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
for y, x in enumerate(nai_s_y_data):
    ax2.text(x+0.25 if (x >= 0) else x-0.2, y-0.17 if (x >= 0) else y-0.14, '%s' % float('%.3f' % nai_s_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(sgx_s_y_data):
    ax2.text(x+0.3 if (x >= 0) else x-0.2, y+0.02 if (x >= 0) else y+0.08, '%s' % float('%.3f' % sgx_s_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(cdb_s_y_data):
    ax2.text(x+0.35, y+0.26, '%s' % float('%.3f' % cdb_s_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
ax2.set_yticks(np.arange(len(op_x_data))+bar_width)
ax2.set_yticklabels(op_x_data)
x_minor_locator = MultipleLocator(0.5)
x_major_locator = MultipleLocator(1)
ax2.xaxis.set_minor_locator(x_minor_locator)
ax2.xaxis.set_major_locator(x_major_locator)
ax2.set(xlim=[-1.8,4.8])
ax2.tick_params(labelsize=8.5)
labels = ax2.get_xticklabels() + ax2.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax2.legend(loc='lower right', frameon=True, prop=font1)
ax2.set_xlabel('Logarithmic Time (ms)', font3)
ax2.set_ylabel('No. of Documents', font3)

nai_a_y_data = []
nai_a_y_data.append(nai_a_exe_time_ms_log[0])
nai_a_y_data.append(nai_a_exe_time_ms_log[1])
nai_a_y_data.append(nai_a_exe_time_ms_log[2])
nai_a_y_data.append(nai_a_exe_time_ms_log[3])
sgx_a_y_data = []
sgx_a_y_data.append(sgx_a_exe_time_ms_log[0])
sgx_a_y_data.append(sgx_a_exe_time_ms_log[1])
sgx_a_y_data.append(sgx_a_exe_time_ms_log[2])
sgx_a_y_data.append(sgx_a_exe_time_ms_log[3])
cdb_a_y_data = []
cdb_a_y_data.append(cdb_a_exe_time_ms_log[0])
cdb_a_y_data.append(cdb_a_exe_time_ms_log[1])
cdb_a_y_data.append(cdb_a_exe_time_ms_log[2])
cdb_a_y_data.append(cdb_a_exe_time_ms_log[3])

ax3.set_title(r'Aggregator $\phi$', font2)
ax3.grid(linestyle='--', zorder=1, axis='x', alpha=0.5, which='minor')
ax3.barh(y=range(len(op_x_data)), width=nai_a_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax3.barh(y=np.arange(len(op_x_data))+ 1*bar_width, width=sgx_a_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax3.barh(y=np.arange(len(op_x_data))+ 2*bar_width, width=cdb_a_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
for y, x in enumerate(nai_a_y_data):
    ax3.text(x+0.25 if (x >= 0) else x-0.2, y-0.17 if (x >= 0) else y-0.14, '%s' % float('%.3f' % nai_a_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(sgx_a_y_data):
    ax3.text(x+0.3 if (x >= 0) else x-0.2, y+0.02 if (x >= 0) else y+0.08, '%s' % float('%.3f' % sgx_a_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(cdb_a_y_data):
    ax3.text(x+0.35, y+0.26, '%s' % float('%.3f' % cdb_a_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
ax3.set_yticks(np.arange(len(op_x_data))+bar_width)
ax3.set_yticklabels(op_x_data)
x_minor_locator = MultipleLocator(0.5)
x_major_locator = MultipleLocator(1)
ax3.xaxis.set_minor_locator(x_minor_locator)
ax3.xaxis.set_major_locator(x_major_locator)
ax3.set(xlim=[-1.8,4.8])
ax3.tick_params(labelsize=8.5)
labels = ax3.get_xticklabels() + ax3.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax3.legend(loc='lower right', frameon=True, prop=font1)
ax3.set_xlabel('Logarithmic Time (ms)', font3)
ax3.set_ylabel('No. of Documents', font3)

nai_j_y_data = []
nai_j_y_data.append(nai_j_exe_time_ms_log[0])
nai_j_y_data.append(nai_j_exe_time_ms_log[1])
nai_j_y_data.append(nai_j_exe_time_ms_log[2])
nai_j_y_data.append(nai_j_exe_time_ms_log[3])
sgx_j_y_data = []
sgx_j_y_data.append(sgx_j_exe_time_ms_log[0])
sgx_j_y_data.append(sgx_j_exe_time_ms_log[1])
sgx_j_y_data.append(sgx_j_exe_time_ms_log[2])
sgx_j_y_data.append(sgx_j_exe_time_ms_log[3])
cdb_j_y_data = []
cdb_j_y_data.append(cdb_j_exe_time_ms_log[0])
cdb_j_y_data.append(cdb_j_exe_time_ms_log[1])
cdb_j_y_data.append(cdb_j_exe_time_ms_log[2])
cdb_j_y_data.append(cdb_j_exe_time_ms_log[3])

ax4.set_title(r'Nested Join $\gamma$', font2)
ax4.grid(linestyle='--', zorder=1, axis='x', alpha=0.5, which='minor')
ax4.barh(y=range(len(op_j_x_data)), width=nai_j_y_data, label='Baseline', zorder=2, color='slategrey', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax4.barh(y=np.arange(len(op_j_x_data))+ 1*bar_width, width=sgx_j_y_data, label='QShield', zorder=2, color='chocolate', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
ax4.barh(y=np.arange(len(op_j_x_data))+ 2*bar_width, width=cdb_j_y_data, label='CryptDB', zorder=2, color='forestgreen', edgecolor='dimgray', linewidth=0.5, alpha=1, height=bar_width)
for y, x in enumerate(nai_j_y_data):
    ax4.text(x+0.25 if (x >= 0) else x-0.2, y-0.17 if (x >= 0) else y-0.14, '%s' % float('%.3f' % nai_j_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(sgx_j_y_data):
    ax4.text(x+0.3 if (x >= 0) else x-0.2, y+0.02 if (x >= 0) else y+0.08, '%s' % float('%.3f' % sgx_j_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
for y, x in enumerate(cdb_j_y_data):
    ax4.text(x+0.35, y+0.26, '%s' % float('%.3f' % cdb_j_exe_time_ms[y]), ha='center', va='bottom', fontdict=font4)
ax4.set_yticks(np.arange(len(op_j_x_data))+bar_width)
ax4.set_yticklabels(op_j_x_data)
x_minor_locator = MultipleLocator(0.5)
x_major_locator = MultipleLocator(1)
ax4.xaxis.set_minor_locator(x_minor_locator)
ax4.xaxis.set_major_locator(x_major_locator)
ax4.set(xlim=[-1.8,4.8])
ax4.tick_params(labelsize=8.5)
labels = ax4.get_xticklabels() + ax4.get_yticklabels()
[label.set_fontname('Times New Roman') for label in labels]
ax4.legend(loc='lower right', frameon=True, prop=font1)
ax4.set_xlabel('Logarithmic Time (ms)', font3)
ax4.set_ylabel('No. of Documents', font3)

plt.tight_layout()
plt.show()
