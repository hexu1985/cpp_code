#!/bin/sh
# Usage: gen_random.sh num

CMDNAME=`basename $0`

if (( $# != 1 ))
then
	echo "Usage: $CMDNAME num"
	exit 1
fi

num=$1
i=0
while (( i < num ))
do
	echo $RANDOM
	(( i += 1 ))
done
