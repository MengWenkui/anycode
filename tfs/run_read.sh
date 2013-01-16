#!/bin/bash

workdir=.
cmd=read_sample_3500
nsip=172.25.90.30:8108
wnum=100000
rlog=read_list_
elog=err_log_read_
pcount=10
flist=write_list_sdc1

for ((i = 1; i <= $pcount; i++)) 
do
   command=$workdir/$cmd
   nohup $command $nsip $flist $wnum 1>$rlog$i 2>$elog$i &
done
