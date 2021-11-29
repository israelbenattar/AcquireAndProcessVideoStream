#!bin/sh

#Updating ubuntu
sudo apt-get update
sudo apt-get upgrade

#instal dependencies
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python3.6-dev python3-numpy libtbb2 libtbb-dev
sudo apt-get install libjasper-dev
sudo apt install grap
REQUIRED_PKG="libjasper-dev"
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $REQUIRED_PKG|grap "install ok installed")
echo $PKG_OK
if ["" = "$PKG_OK"]; then
    sudo apt install software-properties-common
    sudo apt update
    sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
    sudo apt update
fi
sudo apt-get install libjpeg-dev libpng-dev libtiff5-dev libjasper-dev libdc1394-22-dev libeigen3-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common libtbb-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libopenexr-dev libgstreamer-plugins-base1.0-dev libavutil-dev libavfilter-dev libavresample-dev

#get opencv
sudo -s <<EOF
cd /opt 
git clone https://github.com/Itseez/opencv.git
git clone https://github.com/Itseez/opencv_contrib.git

#build and install the opencv
cd opencv
mkdir release && cd release
cmake -D BUILD_TIFF=ON -D WITH_CUDA=OFF -D ENABLE_AVX=OFF -D WITH_OPENGL=OFF -D WITH_OPENCL=OFF -D WITH_IPP=OFF -D WITH_TBB=ON -D BUILD_TBB=ON -D WITH_EIGEN=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules /opt/opencv/
make -j4
make install
ldconfig
EOF
cd ~

#check if opencv was install on the machine
sudo apt install apt-file
sudo apt update
P=$(sudo apt-file search opencv.pc)
P=${P%/*}
P=${P#*:}
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$P
export PKG_CONFIG_PATH
pkg-config --modversion opencv