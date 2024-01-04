
sudo ip link set can3 down
sudo ip link set can3 type can bitrate 250000 restart-ms 5000  
sudo ip link set can3 up


sudo ip link set can3 down
sudo ip link set can3 type can bitrate 250000 dbitrate 2000000 berr-reporting on fd on listen-only on 
sudo ip link set can3 up


sudo candump -ta can3,0:0,#FFFFFFFF