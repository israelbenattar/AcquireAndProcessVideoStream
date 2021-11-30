#!bin/sh

sudo apt update
sudo apt install python3-opencv

#Updating ubuntu
sudo apt-get update
sudo apt-get upgrade

#instal dependencies
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python3.6-dev python3-numpy libtbb2 libtbb-dev
sudo apt install build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev

#get opencv
mkdir ~/opencv_build && cd ~/opencv_build
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

#Once the download is complete, create a temporary build directory, and switch to it:
cd ~/opencv_build/opencv
mkdir build && cd build

#Set up the OpenCV build with CMake:
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON ..


#Start the compilation process:
make -j8
sudo make install

pkg-config --modversion opencv4
sudo -s <<EOF
mv /usr/local/include/opencv4/opencv2 /usr/local/include
P=$(sudo find ~/ -name "libopencv_core.so.4.5")
P=${P%/*}
touch /etc/ld.so.conf.d/opencv.conf
echo  $P>>/etc/ld.so.conf.d/opencv.conf
sudo ldconfig -v
EOF

sudo apt-get update
sudo apt-get upgrade
