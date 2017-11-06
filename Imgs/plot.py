import numpy as np
import matplotlib.pyplot as plt
from pylab import rcParams
import matplotlib.patches as mpatches
import os



size = 7, 4

width = 0.4
name = 'SkillMack_5.pdf'

n = 8

mean_rank = (1.0000, 2.2500, 3.8750, 3.9375, 4.0000, 3.5000, 3.7500, 5.6875)

names = ("C-ITGO", "IAPSO", "IABC-MAL", "MBA", "LCA", "CMA-ES", "MVDE", "APSO")

         

"""
size = 12, 4.2
width = 0.3
name = 'SkillMack_3.pdf'

n = 15

mean_rank = (1.0000, 2.6875, 3.1250, 4.8125, 6.8750,
             6.9375, 5.1875, 5.3750, 4.6250, 5.9375,
             4.5000, 4.8750, 5.5625, 5.4375, 8.0625)

names = ("C-ITGO", "IAPSO", "SAMP-\nJaya", "IABC-\nMAL", "PSO-DE", 
         "HPSO", "MBA", "LCA", "CB-ABC", "DELC",
         "CMA-ES", "MVDE", "IPSO", "WCA", "APSO")
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