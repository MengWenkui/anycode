#!/bin/bash

BASE_HOME=`dirname $(readlink -f $0)`
LOG_DIR=$BASE_HOME/iolog
LOG_FILE=$LOG_DIR/cluster.result
IOSTAT_FILE=$LOG_DIR/iostat.result
TMP_LOG=$LOG_DIR/tmp.log

#$1 pattern
#$2 interval
#$3 file name
get_times()
{
  ret=`egrep "$1" $3 | wc -l` 
  time=`echo $ret $2 | awk '{printf "%.2f\n", $1 / $2 }'` 
  echo $time
}

#$1 interval
#$2 file name
get_read_size()
{
  total_size=0
  time_ret=`egrep "read (v2|) *success" $2 | wc -l`
  read_ret=`egrep "read (v2|) *success" $2 | egrep -o "read len: [0-9]+" | awk '{print $NF}'`
  for i in $read_ret
  do
    total_size=$(($total_size + $i))
  done
  size=`echo "$total_size / $time_ret" | bc`
  echo $size
}

#main
#$1 interval time
#$2 log file
#$3 end_time

if [ $# -lt 2 ]
then
  echo "$0: interval(s) logfile"
  exit 1
fi

if ! [ -d $LOG_DIR ]
then
  mkdir $LOG_DIR
fi

start_time=`date +%s -d today`
end_time=$(echo "$start_time + $1" | bc)

index=`echo $2 | egrep -o "[0-9]+"`
dev_name=`df -lh | awk '/disk'$index'$/ {print $1}' | awk -F '/' '{print $NF}'`
nohup iostat -dxk $dev_name $1 2 >> $IOSTAT_FILE &
sleep_time=`expr $1 + 10`
sleep $sleep_time 

spattern=`date -d "1970-01-01 UTC $start_time seconds" +"%Y-%m-%d %H:%M"`
dpattern=`date -d "1970-01-01 UTC $end_time seconds" +"%Y-%m-%d %H:%M"`
start_pos=`grep -n "$spattern" $2 | head -1 | awk -F ':' '{print $1}'`
end_pos=`grep -n "$dpattern" $2 | head -1 | awk -F ':' '{print $1}'`
if [ -z "$start_pos" ]
then
  echo "no log available"
  exit 1
fi
sed -n ''$start_pos', '$end_pos'p' $2 > $TMP_LOG

read_tps=`get_times "read (v2|) *success" $1 $TMP_LOG`
write_tps=`get_times "close file success" $1 $TMP_LOG`
read_avg_size=`get_read_size $1 $TMP_LOG`

echo "read_tps: $read_tps, write_tps: $write_tps, read_agv_size: $read_avg_size" >> $LOG_FILE
rm $TMP_LOG
