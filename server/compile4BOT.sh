#!/bin/bash

cd ./aGarcia
make_cs23_debug.sh
cd ..
mv ./aDebug/aUnix/ARM/cs23Garcia ./aDebug/aUnix/ARM/moveServer
scp ./aDebug/aUnix/ARM/moveServer root@129.170.210.230:/root/moveServer

