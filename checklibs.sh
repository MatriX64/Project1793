#!/bin/bash

CURRENT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

###############################################################
FILE=/lib64/ld-linux-x86-64.so.2
if [ ! -f $FILE ]
then 	  
	echo "Файл ld-linux-x86-64.so.2 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/ld-linux-x86-64.so.2 /lib64/
else
	echo "Файл ld-linux-x86-64.so.2 присутствует"
fi
###############################################################
FILE=/lib/x86_64-linux-gnu/libc.so.6
if [ ! -f $FILE ] 
then 	  
	echo "Файл libc.so.6 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libc.so.6 /lib/x86_64-linux-gnu/
else
	echo "Файл libc.so.6 присутствует"
fi
###############################################################
FILE=/lib/x86_64-linux-gnu/libcrypto.so.1.0.0 
if [ ! -f $FILE ] 
then 	  
	echo "Файл libcrypto.so.1.0.0 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libcrypto.so.1.0.0   /lib/x86_64-linux-gnu/   
else
	echo "Файл libcrypto.so.1.0.0 присутствует"
fi
###############################################################
FILE=/lib/x86_64-linux-gnu/libdl.so.2 
if [ ! -f $FILE ] 
then 	  
	echo "Файл libdl.so.2 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libdl.so.2 /lib/x86_64-linux-gnu/
else
	echo "Файл libdl.so.2 присутствует"
fi
###############################################################	
FILE=/lib/x86_64-linux-gnu/libgcc_s.so.1  
if [ ! -f $FILE ] 
then 
	echo "Файл libgcc_s.so.1 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libgcc_s.so.1 /lib/x86_64-linux-gnu/
else	
	echo "Файл libgcc_s.so.1 присутствует"
fi
###############################################################	 
FILE=/lib/x86_64-linux-gnu/libm.so.6 
if [ ! -f $FILE ] 
then 
	echo "Файл libm.so.6 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libm.so.6 /lib/x86_64-linux-gnu/
else	
	echo "Файл libm.so.6 присутствует"
fi
###############################################################
FILE=/lib/x86_64-linux-gnu/libnl-3.so.200
if [ ! -f $FILE ] 
then 
	echo "Файл libnl-3.so.200 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libnl-3.so.200 /lib/x86_64-linux-gnu/
else	
	echo "Файл libnl-3.so.200 присутствует"
fi	   
###############################################################
FILE=/lib/x86_64-linux-gnu/libnl-genl-3.so.200
if [ ! -f $FILE ] 
then 
	echo "Файл libnl-genl-3.so.200 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libnl-genl-3.so.200 /lib/x86_64-linux-gnu/
else	
	echo "Файл libnl-genl-3.so.200 присутствует"
fi
###############################################################
FILE=/usr/lib/x86_64-linux-gnu/libpcap.so.0.8
if [ ! -f $FILE ] 
then 
	echo "Файл libpcap.so.0.8 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libpcap.so.0.8 /usr/lib/x86_64-linux-gnu/
else	
	echo "Файл libpcap.so.0.8 присутствует"
fi
###############################################################
FILE=/lib/x86_64-linux-gnu/libpthread.so.0  
if [ ! -f $FILE ] 
then 
	echo "Файл libpthread.so.0 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libpthread.so.0 /lib/x86_64-linux-gnu/
else	
	echo "Файл libpthread.so.0 присутствует"
fi
###############################################################
FILE=/usr/lib/x86_64-linux-gnu/libstdc++.so.6 
if [ ! -f $FILE ] 
then 
	echo "Файл libstdc++.so.6 отсуствует. Производим копирование..."
	cp $CURRENT_DIR/../lib/libstdc++.so.6 /usr/lib/x86_64-linux-gnu/
else	
	echo "Файл libstdc++.so.6 присутствует"
fi
