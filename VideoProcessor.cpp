#include "StreamCapture.hpp"
#include <unistd.h>
#include <chrono>
#include <iostream>

/**
 * @brief this function applay the sobel edge detection on the frame and 
 * blend the frame with the image of its edge. 
 * 
 * @param frame pointer to a Mat object
 */
void frameProcess(Mat* frame)
{   
    // Convert to graycsale
    Mat img_gray;
    cvtColor(*frame, img_gray, COLOR_BGR2GRAY);

    // Blur the image for better edge detection
    Mat img_blur;
    GaussianBlur(img_gray, img_blur, Size(3,3), 0);
    

    // compute the edges of the frame
    Mat sobelxy;
    Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);

    double alpha = 0.5; double beta;
    beta = ( 1.0 - alpha );

    // convert the sobelxy from gray to bgr
    sobelxy.convertTo(sobelxy, CV_8U);
    cvtColor(sobelxy, sobelxy, COLOR_GRAY2BGR);

    // blend the tow images
    addWeighted(sobelxy, alpha, *frame, beta, 0.0, *frame);
    
}


int main( int argc, char** argv ) 
{
    if(argc != 4)
    {
        cerr << "Error: not enough argument, call suold be like this:\n \
                ./VideoProcessor <path To Input> <path To Output> <inerval in ms>\n";
        exit(EXIT_FAILURE);
    }
    // auto start = high_resolution_clock::now();
    Mat* frame;
    VideoWriter outputWriter;
    StreamCapture sc(argv[1], atoi(argv[3]));
    sc.start();

    // open the outfile and checks if it opend successfully
    outputWriter.open(argv[2], VideoWriter::fourcc('X','V','I','D'), 
                      1000/atoi(argv[3]), Size(sc.getWidth(),sc.getHeight()));

    if (!outputWriter.isOpened()) {
        cerr << "Error: outputWriter Could not open the output\n";
        exit(EXIT_FAILURE);
    }

    frame = new Mat();
    while (true)
    {
        //get a frame from the StreamCapture object
        sc.getFrame(frame);

        //if frame is empty and sc.endOfFile() is true than we finish to read the stream frames.
        if(sc.endOfFile() & frame->empty())
        {
            break;
        }

        //if frame is empty and sc.endOfFile() is false than we wait to anoter frame.
        if(frame->empty())
        {
            //sleep for random time betwen 0ms to 60ms
            double r = ((double) rand() / (RAND_MAX));
            usleep(r * 60 * 1000); 
        }
        else
        {
            // process the frame
            frameProcess(frame);

            //write to the output file
            outputWriter << *frame;

        }
    }
    // release resurcas
    outputWriter.release();
    delete frame;
    return 0;
}