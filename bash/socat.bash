
sudo socat -v TCP-LISTEN:4010,fork,reuseaddr UDP-RECVFROM:4002,reuseaddr


sudo socat -v tcp-listen:8000,reuseaddr,fork file:/dev/ttyUSB0,nonblock,waitlock=/var/run/tty0.lock,b115200,raw,echo=0
sudo socat -v pty,link=/dev/ttyUSB1,waitslave tcp:127.0.0.1:8000
