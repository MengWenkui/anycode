#!/bin/bash

workdir=.
cmd=write_sample_3500
nsip=172.25.90.30:8108
rlog=write_list_
elog=err_log_
pcount=20
min=15
max=20
wnum=2000000

for ((i = 1; i <= $pcount; i++)) 
do
   command=$workdir/$cmd
   nohup $command $nsip $wnum $min $max 1>$rlog$i 2>/dev/null &
done


