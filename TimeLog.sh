#!/usr/bin/bash

time=date | awk '{print $6$5}'
while [[ ! ( $time < "AM08:00:00" ) || ! ( $time > "PM05:00:00" ) ]]
do
	echo `w | awk '{print $1}' | tail -n+2` `date`
	sleep 10s
done
