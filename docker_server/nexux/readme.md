
export NEXUS_DOMAIN="qmlsrv.com"
export NEXUS_IP_ADDRESS="10.159.101.101"

keytool -genkeypair -keystore keystore.jks -storepass password -keypass password -alias jetty -keyalg RSA -keysize 2048 -validity 5000 -dname "CN=*.${NEXUS_DOMAIN}, OU=Example, O=Sonatype, L=Unspecified, ST=Unspecified, C=CN" -ext "SAN=DNS:${NEXUS_DOMAIN},IP:${NEXUS_IP_ADDRESS}" -ext "BC=ca:true"


curl -u "${nexus_username}:${nexus_passwd}" -H "Content-Type: multipart/form-data" --data-binary "@./${deb_package_name}" ${publish_url}
