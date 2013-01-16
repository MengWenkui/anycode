#!/bin/bash

DATADIR=/data/disk
TMPINDEX=/home/admin/tfs/index_tmp
BAKINDEX=/home/admin/tfs/index_bak

# for local test
#DATADIR=/home/linqing.zyd/testdir
#TMPINDEX=/home/linqing.zyd/index_tmp

usage()
{
  echo $0 index
  exit 1
}

recover()
{ 
  # remove three blocks
  ll_items=`ls -l $DATADIR$1 | wc -l`
  phy_max=`expr $ll_items - 5`
  for (( i=0; i<3; i++ ))
  do
    todel=`expr $phy_max - $i`
    if [ $? -eq 0 ]; then
      rm $DATADIR$1/$todel
    fi
  done

  # remove soft links
  if [ $? -eq 0 ]; then
    rm -rf $DATADIR$1/index
  fi

  # mv back_up
  if [ ! -d $BAKINDEX ]
    mkdir $BAKINDEX
  fi

  if [ $? -eq 0]; then
    mv $TMPINDEX/index$1/index $BAKINDEX/index$1
  fi

  # recovery index
  if [ $? -eq 0 ]; then
    cp -rf $TMPINDEX/index$1 $DATADIR$1/index
  fi
}

if [ 1 != $# ]; then
  usage
else
  recover $1
fi
  
