#!/bin/sh
g++ -o time_func -pg -Wall -std=c++11 time_func.cpp
./time_func
gprof time_func > time_func.out
