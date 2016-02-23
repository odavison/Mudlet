#!/bin/sh
# Based on msys_build from the julia project
# https://github.com/JuliaLang/julia/blob/8679538a20147e08a8cf6421c8845d2fd23e64a0/contrib/windows/msys_build.sh

# run in top-level directory
cd `dirname "$0"`/..
# stop on error
set -e
# show commands as they run
set -x
# make sure stdin exists (necessary for ./configure scripts to work on appveyor)
exec < /dev/null

# Set PATH
export PATH="/c/MinGW/bin:/c/MinGW/msys/1.0/bin:/c/Program Files (x86)/CMake/bin:$PATH"

# Update mingw/msys
#mingw-get update
#mingw-get upgrade
mingw-get install libz-dll libz-dev

# Print utility versions
curl --version
git --version
gcc -v
make -v

buildtype=i686-pc-mingw32
prefix=`pwd`/lib

mkdir -p lib
curlflags="curl --retry 10 -k -L -y 5"

#libname=hunspell-1.3.3
#filename=${libname}.tar.gz
#url=http://downloads.sourceforge.net/hunspell/$filename
#$curlflags -o $filename -O "$url"
#tar -xzf $filename -C lib
#pushd lib/$libname
#./configure --prefix=$prefix --build=$buildtype
#make && make install
#popd
#
#libname=lua-5.1.5
#filename=${libname}.tar.gz
#url=http://www.lua.org/ftp/$filename
#$curlflags -o $filename -O "$url"
#tar -xzf $filename -C lib
#pushd lib/$libname
#make INSTALL_TOP=$prefix mingw && make INSTALL_TOP=$prefix install
#popd
# 
#libname=pcre-8.38
#filename=${libname}.tar.gz
#url=ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/$filename
#$curlflags -o $filename -O "$url"
#tar -xzf $filename -C lib
#pushd lib/$libname
#./configure --prefix=$prefix --build=$buildtype
#make
#make install || true
#popd
# 
#libname=zlib-1.2.8
#filename=${libname}.tar.gz
#url=http://zlib.net/$filename
#$curlflags -o $filename -O "$url"
#tar -xzf $filename -C lib
#pushd lib/$libname
#make -f win32/Makefile.gcc
#export INCLUDE_PATH=/c/mingw32/include/
#export LIBRARY_PATH=/c/mingw32/lib/
#export BINARY_PATH=/c/mingw32/bin/
#make -f win32/Makefile.gcc install
#cp zlib1.dll /c/mingw32/bin
#cp libz.dll.a /c/mingw32/lib
#popd
#
#libname=sqlite-autoconf-3110000
#filename=${libname}.tar.gz
#url=http://sqlite.org/2016/$filename
#$curlflags -o $filename -O "$url"
#tar -xzf $filename -C lib
#pushd lib/$libname
#./configure --prefix=$prefix --build=$buildtype
#make && make install
#popd
#
#libname=libzip-1.1.2
#filename=${libname}.tar.gz
#url=http://www.nih.at/libzip/$filename
#$curlflags -o $filename -O "$url"
#tar -xzf $filename -C lib
#pushd lib/$libname
#./configure --prefix=$prefix --build=$buildtype
#make && make install
#popd
#
#libname=yajl-2.1.0
#git clone https://github.com/lloyd/yajl.git lib/$libname || true
#pushd lib/$libname
#git checkout -b tags/2.1.0 || true
#sed -i 's/WIN32/MSVC/g' CMakeLists.txt
#awk '/^PROJECT/ {print; print"ADD_DEFINITIONS(-Dsprintf_s=snprintf)"; next}1' \
#  CMakeLists.txt > CMakeLists.tmp
#mv CMakeLists.tmp CMakeLists.txt
#mkdir -p build
#pushd build
#cmake \
#  -DCMAKE_INSTALL_PREFIX=$prefix \
#  -G "MSYS Makefiles" ..
#make && make install
#popd
#popd

#libname=boost_1_60_0
#filename=${libname}.tar.gz
#url=http://iweb.dl.sourceforge.net/project/boost/boost/1.60.0/$filename
#$curlflags -o $filename -O "$url"
#tar -xzf $filename -C lib
#pushd lib/$libname
#./bootstrap mingw
#./b2 --toolset=gcc --with-graph
#./b2 -d0 install PREFIX=$prefix
#popd

# Build mudlet
mkdir -p build
pushd build
CMAKE_PREFIX_PATH="/c/Qt/5.5/mingw492_32/lib/cmake" \
LUA_DIR="$prefix" \
HUNSPELL_DIR="$prefix" \
ZIP_DIR="$prefix" \
PCRE_DIR="$prefix" \
YAJL_DIR="$prefix" \
LibZip_DIR="$prefix" \
BOOST_ROOT="$prefix" \
cmake \
-DBoost_COMPILER=-mgw49 \
-G "MSYS Makefiles" ..
make
cp -R ../src/mudlet-lua src
popd
