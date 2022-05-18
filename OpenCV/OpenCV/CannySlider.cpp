#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{

    // First we declare the variables we are going to use
    Mat image, cannyImg;
    const String window_name = "Canny Demo - Edge Detector";
    int thres1 = 2;
    int thres2 = 1;
    bool L2 = false;

    String imageName = "Resources/lambo.png";
    // As usual we load our source image (src)
    image = imread(samples::findFile(imageName), IMREAD_COLOR); // Load an image
    // Check if image is loaded fine
    if (image.empty())
    {
        printf("Error opening image: %s\n", imageName.c_str());
        return EXIT_FAILURE;
    }
    for (;;)
    {
        // Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
        
        cv::Canny(image, cannyImg, thres1, thres2, 3, L2);
        cv::imshow(window_name, cannyImg);
        char key = (char)waitKey(0);
        if (key == 27)
        {
            return EXIT_SUCCESS;
        }
        if (key == 'w' || key == 'W')
        {
            thres1+=10;
        }
        if (key == 's' || key == 'S')
        {
            thres1-=10;
        }
        if (key == 'e' || key == 'E')
        {
            thres2+=10;
        }
        if (key == 'd' || key == 'D')
        {
            thres2-=10;
        }

        if (key == 'h' || key == 'H') {
            L2 = !L2;
        }
        if (key == 'r' || key == 'R')
        {
            thres1 = 2;
            thres2 = 1;
            L2 = false;
        }
    }
    return EXIT_SUCCESS;
}