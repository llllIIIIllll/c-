
chr=/data/overlay_test
mkdir -p $chr || true
mkdir -p $chr/{bin,lib,lib64}
cd $chr
cp -v /bin/{bash,touch,ls,rm} $chr/bin


