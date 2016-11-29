#!/bin/bash

#required applications:
#uname
#aircrack-ng
#reaver-wps

USERID=""

#if [ -n "$(command -v id 2> /dev/null)" ]; then
#        USERID="$(id -u 2> /dev/null)"
#fi

#if [ -z "${USERID}" ] && [ -n "$(id -ru)" ]; then
#        USERID="$(id -ru)"
#fi

#if [ -n "${USERID}" ] && [ "${USERID}" != "0" ]; then
#        printf "nroot\n" ; exit 1;
#elif [ -z "${USERID}" ]; then
#        printf "adenied\n"
#fi

sleep 3

printf "complete\n"
