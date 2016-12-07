#!/bin/bash

#required applications:
#uname
#aircrack-ng
#reaver-wps

#checking root
USERID=""

if [ -n "$(command -v id 2> /dev/null)" ]; then
        USERID="$(id -u 2> /dev/null)"
fi

if [ -z "${USERID}" ] && [ -n "$(id -ru)" ]; then
        USERID="$(id -ru)"
fi

if [ -n "${USERID}" ] && [ "${USERID}" != "0" ]; then
        printf "nroot\n" ; exit 1;
elif [ -z "${USERID}" ]; then
        printf "adenied\n" ; exit 1;
fi

#checking binaries
#aircrack-ng | grep -oP '(?<=Aircrack-ng\s)(\S+)'
if [ ! -x "$(command -v iw 2>&1)" ]; then
    printf "iwerror\n" ; exit 1;
fi

if [ ! -x "$(command -v airmon-ng 2>&1)" ]; then
    printf "aicngerror\n" ; exit 1;
fi

if [ ! -x "$(command -v reaver 2>&1)" ]; then
    printf "reaerror\n" ; exit 1;
fi

if [ ! -x "$(command -v wash 2>&1)" ]; then
    printf "wserror\n" ; exit 1;
fi

sleep 6

printf "complete\n"
