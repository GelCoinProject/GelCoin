#!/bin/bash

if [ -d "$1" ]; then
  cd "$1"
else
  echo "Usage: $0 <datadir>" >&2
<<<<<<< HEAD
  echo "Removes obsolete GelCoin database files" >&2
=======
  echo "Removes obsolete Bitcoin database files" >&2
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
  exit 1
fi

LEVEL=0
if [ -f wallet.dat -a -f addr.dat -a -f blkindex.dat -a -f blk0001.dat ]; then LEVEL=1; fi
if [ -f wallet.dat -a -f peers.dat -a -f blkindex.dat -a -f blk0001.dat ]; then LEVEL=2; fi
if [ -f wallet.dat -a -f peers.dat -a -f coins/CURRENT -a -f blktree/CURRENT -a -f blocks/blk00000.dat ]; then LEVEL=3; fi
if [ -f wallet.dat -a -f peers.dat -a -f chainstate/CURRENT -a -f blocks/index/CURRENT -a -f blocks/blk00000.dat ]; then LEVEL=4; fi

case $LEVEL in
  0)
<<<<<<< HEAD
    echo "Error: no GelCoin datadir detected."
    exit 1
    ;;
  1)
    echo "Detected old GelCoin datadir (before 0.7)."
=======
    echo "Error: no Bitcoin datadir detected."
    exit 1
    ;;
  1)
    echo "Detected old Bitcoin datadir (before 0.7)."
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    echo "Nothing to do."
    exit 0
    ;;
  2)
<<<<<<< HEAD
    echo "Detected GelCoin 0.7 datadir."
    ;;
  3)
    echo "Detected GelCoin pre-0.8 datadir."
    ;;
  4)
    echo "Detected GelCoin 0.8 datadir."
=======
    echo "Detected Bitcoin 0.7 datadir."
    ;;
  3)
    echo "Detected Bitcoin pre-0.8 datadir."
    ;;
  4)
    echo "Detected Bitcoin 0.8 datadir."
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
    ;;
esac

FILES=""
DIRS=""

if [ $LEVEL -ge 3 ]; then FILES=$(echo $FILES blk????.dat blkindex.dat); fi
if [ $LEVEL -ge 2 ]; then FILES=$(echo $FILES addr.dat); fi
if [ $LEVEL -ge 4 ]; then DIRS=$(echo $DIRS coins blktree); fi

for FILE in $FILES; do
  if [ -f $FILE ]; then
    echo "Deleting: $FILE"
    rm -f $FILE
  fi
done

for DIR in $DIRS; do
  if [ -d $DIR ]; then
    echo "Deleting: $DIR/"
    rm -rf $DIR
  fi
done

echo "Done."
