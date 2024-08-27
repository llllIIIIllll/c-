#!/bin/bash


INPUT_NUMBER=$1

gst-launch-1.0 -e nvv4l2camerasrc device=/dev/video${INPUT_NUMBER} ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1080' !  \
nvvidconv ! fpsdisplaysink video-sink=xvimagesink


gst-launch-1.0 --gst-plugin-path=/opt/qomolo/gst-plugins/plugins/ros2bridge/plugin/ \
nvv4l2camerasrc device=/dev/video${INPUT_NUMBER} ! \
nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' !\
autovideoconvert !\
autovideoconvert ! videorate ! video/x-raw,framerate=5/1 ! \
autovideoconvert !\
videocrop left=0 right=0 top=288 bottom=228 !\
videoconvert !\
"video/x-raw,width=1920,height=1080" !\
videoscale ! video/x-raw,width=960,height=540 !\
autovideoconvert ! rosimagesink ros-name="${QOMOLO_ROBOT_ID}_gst_image_${INPUT_NUMBER}" ros-topic="/${QOMOLO_ROBOT_ID}/camera_${INPUT_NUMBER}"
