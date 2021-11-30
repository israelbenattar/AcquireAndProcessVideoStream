//  @section DESCRIPTION
//  This program reads MP4 file and simulates video stream reading at const intervals of _interval ms
//  Input : path to the mp4 file, cons interval in ms

#ifndef _STREAMCAPTURE_HPP
#define _STREAMCAPTURE_HPP

#include "opencv2/opencv.hpp"
#include <pthread.h>
#include <chrono>
#include <unistd.h>

using namespace cv;
using namespace std;
using namespace std::chrono;

class StreamCapture
{
private:

    // VideoCapture to the stream
    VideoCapture _cap;

    // queue of readed frames 
    queue<Mat*>* _frames;
    
    // the width of the stream frames
    int _frameWidth;

    // the height of the stream frames
    int _frameHeight;

    // the fps rate of the stream
    double _fps;

    // flag for end of file
    bool _eof;

    // time in ms from frame to frame
    int _interval;

    /**
     * @brief Read the video stream until the end of the stream in const intarvel of 40ms
     * 
     * @param ptr pointer to a StreamCapture object
     * @return void* return NULL
     */

    static void* _readFrame(void* ptr);

public:

    /**
     * @brief Construct a new Stream Capture:: Stream Capture object
     * 
     * @param video_path A path to a video file
     */
    StreamCapture(string video_path, int ms);

    /**
     * @brief Destroy the Stream Capture:: Stream Capture object
     */
    ~StreamCapture();

     /**
     * @brief This function create a thread that will start read the video stream.
     */
    void start();

    /**
     * @brief Get the next frame from frames
     * 
     * @return Mat The frame if avilable
     */
    void getFrame(Mat* frame);

    /**
     * @brief checks if the fraem queue is empty
     * 
     * @return true if the freams queue is empty, else false
     */
    bool empty();

    /**
     * @brief checks if the stream is ended
     * 
     * @return true if the stream is ended, else false
     */
    bool endOfFile() {return _eof;}

    /**
     * @return int the height of the stream fream
     */
    int getHeight() {return _frameHeight;}

    /**
     * @return int the width of the stream fream
     */
    int getWidth() {return _frameWidth;}

    /**
     * @return double the fream par second rate of the stream
     */
    double getFps() {return _fps;}
};
#endif // _STREAMCAPTURE_HPP