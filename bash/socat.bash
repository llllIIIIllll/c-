
sudo socat -v TCP-LISTEN:4010,fork,reuseaddr UDP-RECVFROM:4002,reuseaddr


sudo socat -v udp-listen:4001,reuseaddr,fork file:/dev/ttyS1,nonblock,waitlock=/var/run/tty0.lock,b115200,raw,echo=0

sudo socat -v pty,link=/dev/ttyUSB1,waitslave tcp:127.0.0.1:8000


sudo socat -v  file:/dev/ttyS1,echo=0,b115200,raw,crnl,icanon=1 TCP:192.168.66.203:4010,reuseaddr,fork,crlf


sudo socat -u -v -v TCP:192.168.66.203:4010,fork UDP:4444

sudo socat -v -v UDP-RECVFROM:4001,fork,reuseaddr UDP:192.168.66.1:4001,reuseaddr
