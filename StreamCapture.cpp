#include "StreamCapture.hpp"

// a mutex for the critical part. (eg. read and write to the fram queue)
pthread_mutex_t frameLock;

/**
 * @brief Construct a new Stream Capture:: Stream Capture object
 * 
 * @param video_path A path to a video file
 */
StreamCapture::StreamCapture(string video_path, int ms)
{
    _cap = VideoCapture(video_path);

    // checks if the file was opened successfully
    if(!_cap.isOpened()){
        cerr << "Error: Cannot open video stream or file" << endl;
        exit(EXIT_FAILURE);
    }

    // checks if the mutex was init successfully
    if(pthread_mutex_init(&frameLock, NULL)){
        cerr << "Error: Cannot init mutex" << endl;
        exit(EXIT_FAILURE);
    }

    // init the global var
    _frames = new queue<Mat*>;
    _interval = ms;
    _fps = _cap.get(CAP_PROP_FPS);
    _frameWidth = _cap.get(CAP_PROP_FRAME_WIDTH);
    _frameHeight = _cap.get(CAP_PROP_FRAME_HEIGHT);
    _eof = false;

}

/**
 * @brief Destroy the Stream Capture:: Stream Capture object
 */
StreamCapture::~StreamCapture()
{
    pthread_mutex_destroy(&frameLock);
    delete _frames;
    _cap.release();
}

/**
 * @brief Read the video stream until the end of the stream in const intarvel of 40ms
 * 
 * @param ptr pointer to a StreamCapture object
 * @return void* return NULL
 */
void* StreamCapture::_readFrame(void* ptr)
{
    Mat *frame;
    StreamCapture* sc = (StreamCapture*) ptr;

    // run until we get to the end of file
    while (true)
    {
        auto start = high_resolution_clock::now();
        
        // read a frame from the stream
        frame = new Mat();
        sc->_cap >> *frame;

        // check if we get to the end of the stream
        if (frame->empty())
        {
            sc->_eof = true; 
            break;
            
        }

        // push the frame to the frames queue 
        pthread_mutex_lock(&frameLock);
        sc->_frames->push(frame);
        pthread_mutex_unlock(&frameLock);

        // calculate the sleeping time of the thread
        auto end = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(start - end);
        int sleepTimeMs = int(sc->_interval - time_span.count()*1000) ;

        // simulates the time between frames
        usleep(sleepTimeMs * 1000);
    }
    return NULL;
    
}

/**
 * @brief This function create a thread that will start read the video stream.
 */
void StreamCapture::start()
{
    pthread_t threadId;
    int res = pthread_create(&threadId, NULL, &_readFrame, this);


    // checks if the thread was created successfully
    if (res)
    {
        cerr << "Error: pthred_create failed." <<endl;
        exit(EXIT_FAILURE);
    }
    
}

/**
 * @brief Get the next frame from frames
 * 
 * @return Mat A frame if avilable, else an empty frame
 */
void StreamCapture::getFrame(Mat* frame)
{
    // checks if the fraem queue is empty
    if(empty())
    {
        *frame = Mat();
    }
    else
    {
        // pop the curr frame to frame
        pthread_mutex_lock(&frameLock);
        *frame = *_frames->front();
        delete _frames->front();
        _frames->pop();
        pthread_mutex_unlock(&frameLock);
    }    
}

/**
 * @brief checks if the fraem queue is empty
 * 
 * @return true if the freams queue is empty, else false
 */
bool StreamCapture::empty()
{
    return _frames->empty();
}
