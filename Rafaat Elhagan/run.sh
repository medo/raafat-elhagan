#!/bin/bash

if [[ $2 == "-s" ]]; then
  nc -k -l 8012 | ./main.bin 1 | while true; do nc $1 8011; done
else
  nc -k -l 8011 | ./main.bin 2 | while true; do nc $1 8012; done
fi

