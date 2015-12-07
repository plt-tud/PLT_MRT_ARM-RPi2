#!/bin/bash

WDIR="/home/ichrispa/work/svn/working_copies/RPi_UA_Blinker"
EXECUTABLE="ua_blinker"
#IP="10.42.0.158"
#IP="10.0.53.112"
IP="192.168.1.56"

scp $WDIR/* pi@$IP:~/
scp $WDIR/lib/* pi@$IP:~/
ssh pi@$IP  "sudo killall gdbserver $EXECUTABLE; chmod +x ~/$EXECUTABLE *.so"
ssh pi@$IP  "sudo LD_LIBRARY_PATH=./ gdbserver :2345 ~/$EXECUTABLE" &

exit 0