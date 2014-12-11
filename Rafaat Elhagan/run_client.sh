#!/bin/bash

while true; do nc localhost 8012; done | ./main.bin | ncat -l 8011
