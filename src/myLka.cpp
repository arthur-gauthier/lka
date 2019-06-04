//============================================================================
// Name        : myLka.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void Detect();

int main() {
	cout << "!!! Hello World !!" << endl; // prints !!!Hello World!!!
	Detect();
	return 0;
}

extern void colorthresh(cv::Mat input, cv::Mat* ouput);
extern void findBoundingRect(cv::Mat input, cv::Mat* output);

void Detect() {

	cv::Mat img = imread("/home/ubuntu/git/lka/inputImage.png");
	if (!img.empty()) {
//     cv::namedWindow("Turtlebot View");
//     imshow("Turtlebot View", img);
//     cv::waitKey(2500);

		// Perform image processing
		// cv::Mat img = Gauss(maskGauss); //BIP removed it because for the moment i do not want to smooth the edges ; impacts below arg
		cv::Mat colorthresh_image;
		colorthresh(img, &colorthresh_image);
		findBoundingRect(colorthresh_image, &img);
	}
}

cv::Mat Gauss(cv::Mat input) {
	cv::Mat output;
	// Applying Gaussian Filter
	cv::GaussianBlur(input, output, cv::Size(5, 5), 0.1, 0.1); //kernel size = (3,3)
	return output;
}

void colorthresh(cv::Mat input, cv::Mat* img_mask) {
	// Initializaing variables
	cv::Size s = input.size();
	auto w = s.width;
	auto h = s.height;
	// Detect all objects within the HSV range
	cv::Mat img_hsv;

	cv::cvtColor(input, img_hsv, CV_BGR2HSV);
	cv::namedWindow("img_hsv");
	imshow("img_hsv", img_hsv);
	cv::waitKey(10);
	//	LowerYellow and UpperYellow in BGR format
	cv::Scalar LowerYellow = { 10, 100, 100 }; //before {10,100,100}
	cv::Scalar UpperYellow = { 30, 255, 255 };
	cv::inRange(img_hsv, LowerYellow, UpperYellow, *img_mask);
	//img_mask(cv::Rect(0, 0, w, 0.8*h)) = 0;
	cv::namedWindow("mask on HSV");
	imshow("mask on HSV", *img_mask);
	cv::waitKey(2500);
}

void findBoundingRect(cv::Mat input, cv::Mat* output) {

	// Perform centroid detection of line (important to do it after the findContours otherwise the circle drawned will be contoured !)
	auto c_x = 0.0;
	cv::Moments M = cv::moments(input);
	if (M.m00 > 0) {
		cv::Point p1(M.m10 / M.m00, M.m01 / M.m00);
		cv::circle(*output, p1, 5, cv::Scalar(155, 200, 0), -1);
	}
	c_x = M.m10 / M.m00;

//	std::vector<std::vector<cv::Point> > v;
	// Find contours for better visualisation
//	cv::findContours(input, v, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
//	if (v.size() != 0) {
//		auto area = 0;
//		auto idx = 0;
//		auto count = 0;
//		while (count < v.size()) {
//			if (area < v[count].size()) {
//				idx = count;
//				area = v[count].size();
//			}
//			count++;
//		}
//
//		cv::Rect rect = boundingRect(v[idx]);
//		cv::Point pt1, pt2, pt3, ptmid;
//		pt1.x = rect.x;
//		pt1.y = rect.y;
//		pt2.x = rect.x + rect.width;
//		pt2.y = rect.y + rect.height;
//		// for text start point
//		pt3.x = pt1.x + 5;
//		pt3.y = pt1.y - 5;
//		//middle of the rectangle
//		ptmid.x = rect.x + rect.width / 2;
//		ptmid.y = rect.y + rect.height / 2;
//		// Drawing the rectangle using points obtained
//		rectangle(*output, pt1, pt2, CV_RGB(0, 255, 255), 2);
//		circle(*output, ptmid, 5, cv::Scalar(155, 200, 0), -1);
//	}
	cv::namedWindow("bounding rect");
	imshow("bounding rect", *output);
	cv::waitKey(10000);

}

