#!/bin/bash

if [ "$#" -ne 1 ];
then
	echo "usage: $0 <tag>"
	exit 1
fi

tag=$1
grep -rnw './src' './include' -e "$tag"

