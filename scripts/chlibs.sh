#!/bin/bash

CURRENT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
LIB_DIR=/usr/lib/libs_1793
LDCONF=/etc/ld.so.conf.d/libs_1793.conf

set -e
set -o pipefail

if [ ! -d $LIB_DIR ]
then 	  
	mkdir $LIB_DIR
	cp $CURRENT_DIR/../lib/ld-linux-x86-64.so.2     $LIB_DIR
	cp $CURRENT_DIR/../lib/libc.so.6 		$LIB_DIR
	cp $CURRENT_DIR/../lib/libcrypto.so.1.0.0  	$LIB_DIR
	cp $CURRENT_DIR/../lib/libdl.so.2 		$LIB_DIR
	cp $CURRENT_DIR/../lib/libgcc_s.so.1 		$LIB_DIR
	cp $CURRENT_DIR/../lib/libm.so.6 		$LIB_DIR
	cp $CURRENT_DIR/../lib/libnl-3.so.200 		$LIB_DIR
	cp $CURRENT_DIR/../lib/libnl-genl-3.so.200 	$LIB_DIR
	cp $CURRENT_DIR/../lib/libpcap.so.0.8 		$LIB_DIR
	cp $CURRENT_DIR/../lib/libpthread.so.0 		$LIB_DIR
	cp $CURRENT_DIR/../lib/libstdc++.so.6 		$LIB_DIR
	
	if [ ! -f $LDCONF ]
	then
		cat > /etc/ld.so.conf.d/libs_1793.conf <<EOF
$LIB_DIR
EOF
		ldconfig
	fi
	echo  "complete"
	
else
	if [ ! -f $LIB_DIR/ld-linux-x86-64.so.2 ]
	then
		cp $CURRENT_DIR/../lib/ld-linux-x86-64.so.2     $LIB_DIR
	fi
	
	if [ ! -f $LIB_DIR/libc.so.6 ]
	then
		cp $CURRENT_DIR/../lib/libc.so.6	     	$LIB_DIR
	fi

	if [ ! -f $LIB_DIR/libcrypto.so.1.0.0 ]
	then
		cp $CURRENT_DIR/../lib/libcrypto.so.1.0.0       $LIB_DIR
	fi

	if [ ! -f $LIB_DIR/libdl.so.2 ]
	then
		cp $CURRENT_DIR/../lib/libdl.so.2 	        $LIB_DIR
	fi

	if [ ! -f $LIB_DIR/libgcc_s.so.1 ]
	then
		cp $CURRENT_DIR/../lib/libgcc_s.so.1	        $LIB_DIR
	fi

	if [ ! -f $LIB_DIR/libm.so.6 ]
	then
		cp $CURRENT_DIR/../lib/libm.so.6 	        $LIB_DIR
	fi

	if [ ! -f $LIB_DIR/libnl-3.so.200 ]
	then
		cp $CURRENT_DIR/../lib/libnl-3.so.200      	$LIB_DIR
	fi

	if [ ! -f $LIB_DIR/libnl-genl-3.so.200 ]
	then
		cp $CURRENT_DIR/../lib/libnl-genl-3.so.200      $LIB_DIR
	fi
	
	if [ ! -f $LIB_DIR/libpcap.so.0.8 ]
	then
		cp $CURRENT_DIR/../lib/libpcap.so.0.8           $LIB_DIR
	fi

	if [ ! -f $LIB_DIR/libpthread.so.0 ]
	then
		cp $CURRENT_DIR/../lib/libpthread.so.0     	$LIB_DIR
	fi

	if [ ! -f $LIB_DIR/libstdc++.so.6 ]
	then
		cp $CURRENT_DIR/../lib/libstdc++.so.6     	$LIB_DIR
	fi
	
	echo "complete"
fi
