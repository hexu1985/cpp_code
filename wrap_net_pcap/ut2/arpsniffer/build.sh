#!/bin/sh
# run arpsniffer as root
g++ -g -I../../lib/ arpsniffer.cpp ../../lib/wrappcap.cpp -o arpsniffer -lpcap
