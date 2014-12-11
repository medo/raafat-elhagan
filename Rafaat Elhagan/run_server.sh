#!/bin/bash

while true; do nc localhost 8011; done | ./main.bin | ncat -l 8012

