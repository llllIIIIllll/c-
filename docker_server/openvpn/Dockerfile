FROM kylemanna/openvpn

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apk/repositories && \
    apk add --update coreutils && \
    apk add python2 curl gcc

RUN curl https://bootstrap.pypa.io/pip/2.7/get-pip.py -o get-pip.py && python get-pip.py 

RUN apk add python2-dev musl-dev

RUN python2.7 -m pip install obfsproxy -i https://mirrors.aliyun.com/pypi/simple/ 


