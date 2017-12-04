#!/bin/bash

DIRECTORY="$(pwd)/tests/arrays/"

if [ ! -f ./generate ]; then
  c++ problem_5_generate.cpp code.cpp -o ./generate -std=c++11
fi

if [ ! -f ./timer ]; then
  c++ timer.c -o ./timer -std=c++11
fi

if [ ! -f ./sorter ]; then
  c++ problem_5_sort.cpp code.cpp -o ./sorter -std=c++11
fi

for size in 256 1024 65536 2097152; do
    for i in {1..20}; do
      fn=$(printf "%0.3d\n" $i)
      fs=$(printf "%0.7d\n" $size)
      name="${DIRECTORY}/${fs}_${fn}.txt"

      if [ ! -f $name ]; then
        ./generate $size > $name
      fi
    done
done


sorting_methods=( "merge" "quick" "empty" "selection" "insertion" "insertion+" "bubble" )
for sorting in "${sorting_methods[@]}"; do
  for size in 256 1024 65536 2097152; do

    fs=$(printf "%0.7d\n" $size)
    report="$(dirname $DIRECTORY)/report_${sorting}_${fs}.txt"

    if [ ! -f $report ]; then
      find "$(dirname $DIRECTORY)" -type f -name "${fs}_*.txt" | while read txt; do

        start=$(./timer)
        cat $txt | xargs -L1 ./sorter $sorting {}
        end=$(./timer)
        echo "$(bc <<< "scale=3; $end-$start")" >> $report

      done
    fi;
  done;
done
