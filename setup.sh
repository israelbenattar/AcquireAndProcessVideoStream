#!bin/sh

set -e

sudo apt update

#instal dependencies
sudo apt-get install -y build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install -y python3.6-dev python3-numpy libtbb2 libtbb-dev
sudo apt install -y build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev

#get opencv
mkdir ~/opencv_folder
cd ~/opencv_folder
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

#Once the download is complete, create a temporary build directory, and switch to it:
mkdir build
cd build

#Set up the OpenCV build with CMake:
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=OFF \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_folder/opencv_contrib/modules \
    -D BUILD_EXAMPLES=OFF ../opencv

#Start the compilation process:
make -j$(nproc)
sudo make install
sudo ldconfig