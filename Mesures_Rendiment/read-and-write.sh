#!/bin/bash

if [ "$#" -ne 4 ]; then
    echo "Usage: chunkSize, sync[0, 1], FilePathRead, FilePathWrite"
    exit
fi
#sync; sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'
echo "./write-to-disk2 $1 $2 $4 &"
./write-to-disk2 $1 $2 $4 &
echo "./read-from-disk $1 $2 $3 &"
./read-from-disk $1 $2 $3 &
wait
