#!/bin/bash

CURRENT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

set -e
set -o pipefail

if [ ! -d $CURRENT_DIR/../../bin ]
then
	echo "error"
	exit
else
	if [ ! -d $CURRENT_DIR/../../bin/aircrack-ng ] || [ ! -d $CURRENT_DIR/../../bin/lib ] || [ ! -d $CURRENT_DIR/../../bin/reaver-wps ]
	then
		echo "error"
		exit
	fi
fi
echo "complete"
