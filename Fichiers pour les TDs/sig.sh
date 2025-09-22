#!/bin/bash

trap 'handle' 20

handle()
{
  echo "Caught SIGTSTP signal"
}

### main script
X=0
while [ 1 ] ; do
  echo "[sig.sh] $X seconds"
  X=$((X+1))
  sleep 1
done

