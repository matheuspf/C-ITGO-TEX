import numpy as np
import matplotlib.pyplot as plt
from pylab import rcParams
import matplotlib.patches as mpatches
import os



size = 9, 4

width = 0.4
name = 'SkillMack_5.pdf'

mean_rank = (1.0000, 2.3750, 4.3125, 7.5625, 5.1250, 4.8750, 5.9375, 4.1875, 4.2500, 5.4375, 4.9375, 7.7500)

n = len(mean_rank)

names = ("C-ITGO", "IAPSO", "IABC-MAL", "PSO-DE", "MBA", "LCA", "DELC", "CMA-ES", "MVDE", "IPSO", "WCA", "APSO")

         

"""
size = 12, 4.2
width = 0.3
name = 'SkillMack_3.pdf'

mean_rank = (1.0000, 2.7500, 2.7500, 5.1250, 8.6250, 7.9375, 5.8750, 8.9375, 5.8125,
             4.8750, 7.0000, 5.0000, 5.0625, 6.5000, 5.8750, 8.5625, 9.2500)

n = len(mean_rank)

names = ("C-ITGO", "IAPSO", "SAMP-\nJaya", "IABC-\nMAL", "PSO-DE", 
         "HPSO", "MBA", "CPSO", "LCA", "CB-ABC", "DELC",
         "CMA-ES", "MVDE", "IPSO", "WCA", "UPSO", "APSO")
"""



rcParams['figure.figsize'] = size


fig, ax = plt.subplots()

index = np.arange(n)

rects = plt.bar(index, mean_rank, width=width, alpha=0.4, color='b')

for rect, val in zip(rects, mean_rank):
        height = rect.get_height()
        ax.text(rect.get_x() + rect.get_width()/2., 1.01*height, '%.2f' % val, ha='center', va='bottom')


#plt.xlabel('Methods')
plt.ylabel('Mean rank')
#plt.title('Skillings-Mack test')
plt.xticks(index, names)
ax.tick_params(axis=u'both', which=u'both', length=0, labelsize=8)
plt.legend()
plt.box(on=None)
plt.savefig(name, format='pdf')

os.system('pdfcrop ' + name)

plt.tight_layout()
plt.show()