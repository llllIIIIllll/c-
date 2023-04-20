
```
#gst-launch-1.0 compositor name=comp sink_1::xpos=50 sink_1::ypos=50 ! \
#  videoconvert ! ximagesink \
#  videotestsrc pattern=snow timestamp-offset=3000000000 ! \
#  "video/x-raw,format=AYUV,width=640,height=480,framerate=(fraction)30/1" ! \
#  timeoverlay ! queue2 ! comp. \
#  videotestsrc pattern=smpte ! \
#  "video/x-raw,format=AYUV,width=800,height=600,framerate=(fraction)10/1" ! \
#  timeoverlay ! queue2 ! comp.
#

gst-launch-1.0 compositor name=comp sink_1::xpos=480 sink_2::xpos=960 sink_3::xpos=1440 \
  sink_4::xpos=480 sink_6::xpos=960 sink_7::xpos=1440 \
  sink_4::ypos=384 sink_5::ypos=384 sink_6::ypos=384 sink_7::ypos=384 ! \
  videoconvert ! xvimagesink \
  nvv4l2camerasrc device=/dev/video0 ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' ! nvvidconv ! video/x-raw,width=480,height=768,formate=I420 ! nvvidconv !\
  queue2 ! comp. \
  nvv4l2camerasrc device=/dev/video1 ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' ! nvvidconv ! video/x-raw,width=480,height=768,formate=I420 ! nvvidconv !\
  queue2 ! comp. \
  nvv4l2camerasrc device=/dev/video2 ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' ! nvvidconv ! video/x-raw,width=480,height=768,formate=I420 ! nvvidconv !\
  queue2 ! comp. \
  nvv4l2camerasrc device=/dev/video3 ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' ! nvvidconv ! video/x-raw,width=480,height=768,formate=I420 ! nvvidconv !\
  queue2 ! comp. \
  nvv4l2camerasrc device=/dev/video4 ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' ! nvvidconv ! video/x-raw,width=480,height=768,formate=I420 ! nvvidconv !\
  queue2 ! comp. \
  nvv4l2camerasrc device=/dev/video5 ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' ! nvvidconv ! video/x-raw,width=480,height=768,formate=I420 ! nvvidconv !\
  queue2 ! comp. \
  nvv4l2camerasrc device=/dev/video6 ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' ! nvvidconv ! video/x-raw,width=480,height=768,formate=I420 ! nvvidconv !\
  queue2 ! comp. \
  nvv4l2camerasrc device=/dev/video7 ! nvvidconv ! 'video/x-raw(memory:NVMM), width=1920, height=1536' ! nvvidconv ! video/x-raw,width=480,height=768,formate=I420 ! nvvidconv !\
  queue2 ! comp. 

```