#!/bin/bash

if [[ $2 == "-s" ]]; then
  while true; do nc $1 8011; done | ./main.bin 1 | ncat -l 8012
else
  while true; do nc $1 8012; done | ./main.bin 2 | ncat -l 8011
fi

