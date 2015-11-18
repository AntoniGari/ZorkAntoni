#!/bin/bash

#Script basic
# Script to compile and execute a c++ program in one step.
# Get file name without the .c extension
# file_name=$(echo $1|sed 's/\(.*\)\.cpp/\1/')

# Compile the program with -o option to specify the name of the binary
# g++ -o $file_name.out $1

# If there were no compilation errors, run the program
#if [[ $? -eq 0 ]]; then
#    ./$file_name.out
#fi

clear
clear
clear

#afegir tots els arxius darrere el main.cpp
g++ Item.cpp World.cpp Area.cpp main.cpp -o my_zork.out

if [[ $? -eq 0 ]]; then
    ./my_zork.out
fi
