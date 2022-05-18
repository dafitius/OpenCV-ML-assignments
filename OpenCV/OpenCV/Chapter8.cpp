#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

///////////////  Images  //////////////////////

void main() {

	std::string path = "Resources/faces.jpg";
	cv::Mat img = cv::imread(path);

	cv::CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");

	if (faceCascade.empty()) { std::cout << "XML file not loaded" << std::endl; }

	std::vector<cv::Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);

	for (int i = 0; i < faces.size(); i++)
	{
		cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);
	}

	cv::imshow("Image", img);
	cv::waitKey(0);
}