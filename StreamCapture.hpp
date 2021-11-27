#ifndef _STREAMCAPTURE_HPP
#define _STREAMCAPTURE_HPP

// ------------------------------ includes ------------------------------
#include "opencv2/opencv.hpp"
#include <pthread.h>
#include <unistd.h>

using namespace cv;
using namespace std;

/**
 * @brief 
 * 
 */
class StreamCapture
{
private:

    // VideoCapture to the stream
    VideoCapture cap;

    // queue of readed frames 
    queue<Mat> frames;
    Mat* currFrame; 
    
    // the width of the stream frames
    int frameWidth;

    // the height of the stream frames
    int frameHeight;

    // the fps rate of the stream
    double fps;

    // flag for end of file
    bool eof;

public:

    /**
     * @brief Construct a new Stream Capture:: Stream Capture object
     * 
     * @param video_path A path to a video file
     */
    StreamCapture(string video_path);

    /**
     * @brief Destroy the Stream Capture:: Stream Capture object
     */
    ~StreamCapture();

    /**
     * @brief Read the video stream until the end of the stream in const intarvel of 40ms
     * 
     * @param ptr pointer to a StreamCapture object
     * @return void* return NULL
     */
    void start();

    /**
     * @brief This function create a thread that will start read the video stream.
     */
    static void* readFrame(void* arg);

    /**
     * @brief Get the next frame from frames
     * 
     * @return Mat The frame if avilable
     */
    Mat getFrame();

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
    bool endOfFile();

    /**
     * @return int the height of the stream fream
     */
    int getHeight();

    /**
     * @return int the width of the stream fream
     */
    int getWidth();

    /**
     * @return double the fream par second rate of the stream
     */
    double getFps();
};
#endif // _STREAMCAPTURE_HPP