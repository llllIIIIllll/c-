
sudo socat -v TCP-LISTEN:4010,fork,reuseaddr UDP-RECVFROM:4002,reuseaddr
