#!/bin/bash
#make clean
#make 
qemu-system-arm -kernel csos.elf -cpu arm1176 -m 512 -M raspi  -serial telnet:localhost:1235,server &
sleep 2
telnet localhost 1235
