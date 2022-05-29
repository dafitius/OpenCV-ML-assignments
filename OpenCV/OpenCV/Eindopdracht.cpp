#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


int getContours(cv::Mat imgDil, cv::Mat img) {

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//std::cout << area << std::endl;
		std::string objectType;

		if (area > 2)
		{
			
			
			float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
			if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Letter"; }
			else { objectType = "Word"; }
			

			//drawContours(img, 4, i, cv::Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 69, 255), 1);
		}
	}

	return contours.size();
}


void main() {
	std::string path = "Resources/document.png";
	cv::Mat img = cv::imread(path);
	cv::Mat matrix, imgWarpWords;
	float w = 900, h = 1080;

	cv::Point2f src[4] = { {237,181},{727,235},{78,918},{686,999} };
	cv::Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarpWords, matrix, cv::Point(w, h));

	for (int i = 0; i < 4; i++)
	{
		circle(img, src[i], 10, cv::Scalar(0, 0, 255), cv::FILLED);
	}

	cv::Mat imgGray, imgErode, imgCanny, imgWordDil, imgLetterDil;

	//convert the image to grayscale
	cvtColor(imgWarpWords, imgGray, cv::COLOR_BGR2GRAY);

	
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
	erode(imgGray, imgErode, kernel); //erode the image to separate the individual characters more.
	Canny(imgErode, imgCanny, 192, 131, 3, false); //canny the image to get all the lines.
	kernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(6, 6)); //increase the kernel size
	dilate(imgCanny, imgWordDil, kernel); //dilate the image to "glue" together characters that close to eachother. creates word blobs.

	imgLetterDil = imgCanny;

	cv::Mat imgWarpLetters = imgWarpWords;

	float expectedWordCount = 160;
	float wordCount = getContours(imgWordDil, imgWarpWords);
	float wordAccuracy = (expectedWordCount / wordCount) * 100.0f;
	if (wordAccuracy > 100) wordAccuracy = 100 - wordAccuracy;

	std::cout << "amount of words: " << wordCount << ", we excepted " << expectedWordCount << " so that's " << wordAccuracy << "% accurate" << std::endl;
	
	float expectedLetterCount = 697;
	float letterCount = getContours(imgLetterDil, imgWarpLetters);
	float letterAccuracy = (expectedLetterCount / letterCount) * 100.0f;
	if (letterAccuracy > 100) letterAccuracy = 100 - letterAccuracy;

	std::cout << "amount of characters: " << letterCount << ", we excepted " << expectedLetterCount << " so that's " << letterAccuracy << "% accurate" << std::endl;

	imshow("Image", img);
	imshow("word", imgWordDil);
	imshow("letter", imgLetterDil);
	imshow("Image Warp words", imgWarpWords);
	imshow("Image Warp letters", imgWarpLetters);
	cv::waitKey(0);
}