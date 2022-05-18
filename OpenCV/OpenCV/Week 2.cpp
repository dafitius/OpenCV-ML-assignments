#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void customFilter(cv::Mat& src, cv::Mat& dst);

///////////////  Images  //////////////////////

void main() {

    //Opdrachten:
    bool opdracht1 = false;
    bool opdracht2 = false;
    bool opdracht3 = true;


    std::string path = "Resources/sleutel.jpg";
    cv::Mat img = cv::imread(path);
    cv::Mat imgGray, imgBlur, imgBlur2, imgBlur3, imgBlur4;
    cv::Mat imgCustom;
    cv::Mat imgCanny, imgCanny1, imgCanny2, imgCanny3, imgCanny4;

    cv::cvtColor(img, imgGray, cv::ColorConversionCodes::COLOR_BGR2RGB);
    cv::GaussianBlur(img, imgBlur, cv::Size(1, 1), 1, 0);
    cv::GaussianBlur(img, imgBlur2, cv::Size(3, 3), 3, 0);
    cv::GaussianBlur(img, imgBlur3, cv::Size(5, 5), 5, 0);
    cv::GaussianBlur(img, imgBlur4, cv::Size(11, 11), 11, 0);
    customFilter(img, imgCustom);

    cv::imshow("Image", img);
    
    if(opdracht1)imshow("Image Gray", imgGray);
    if(opdracht1)imshow("custom filter", imgCustom);

    

    cv::Canny(img, imgCanny, 25, 75);
    cv::Canny(img, imgCanny1, 50, 75);
    cv::Canny(img, imgCanny2, 25, 150);
    cv::Canny(img, imgCanny3, 50, 150);

    cv::Canny(img, imgCanny4, 25, 75, 3, true);


    if(opdracht2)cv::imshow("canny filter 0", imgCanny);
    if(opdracht2)cv::imshow("canny filter 1", imgCanny1);
    if(opdracht2)cv::imshow("canny filter 2", imgCanny2);
    if(opdracht2)cv::imshow("canny filter 3", imgCanny3);
    if(opdracht2)cv::imshow("canny filter 4", imgCanny4);



    int ddepth = CV_16S;

    cv::Mat imgSobel;
    cv::Mat greySobel;
    cv::Mat grad;
    // Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
    cv::GaussianBlur(img, imgSobel, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
    // Convert the image to grayscale
    cv::cvtColor(imgSobel, greySobel, cv::COLOR_BGR2GRAY);
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;
    cv::Sobel(greySobel, grad_x, ddepth, 1, 0, -1, 1, 0, cv::BORDER_DEFAULT);
    cv::Sobel(greySobel, grad_y, ddepth, 0, 1, -1, 1, 0, cv::BORDER_DEFAULT);
    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    if(opdracht2)cv::imshow("Sobel filter", grad);




    cv::Mat erodeImg;
    cv::Mat dilateImg;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    cv::erode(img, erodeImg, kernel);
    cv::dilate(img, dilateImg, kernel);

    if (opdracht3)cv::imshow("erode filter", erodeImg);
    if (opdracht3)cv::imshow("dilate filter", dilateImg);




    cv::waitKey(0);
}


void customFilter(cv::Mat& src, cv::Mat& dst) {
    // Declare variables
    cv::Mat kernel;
    cv::Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    // Loads an image
    if (src.empty())
        printf(" Error opening image\n");

    // Initialize arguments for the filter
    anchor = cv::Point(-1, -1);
    delta = 0;
    ddepth = -1;
    // Loop - Will filter the image with different kernel sizes each 0.5 seconds
    int ind = 0;
    for (;;)
    {
        // Update kernel size for a normalized box filter
        kernel_size = 3 + 2 * (ind % 5);

        float kdata[] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 };
        cv::Mat kernel(3, 3, CV_32F, kdata);

        // Apply filter
        filter2D(src, dst, ddepth, kernel, anchor, delta);

        return;
    }

}