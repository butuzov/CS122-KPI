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
        ax.set_ylim([-10,10])
        ax.set_xlim([-5,5])

    for direction in ["left", "right", "bottom", "top"]:
        ax.axis[direction].set_visible(False)

    for label in ax.get_ymajorticklabels():
        label.set_rotation(123)

    for points in [(-10,-2.101, "red"), (-2,0, "green"), (0.001,10, "blue")]:
        x = np.linspace(points[0], points[1], 100)
        y = 2/(x**2+2*x)
        ax.plot(x, y, color="green")

    x = np.linspace(-10, 10, 100)
    ax.plot(x, -(2*(x/x)), "k--")

    y = np.linspace(-10, 10, 100)
    ax.plot(-(2*(y/y)), y, "k--")

    y = np.linspace(-10, 10, 100)
    ax.plot(0*y, y, "k--")

    y = np.linspace(-10, 10, 100)
    ax.plot(y, 0*y, "k--")


    plt.show()
