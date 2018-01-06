#!/bin/bash

defaults() {
    echo "SHOWING FIXMEs"
    grep -rnw './src' './include' './test' -e "FIXME"
    echo ""
    echo "SHOWING TODOs"
    grep -rnw './src' './include' './test' -e "TODO"
    echo ""
    echo "SHOWING NOTEs"
    grep -rnw './src' './include' './test' -e "NOTE"
}

if [ "$#" -eq 0 ];
then
    defaults
    exit 0
fi

if [ "$#" -ne 1 ];
then
    echo "usage: $0 <tag>"
    exit 1
fi

tag=$1
grep -rnw './src' './include' './test' -e "$tag"

