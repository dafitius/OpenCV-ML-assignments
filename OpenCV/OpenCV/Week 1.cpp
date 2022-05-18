#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


void customFilter(cv::Mat& src, cv::Mat& dst);

///////////////  Images  //////////////////////

void main() {

	std::string path = "Resources/sleutel.jpg";
	cv::Mat img = cv::imread(path);
    cv::Mat imgGray, imgBlur, imgBlur2, imgBlur3, imgBlur4;
    cv::Mat imgCustom;

	cvtColor(img, imgGray, cv::ColorConversionCodes::COLOR_BGR2RGB);
	GaussianBlur(img, imgBlur,  cv::Size(1, 1), 1, 0);
	GaussianBlur(img, imgBlur2, cv::Size(3, 3), 3, 0);
	GaussianBlur(img, imgBlur3, cv::Size(5, 5), 5, 0);
	GaussianBlur(img, imgBlur4, cv::Size(11, 11), 11, 0);
    customFilter(img, imgCustom);

	imshow("Image", img);
	//imshow("Image Gray", imgGray);
    imshow("custom filter", imgCustom);

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

///////////////  Video  //////////////////////

//void main() {
//
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true) {
//
//		cap.read(img);
//		imshow("Image", img);
//		waitKey(20);
//	}
//}


/////////////////  Webcam  //////////////////////

//void main() {
//
//	VideoCapture cap(0);
//	Mat img;
//
//	while (true) {
//
//		cap.read(img);
//		imshow("Image", img);
//		waitKey(1);
//	}
//}
