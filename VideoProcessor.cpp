#include "StreamCapture.hpp"
#include "opencv2/opencv.hpp"
#include <unistd.h>



int main( int argc, char** argv ) 
{
    Mat frame, fgMask;
    VideoWriter outputWriter;
    StreamCapture sc(argv[1]);
    sc.start();
    
    string outPath = string(argv[2]) +  string(".avi");
    outputWriter.open(outPath, VideoWriter::fourcc('X','V','I','D'), sc.getFps(), Size(sc.getWidth(),sc.getHeight()));
    if (!outputWriter.isOpened()) {
        cerr << "Error: Could not open the output outputVideoWriter outputWriter file for write\n";
        exit(1);
    }

    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorMOG2();

    while (true)
    {
        frame = sc.getFrame();
        if(sc.endOfFile() & frame.empty())
        {
            break;
        }
        if(frame.empty())
        {
            double r = ((double) rand() / (RAND_MAX));
            usleep(r * 60 * 1000); 
        }
        else
        {
            // Scalar color = Scalar(0, 0, 255);       //define desired color
            // Mat mask = Mat(frame.rows, frame.cols, CV_8UC3, color);     //create a mask of such color
            // Mat result;
            // addWeighted(frame, 0.5, mask, 0.5, 0, result, CV_8UC3); 
            // pBackSub->apply(frame, fgMask);
 
            // imwrite("out.jpeg", fgMask);
        
            outputWriter << frame;
        }
    }
    outputWriter.release();
    return 0;
}