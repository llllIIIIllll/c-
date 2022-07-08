
# 1. fix fdisk size error
sudo parted -l

# 2. resize disk space
sudo cfdisk

# 3. fix fdisk df show error
sudo resize2fs /dev/sdax