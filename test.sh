#!/bin/bash
make clean
make 
make test &
sleep 2
telnet localhost 1235
