#!/bin/bash

ipcs -m 
ipcs -s
ipcs -q

shmid=$(ipcs -m | tail -n 2 | awk '{print $2}')
semid=$(ipcs -s | tail -n 2 | awk '{print $2}')
msqid=$(ipcs -q | tail -n 2 | awk '{print $2}')


echo
echo
echo "Clean shared memory : [$shmid]"

ipcrm -m $shmid

echo "Clean semaphore : [$semid]"

ipcrm -s $semid

echo "Clean message queue : [$msqid]"

ipcrm -q $msqid


echo
echo
ipcs -m 
ipcs -s
ipcs -q
