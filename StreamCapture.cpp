// ------------------------------ includes ------------------------------
#include "opencv2/opencv.hpp"
#include <pthread.h>
#include <atomic>
#include <unistd.h>

using namespace cv;
using namespace std;

class StreamCapture
{
private:
    queue<Mat*> frames; 

public:
VideoCapture cap;
    int frameWidth;
    int frameHeight;
    StreamCapture(String video_path);
    ~StreamCapture();
    void start();
    static void* readFrame(void* arg);
    Mat* getFrame();
    bool empty();
    bool EFO;
    atomic<bool> readed;
};


/**
 * @brief Construct a new Stream Capture:: Stream Capture object
 * 
 * @param video_path A path to a video file
 */
StreamCapture::StreamCapture(String video_path)
{
    cap = VideoCapture(video_path);

    frameWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    frameHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    //Checks if the file was opened successfully
    if(!cap.isOpened()){
        cerr << "Error: Cannot open video stream or file" << endl;
        exit(1);
    }

    EFO = false;
    readed = false;

}


/**
 * @brief Destroy the Stream Capture:: Stream Capture object
 */
StreamCapture::~StreamCapture()
{
}


/**
 * @brief Read the video stream frame by frame
 * 
 * @param ptr pointer to a StreamCapture object
 * @return void* return NULL
 */
void* StreamCapture::readFrame(void* ptr)
{
    StreamCapture* sc = (StreamCapture*) ptr;
    while (true)
    {
        Mat frame;
        sc->cap >> frame;

        //Checks if end of stream
        if (frame.empty())
        {
            sc->EFO = true; 
            break;
        }
        
        sc->frames.push(&frame);
        // cout << frame.size() << endl;
        usleep(40);

    }
    
}

/**
 * @brief This function create a thread that will start read the video stream.
 */
void StreamCapture::start()
{
    pthread_t threadId;
    pthread_attr_t* threadAttr;
    int res = pthread_create(&threadId, NULL, &StreamCapture::readFrame, this);

    //Checks if the thread was created successfully
    if (res)
    {
        cerr << "Error: pthred_create failed." <<endl;
        exit(1);
    }
    
}

Mat* StreamCapture::getFrame()
{
    readed = true;
    Mat* frame = frames.front();
    frames.pop();
    return frame;
}

bool StreamCapture::empty()
{
    return frames.empty();
}
