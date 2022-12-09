#!/bin/bash

if [[ $# -ne 1 ]] ; then
    echo "Usage: $0 Your-Password"
    exit 1
fi

password=$1
len=${#password}

if [[ $len -lt 8 ]]; then
    echo "Length check failed! { needs to have atleast 8 characters }"

elif [[ ! $password =~ [0-9] ]]; then
    echo "Numeric characters check failed! { needs to have atleast one numeric character }"

elif ! [[ $password =~ [@\#\$%\&*+-=] ]]; then
    echo "Special charaters check failed! { needs to have atleast one of these symbols [@, #, $, %, &, *, +, -, =] }"

else
    echo "That's a strong password!"
fi
