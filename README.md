# VideoProcessor

VideoProcessor is a c++ program to read a .mp4 file as if it was
a live video stream and process the video in run time and write it the an .avi file.
The process is: for each frame its edges are calculated using sobel edge detector 
and then the original frame is blended with its edges image.

## Build and Install dependencies
The current recommended and tested environment is Ubuntu 18.04 LTS whit c++>=11
1) go to the folder that you want to clone the repastory
2) run the folwing commands:
```
git clone https://github.com/israelbenattar/AcquireAndProcessVideoStream.git
cd AcquireAndProcessVideoStream
bash setup.sh
```
## Usage
to run the program go to AcquireAndProcessVideoStream folder and run the folwing commands:
```
make
./VideoProcessor <path to the input .mp4 file> <name of output + .avi> <interval between frames in ms>
```
you are provided with one .mp4 file, for exmple you can run:
```
make
./VideoProcessor stream_part6.mp4 exampleOutput.avi 40
``` 
to clean the .o files from your folder run:
```
make clean
```

