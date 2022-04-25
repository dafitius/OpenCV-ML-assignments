//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
////////////////  Draw Shapes and Text //////////////////////
//
//void main() {
//
//	// Blank Image 
//	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
//
//	circle(img, Point(256, 256), 155, Scalar(70, 180, 255), FILLED);
//	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
//	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);
//
//	putText(img, "Daan en David", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(36, 49, 255), 2);
//
//	imshow("Image", img);
//	waitKey(0);
//}