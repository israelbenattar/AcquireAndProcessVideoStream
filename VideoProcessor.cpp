#include "StreamCapture.hpp"
#include <unistd.h>
#include <chrono>
#include <iostream>

auto start = high_resolution_clock::now() ;
void frameProcess(Mat* frame)
{   
    Mat frame_HSV, frame_threshold;
    // int low_H = 0, low_S = 0, low_V = 0;
    // int high_H = 179, high_S = 255, high_V = 255;
    // circle( *frame, pos, 20, Scalar( rand() % 255, rand() % 255, rand() % 255 ), FILLED, LINE_8 );
    // cvtColor(*frame ,*frame , COLOR_BGR2HSV);
    // inRange(*frame, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), *frame);

    // Convert to graycsale
    Mat img_gray;
    cvtColor(*frame, img_gray, COLOR_BGR2GRAY);
    // Blur the image for better edge detection
    Mat img_blur;
    GaussianBlur(img_gray, img_blur, Size(3,3), 0);
    
    // Sobel edge detection
    Mat sobely;
    // Sobel(img_blur, sobelx, CV_64F, 1, 0, 5);
    Sobel(img_blur, sobely, CV_64F, 0, 1, 5);
    // Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);
    // Display Sobel edge detection images
    // imshow("Sobel X", sobelx);
    // waitKey(0);
    // imshow("Sobel Y", sobely);
    // waitKey(0);
    // waitKey(0);

    // // Canny edge detection
    // Mat edges;
    // Canny(img_blur, edges, 100, 200, 3, false);
    Mat h = sobely;
    double alpha = 0.5; double beta;
    beta = ( 1.0 - alpha );
    h.convertTo(h, CV_8U);
    cvtColor(h, h, COLOR_GRAY2BGR);
    addWeighted(h, alpha, *frame, beta, 0.0, *frame);
    imwrite("out.jpeg", *frame);
    // auto end = high_resolution_clock::now();
    // duration<double> time_span = duration_cast<duration<double>>(end - start);
    // start = high_resolution_clock::now(); 
    
    // cout << time_span.count() * 1000<< endl; 
    
}


int main( int argc, char** argv ) 
{
    if(argc != 4)
    {
        cerr << "Error: not enough argument, call suold be like this:\n ./VideoProcessor <path To Input> <path To Output> <inerval in ms>\n";
        exit(EXIT_FAILURE);
    }
    // auto start = high_resolution_clock::now();
    Mat* frame;
    VideoWriter outputWriter;
    StreamCapture sc(argv[1], atoi(argv[3]));
    sc.start();

    // open the outfile and checks if it opend successfully
    outputWriter.open(argv[2], VideoWriter::fourcc('X','V','I','D'), 1000/atoi(argv[3]), Size(sc.getWidth(),sc.getHeight()));
    if (!outputWriter.isOpened()) {
        cerr << "Error: outputWriter Could not open the output\n";
        exit(EXIT_FAILURE);
    }

    frame = new Mat();
    start = high_resolution_clock::now();
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