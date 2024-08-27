
#
git clone --depth=1 -b Ubuntu-5.4.0-42.46 git://git.launchpad.net/~ubuntu-kernel/ubuntu/+source/linux/+git/focal



# prepare
chmod a+x debian/rules
chmod a+x debian/scripts/*
chmod a+x debian/scripts/misc/*
fakeroot debian/rules clean
fakeroot debian/rules editconfigs # you need to go through each (Y, Exit, Y, Exit..) or get a complaint about config later


# build
fakeroot debian/rules clean

# quicker build:
fakeroot debian/rules binary-headers binary-generic binary-perarch

# if you need linux-tools or lowlatency kernel, run instead:
fakeroot debian/rules binary
