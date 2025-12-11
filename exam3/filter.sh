#!/bin/sh
[ -z "$1" ] && exit 1
pattern=$(printf '%s' "$1" | sed 's/[]\/$*.^[]/\\&/g')
replacement=$(printf '%s' "$1" | sed 's/./*/g')
sed "s/$pattern/$replacement/g"