#!/bin/bash

trim_string() {
    #Usage: trim_string "  example string  "
    : "${1#"${1%%[![:space:]]*}"}"
    : "${_%"${_##*[![:space:]]}"}"
    printf '%s\n' "$_"
}
