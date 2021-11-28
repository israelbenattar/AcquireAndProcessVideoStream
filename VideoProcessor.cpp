#include "StreamCapture.hpp"
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <chrono>
#include "opencv2/ximgproc/segmentation.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <ctime>
using namespace std::chrono;
using namespace cv::ximgproc;
using namespace segmentation;

int edgeDetection(Mat frame, char t)
{
    // speed-up using multithreads
    // setUseOptimized(true);
    // setNumThreads(4);

    // // read image
    // Mat im = frame;
    // // resize image
    // int newHeight = 200;
    // int newWidth = im.cols*newHeight/im.rows;
    // resize(im, im, Size(newWidth, newHeight));

    // // create Selective Search Segmentation Object using default parameters
    // Ptr<SelectiveSearchSegmentation> ss = createSelectiveSearchSegmentation();
    // // set input image on which we will run segmentation
    // ss->setBaseImage(im);

    // // Switch to fast but low recall Selective Search method
    // if (t == 'f') {
    //     ss->switchToSelectiveSearchFast();
    // }
    // // Switch to high recall but slow Selective Search method
    // else if (t == 'q') {
    //     ss->switchToSelectiveSearchQuality();
    // }

    // // run selective search segmentation on input image
    // std::vector<Rect> rects;
    // ss->process(rects);
    // std::cout << "Total Number of Region Proposals: " << rects.size() << std::endl;

    // // number of region proposals to show
    // int numShowRects = 100;
    // // increment to increase/decrease total number
    // // of reason proposals to be shown
    // int increment = 50;

    // while(1) {
    //     // create a copy of original image
    //     Mat imOut = im.clone();

    //     // itereate over all the region proposals
    //     for(int i = 0; i < rects.size(); i++) {
    //         if (i < numShowRects) {
    //             rectangle(imOut, rects[i], Scalar(0, 255, 0));
    //         }
    //         else {
    //             break;
    //         }
    //     }

    //     // show output
    //     imwrite("out.jpeg", imOut);

    //     // record key press
    //     int k = waitKey();

    //     // m is pressed
    //     if (k == 109) {
    //         // increase total number of rectangles to show by increment
    //         numShowRects += increment;
    //     }
    //     // l is pressed
    //     else if (k == 108 && numShowRects > increment) {
    //         // decrease total number of rectangles to show by increment
    //         numShowRects -= increment;
    //     }
    //     // q is pressed
    //     else if (k == 113) {
    //         break;
    //     }
    // }
    // Mat alpha;
    // Mat foreground = frame;
    // Mat background;
    // cvtColor(foreground, background, cv::COLOR_BGR2GRAY);
    // cvtColor(background, background, cv::COLOR_GRAY2BGR);
    // Ptr<BackgroundSubtractor> pBackSub;
    // pBackSub = createBackgroundSubtractorKNN();
    // pBackSub->apply(foreground, alpha);
    // cvtColor(alpha, alpha, cv::COLOR_GRAY2BGR);

    // foreground.convertTo(foreground, CV_32FC3);
    // background.convertTo(background, CV_32FC3);

    // alpha.convertTo(alpha, CV_32FC3, 1.0/255);
    
    //     // Storage for output image
    // Mat ouImage = Mat::zeros(foreground.size(), foreground.type());

    // // Multiply the foreground with the alpha matte
    // multiply(alpha, foreground, foreground); 

    // // Multiply the background with ( 1 - alpha )
    // multiply(Scalar::all(1.0)-alpha, background, background); 

    // // Add the masked foreground and background.
    // add(foreground, background, ouImage); 

    // // Display image
    // imwrite("out.jpeg", ouImage);
       
//     // HSV range to detect blue color
//     int minHue = 90, maxHue = 140;
//     int minSat = 74, maxSat = 255;
//     int minVal =  0, maxVal = 255;

//     // Create trackbars in mask settings window
//     // cvCreateTrackbar("Min Hue", MASK_WINDOW, &minHue, 179);
//     // cvCreateTrackbar("Max Hue", MASK_WINDOW, &maxHue, 179);
//     // cvCreateTrackbar("Min Sat", MASK_WINDOW, &minSat, 255);
//     // cvCreateTrackbar("Max Sat", MASK_WINDOW, &maxSat, 255);
//     // cvCreateTrackbar("Min Val", MASK_WINDOW, &minVal, 255);
//     // cvCreateTrackbar("Max Val", MASK_WINDOW, &maxVal, 255);
//     // Convert to graycsale
//     // Mat out;
//     // cvtColor(frame, out, COLOR_BGR2GRAY);
//     Mat inputVideo;
//     cv::flip(frame, inputVideo, 1);
//     cv::Mat inputVideoHSV;
//     cv::cvtColor(inputVideo, inputVideoHSV, cv::COLOR_BGR2HSV);

//     //// 4. Create mask and result (masked) video
//     cv::Mat mask;
//     // params: input array, lower boundary array, upper boundary array, output array
//     cv::inRange(
//         inputVideoHSV, 
//         cv::Scalar(minHue, minSat, minVal), 
//         cv::Scalar(maxHue, maxSat, maxVal), 
//         mask
//     );
//     cv::Mat resultVideo;
//     // params: src1	array, src2 array, output array, mask
//     cv::bitwise_and(inputVideo, inputVideo, resultVideo, mask);



    
//     // // // Sobel edge detection
//     // // Mat sobelx, sobely, sobelxy;
//     // // Sobel(img_blur, sobelx, CV_64F, 1, 0, 5);
//     // // Sobel(img_blur, sobely, CV_64F, 0, 1, 5);
//     // // Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);
//     // // // Display Sobel edge detection images
//     // // imshow("Sobel X", sobelx);
//     // // waitKey(0);
//     // // imshow("Sobel Y", sobely);
//     // // waitKey(0);
//     // Set threshold and maxValue

//     // double thresh = 100;


//     // double maxValue = 255;

 

//     // Binary Threshold

//     // threshold(out,out, thresh, maxValue, THRESH_BINARY);

    

//     // // Canny edge detection
    Mat imageGray, imageBlur, edges, mask;
    cvtColor(frame, imageGray, CV_BGR2HSV);
    // GaussianBlur(imageGray, imageBlur, Size(3, 3), 3, 0);
    // Canny(imageBlur, edges, 30, 75, 3, false);
//     // // // Display canny edge detected image
//     // // imshow("Canny edge detection", edges);
    // max 179    max 255  max255 
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imageGray, lower, upper, mask);
    imwrite("out.jpeg", mask);
//     // // waitKey(0);
    // Ptr<BackgroundSubtractor> pBackSub;
    // pBackSub = createBackgroundSubtractorMOG2();
    // Scalar color = Scalar(0, 0, 255);       //define desired color
    // Mat mask = Mat(frame.rows, frame.cols, CV_8UC3, color);     //create a mask of such color
    // Mat result;
    // addWeighted(frame, 0.5, mask, 0.5, 0, result, CV_8UC3); 
    // pBackSub->apply(frame, fgMask);

    // imwrite("out.jpeg", fgMask);

    // edgeDetection(frame, 'f');
    // cout << frame.size() << endl;
    
    
    return 0;
}



int main( int argc, char** argv ) 
{
    auto start = high_resolution_clock::now();
    Mat* frame;
    VideoWriter outputWriter;
    StreamCapture sc("./stream_part6.mp4");
    sc.start();
    
    string outPath = string(argv[2]) +  string(".avi");
    outputWriter.open(outPath, VideoWriter::fourcc('X','V','I','D'), sc.getFps(), Size(sc.getWidth(),sc.getHeight()));
    if (!outputWriter.isOpened()) {
        cerr << "Error: Could not open the output outputVideoWriter outputWriter file for write\n";
        exit(1);
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
            //write the frame to the output file.
            outputWriter << *frame;
        }
    }
    outputWriter.release();
    delete frame;
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count()/1000 << endl;
    return 0;
}