#!/bin/bash

workdir=.
cmd=write_sample_3500
nsip=172.25.90.30:8108
wnum=100000
rlog=write_list_
elog=err_log_
pcount=10


for ((i = 1; i <= $pcount; i++)) 
do
   command=$workdir/$cmd
   nohup $command $nsip $wnum 1>$rlog$i 2>/dev/null &
done
