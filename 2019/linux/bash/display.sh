#!/bin/bash


INPUT_NUMBER=$1

gst-launch-1.0 -e nvv4l2camerasrc device=/dev/video${INPUT_NUMBER} ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1080' !  \
nvvidconv ! fpsdisplaysink video-sink=xvimagesink
