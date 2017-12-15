#!/usr/bin/env python3

import glob


reports = dict()

def update_dict( sorting_method ):
    for report in glob.glob("tests/report_" + sorting_method + "_*.txt"):
        sorting = report.split("_")

        total_elements = int(sorting[2].split(".")[0])
        sorting_method = sorting[1]


        item = reports.get(sorting_method, {});
        item[total_elements] = 0


        with open(report, 'r') as f :
            line = f.readline()
            lines, total = 1, 0.0
            while line:
                line = f.readline()
                if line.strip():
                    lines += 1
                    total += float(line)

            if sorting_method == "empty":
                item[total_elements] = total/lines;
            else :
                item[total_elements] = (total/lines) - reports['empty'][total_elements];

        reports.update({sorting_method: item})

update_dict('empty')
update_dict('quick')
update_dict('merge')
update_dict('insertion')
update_dict('selection')
update_dict('insertion+')
update_dict('bubble')

print( 'Sorting Method & n=2^8 &  n=2^\{10\} & n=2^\{16\} &  n=2^\{21\} \\\\' )
for key, item in reports.items():
    print( '{} & {:06.4f} &  {:06.4f} &  {:06.4f} &  {:06.4f} \\\\'.format(key, item[256], item[1024], item[65536], item[2097152] ) )
