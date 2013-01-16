#!/bin/bash

POJ=tfs
#OPEN_REPO=http://code.taobao.org/svn/tfs
#INNER_REPO=http://svn.taobao-develop.com/repos/tfs

OPEN_REPO=http://code.taobao.org/svn/poj1
INNER_REPO=http://code.taobao.org/svn/poj2

usage()
{
  echo "usage:" $0 svn_source svn_dest
  echo "   eg:" $0 trunk stable-1.0.0
  echo "   eg:" $0 stable-1.0.0 release-1.0.0 
  exit 1
}

# arg: return value: command
check()
{
  if [ 0 -eq $1 ]; then
    echo $2
  else
    echo $2 failed!
    exit 1
  fi 
}

# two args, source:dest
trunk_to_stable()
{
  src=${OPEN_REPO}/trunk
  dest=${OPEN_REPO}/branches/$2
  svn cp $src $dest -m "create $2"
  check $? "svn cp $src $dest"
}

# two args, source:dest
stable_to_release()
{
  # copy from stable to release
  src=${OPEN_REPO}/branches/$1
  dest=${OPEN_REPO}/tags/$2
  svn cp $src $dest -m "create $2"
  check $? "svn cp $src $dest"

  # export to local
  tmp_dir=$2-`date +%Y-%m-%d`
  svn export $dest $tmp_dir
  check $? "svn export $dest $tmp_dir"

  # change and import
  if [ -d $tmp_dir ]; then
    cd $tmp_dir
    olpath=${INNER_REPO}/tags/$POJ-${tmp_dir:8}
    # svn export encode.h path and change version
    svn import $olpath -m "import $2"
    check $? "svn import $olpath"

    # remove local
    cd ..
    rm $tmp_dir -rf
    echo pack successfully.
  fi
}

if [ 2 != $# ]; then
  usage
else
  if [[ $1 == *trunk* ]] && [[ $2 == *stable-* ]]; then
    trunk_to_stable $1 $2
  elif [[ $1 == *stable-* ]] && [[ $2 == *release-* ]]; then
    stable_to_release $1 $2
  else
    usage 
  fi
fi
  
