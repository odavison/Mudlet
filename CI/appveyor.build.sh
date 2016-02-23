#!/bin/sh
# Based on msys_build from the julia project
# https://github.com/JuliaLang/julia/blob/8679538a20147e08a8cf6421c8845d2fd23e64a0/contrib/windows/msys_build.sh

# run in top-level directory
cd `dirname "$0"`/../..
# stop on error
set -e
# show commands as they run
set -x
# make sure stdin exists
exec < /dev/null

prefix=/c/projects/mudlet/lib

mkdir -p lib
curlflags="curl --retry 10 -k -L -y 5"

libname=hunspell-1.3.3
filename=${libname}.tar.gz
url=http://downloads.sourceforge.net/hunspell/$filename
$curlflags -o $filename -O "$url"
tar -xzf $filename -C lib
pushd lib/$libname
./configure --prefix=$prefix
# remove the problematic thing
make && make install
popd

libname=libzip-0.11.2
filename=${libname}.tar.gz
url=http://www.nih.at/libzip/$filename
$curlflags -o $filename -O "$url"
tar -xzf $filename -C lib
pushd lib/$libname
./configure --prefix=$prefix
make && make install
popd

libname=yajl-2.1.0
filename=${libname}.tar.gz
url=https://github.com/lloyd/yajl/tarball/2.1.0
$curlflags -o $filename -O "$url"
tar -xzf $filename -C lib
pushd lib/$libname
mkdir build
pushd build
cmake -G "MSYS Makefiles" ..
make && make DESTDIR=$prefix install
popd
popd
