#!/bin/sh
echo $1
if [ -z "$1" ]
then 
echo "\$1 is empty"
else
echo "\$1 is NOT empty"
fi
