#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    // First we declare the variables we are going to use
    cv::Mat image, cannyImg;
    const std::string window_name = "Canny Demo - Edge Detector";
    int thres1 = 2;
    int thres2 = 1;
    bool L2 = false;

    std::string imageName = "Resources/lambo.png";
    image = cv::imread(cv::samples::findFile(imageName), cv::IMREAD_COLOR); // Load an image

    // Check if image is loaded fine
    if (image.empty())
    {
        printf("Error opening image: %s\n", imageName.c_str());
        return EXIT_FAILURE;
    }
    for (;;)
    {        
        //apply filter and show result
        cv::Canny(image, cannyImg, thres1, thres2, 3, L2);
        cv::imshow(window_name, cannyImg);

        //get key inputs to change the variables
        char key = (char)cv::waitKey(0);
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