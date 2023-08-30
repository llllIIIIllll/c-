
第一种 
EASYRSA_CERT_EXPIRE=1000000 renew XXX nopass 
进行续期

（easyrsa版本小于3.1.1需要到期前30天内，已经过期的不行，版本大于3.1.1没有30天限制，可以直接续期，同样需要server重启，客户端重连，记录一下）

第二种 
EASYRSA_CERT_EXPIRE=1000000 easyrsa build-server-full XXX nopass
， 然后重启openvpn，客户端重连



