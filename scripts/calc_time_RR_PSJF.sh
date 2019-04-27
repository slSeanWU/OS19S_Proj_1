#!/usr/bin/env bash

input=$1
qt=0.001727558
begin=0.0
first=65536

while IFS= read -r line
do
    if [ ! "$line" ]; then
        break
    fi

    pid=$(echo $line | cut -f4 -d" ")
    if [ $pid -lt $first ]; then
        first=$pid
        begin=$(echo $line | cut -f5 -d" ")
    fi
done < $input

while IFS= read -r line
do
    if [ ! "$line" ]; then
        break
    fi

    pid=$(echo $line | cut -f4 -d" ")
    time2=$(echo $line | cut -f6 -d" ")

    diff=$(echo "scale=9; $time2-$begin" | bc -q)
    rec=$(echo "scale=9; $diff/$qt" | bc -q)
    echo "$pid finish at $rec unit" 

done < $input
