"""
Illustrate simple contour plotting, contours on an image with
a colorbar for the contours, and labelled contours.

See also contour_image.py.
"""
import matplotlib
import numpy as np
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

matplotlib.rcParams['xtick.direction'] = 'out'
matplotlib.rcParams['ytick.direction'] = 'out'


def custom_div_cmap(numcolors=11, name='custom_div_cmap',
                    mincol='blue', midcol='white', maxcol='red'):
    """ Create a custom diverging colormap with three colors
    
    Default is blue to white to red with 11 colors.  Colors can be specified
    in any way understandable by matplotlib.colors.ColorConverter.to_rgb()
    """

    from matplotlib.colors import LinearSegmentedColormap 
    
    cmap = LinearSegmentedColormap.from_list(name=name, 
                                             colors =[mincol, midcol, maxcol],
                                             N=numcolors)
    return cmap



#delta = 0.025
delta = 0.01
x = np.arange(-1.00001, 1.00001, delta)
y = np.arange(-1.00001, 1.00001, delta)
X, Y = np.meshgrid(x, y)
#Z1 = mlab.bivariate_normal(X, Y, 1.0, 1.0, 0.0, 0.0)
#Z2 = mlab.bivariate_normal(X, Y, 1.5, 0.5, 1, 1)
# difference of Gaussians
#Z = 10.0 * (Z2 - Z1)
#Z = 100.0 * (y - x * x)**2 + (1.0 - x)**2
Z = []

for a in x:
	for b in y:
		#Z.append(a*np.exp(-(a**2) -(b**2)))
		#Z.append(np.sin(5*a)*np.cos(5*b)/5.0)
		#Z.append(np.sin(10.0*(a**2+b**2))/10.0)
		#Z.append(np.sin((a - 1)**2 + b**2))
		Z.append(np.sin(a**2) + np.cos(b**2))
		#Z.append(100.0 * (b - a * a)**2 + (1.0 - a)**2)
		#Z.append(a*a + 2*b*b - 0.3*np.cos(3*np.pi*a) - 0.4*np.cos(4*np.pi*b) + 0.7)

Z = np.array(Z)
Z = Z.reshape((len(x), len(y)))


# Create a simple contour plot with labels using default colors.  The
# inline argument to clabel will control whether the labels are draw
# over the line segments of the contour, removing the lines beneath
# the label

#cmap = custom_div_cmap(numcolors=20)
#cmap = custom_div_cmap(numcolors=50, mincol='#2628bf', maxcol='#c62b2b', midcol='#FFFFFF')
cmap = custom_div_cmap(numcolors=200, mincol='#FFFFFF', maxcol='#444444', midcol='#AAAAAA')

plt.figure()
im = plt.imshow(Z, interpolation='bilinear', origin='lower', cmap=cmap, extent=(-1, 1, -1, 1))
CS = plt.contour(X, Y, Z, levels = np.array([0.015, 0.15, 0.5, 1.3, 2.5, 5.0]))
#CS = plt.contour(X, Y, Z, levels = np.array([0.5, 10.0, 100.0, 1000.0, 10000.0]))
#B = plt.colorbar(CS, shrink=0.8, extend='both')
#plt.clabel(CS, inline=1, fontsize=10)
#plt.title('Simplest default with labels')


plt.savefig('test3.pdf', format='pdf', dpi=1000)
