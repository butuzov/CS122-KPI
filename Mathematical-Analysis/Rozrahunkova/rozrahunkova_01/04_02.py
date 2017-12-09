#!/usr/bin/env python3

from mpl_toolkits.axes_grid.axislines import SubplotZero
from matplotlib.transforms import BlendedGenericTransform
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt
import numpy as np


if __name__ == '__main__':

    fig = plt.figure(1)
    ax = SubplotZero(fig, 1, 1, 1)
    # fig.autofmt_xdate(bottom=0.2, rotation=30, ha='right')

    fig.add_subplot(ax)



    ax.text(-1.15, 0.99, 'y', transform=BlendedGenericTransform(ax.transData, ax.transAxes), ha='center')
    ax.text(1., -0.25, 'x', transform=BlendedGenericTransform(ax.transAxes, ax.transData), va='center')
    #
    for direction in ["xzero", "left"]:
        ax.axis[direction].set_axisline_style("-|>")
        ax.axis[direction].set_visible(True)

    for direction in ["right", "bottom", "top"]:
        ax.axis[direction].set_visible(False)

    x = np.linspace(-1., +1., 1000) # x < 0
    # print(x)
    ax.plot(x, 3**((2*x)/(3*x+1)))


    plt.show()
