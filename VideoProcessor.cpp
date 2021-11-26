#include "StreamCapture.cpp"
#include "opencv2/opencv.hpp"
#include <unistd.h>



int main( int argc, char** argv ) 
{
    Mat frame;
    VideoWriter outputWriter;
    StreamCapture sc(argv[1]);
    sc.start();
    
    outputWriter.open(argv[2], VideoWriter::fourcc('X','V','I','D'), sc.getFps(), Size(sc.getWidth(),sc.getHeight()));
    if (!outputWriter.isOpened()) {
        cerr << "Error: Could not open the output outputVideoWriter outputWriter file for write\n";
        exit(1);
    }

    while (true)
    {
        if(sc.endOfFile() & sc.empty())
        {
            break;
        }
        if(sc.empty())
        {
            double r = ((double) rand() / (RAND_MAX));
            usleep(r * 60 * 1000); 
        }
        else
        {
            frame = sc.getFrame();
            if(frame.empty())
            {
                cout << frame.size() << endl;
                break;
            }
            outputWriter << frame;
        }
    }
    outputWriter.release();
    
}