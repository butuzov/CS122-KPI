#!/usr/bin/env python3

from mpl_toolkits.axes_grid.axislines import SubplotZero
from matplotlib.transforms import BlendedGenericTransform
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt
import numpy as np


if __name__ == '__main__':

    fig = plt.figure(1)
    ax = SubplotZero(fig, 1, 1, 1)

    fig.add_subplot(ax)

    labels = range(-4,5)
    plt.plot(labels, labels, color="w")


    ax.axhline(linewidth=.7, color="black")
    ax.axvline(linewidth=.7, color="black")

    ax.text(0, 1.05, 'y', transform=BlendedGenericTransform(ax.transData, ax.transAxes), ha='center')
    ax.text(1.05, 0, 'x', transform=BlendedGenericTransform(ax.transAxes, ax.transData), va='center')
    #
    for direction in ["xzero", "yzero"]:
        ax.axis[direction].set_axisline_style("-|>")
        ax.axis[direction].set_visible(True)

    for direction in ["left", "right", "bottom", "top"]:
        ax.axis[direction].set_visible(False)

    for label in ax.get_ymajorticklabels():
        label.set_rotation(123)

    x = np.linspace(-4, 0, 100) # x < 0
    f1, = ax.plot(x, -(x), label="-x")

    x = np.linspace(0, 2, 10000) # x < 0
    x = x[1:len(x)-1]
    f2, = ax.plot(x, -(x-1)**2, label="-(x-1)^2")
    #
    x = np.linspace(2, 4, 100) # x < 0
    f3, = ax.plot(x, (x-3), label="x-3")

    plt.legend(handles=[f1,f2,f3], loc=1)

    plt.show()
