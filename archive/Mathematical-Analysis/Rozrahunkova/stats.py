#!/usr/bin/env python3

import re

if __name__ == '__main__':
    with open('index.tex') as f:
        read_data = f.read()

        stats = dict()
        colors = re.findall("task{(.*?)}", read_data)
        for color in colors:
            stats.update({color: stats.get(color, 0) + 1})

        ok = stats['green']

        print( "Oleg, your work is " + str(int((ok/len(colors))*100))+"% Ready")
        print( "Total stat", stats)
