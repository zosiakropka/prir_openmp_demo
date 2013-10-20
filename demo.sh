#!/usr/bin/env bash

make clean
make

MAX_THREADS_NUMBER=${1-"16"}

# usage: averageExecutionTime <program>
function averageExecutionTime() {
    program="$1"
    local time=0
    for (( i=0; i<5; i++ )); do
        tmp=`eval $program`
        time=`echo "$time+$tmp" | bc`
    done
    time=`echo "$time*0.2" | bc`
    echo "$time"
}

# usage: averageExecutionTime <program> <data file> <graph file>
function createData() {
    program="$1"
    data_file="$2"
    graph_file="$3"
    # default OpenMP thread's number
    unset OMP_NUM_THREADS
    echo -n "Testing default threads number... "
    time=$(averageExecutionTime "$program")
    echo "$time CPU ticks"
    export PLOT_OPENMP_DEFAULT=$time


    # thread's number set to values 1:16, while number of logical CPU's is 2x4 (HT)
    for (( threads=1; threads<=$MAX_THREADS_NUMBER; threads++ )); do

        (echo -n "$threads ") >> $data_file
        export OMP_NUM_THREADS=$threads
        echo -n "Testing $threads threads... "
        time=$(averageExecutionTime "$program")
        echo "$time CPU ticks"
        (echo $time) >> $data_file
    done

    export PLOT_GRAPH_FILE="$graph_file"
    export PLOT_DATA_FILE="$data_file"
    export PLOT_PROGRAM="$program"

    gnuplot plot.pg
}

createData "./matrix 100 100000" "output/matrix.dat" "output/matrix.png"
