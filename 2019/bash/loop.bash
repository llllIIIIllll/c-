#!/bin/bash

for file in `pwd`/*; do
    printf '%s\n' "$file"
done

#shopt -u globstar
