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

int main() {
<<<<<<< HEAD
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!


=======
	cout << "!!! Hello World !!!" << endl; // prints !!!Hello World!!!
>>>>>>> branch 'master' of https://github.com/arthur-gauthier/lka.git
	return 0;
}


extern cv::Mat colorthresh(cv::Mat input);

void Detect()
{

//  pthread_mutex_lock(&mutex_img);
  cv::Mat img = imread("./../inputImage.png"); //RTE_Subscribe_CameraRgbImage_raw();
  if (!img.empty())
  { //BIP before : det->img
    // cv::namedWindow("Turtlebot View");
    // imshow("Turtlebot View", img);
    // cv::waitKey(25);

    // Perform image processing
    // cv::Mat img = Gauss(maskGauss); //BIP removed it because for the moment i do not want to smooth the edges ; impacts below arg
    cv::Mat mask = colorthresh(img);

//    RTE_Write_ImgOut(mask);


    // cv::namedWindow("Colorthresh View");
    // imshow("Colorthresh View", mask);
    // cv::waitKey(25);
  }
//  pthread_mutex_unlock(&mutex_img);
}

cv::Mat Gauss(cv::Mat input)
{
  cv::Mat output;
// Applying Gaussian Filter
  cv::GaussianBlur(input, output, cv::Size(5, 5), 0.1, 0.1); //kernel size = (3,3)
  return output;
}

cv::Mat colorthresh(cv::Mat input)
{
  // Initializaing variables

  // cv::namedWindow("input");
  // imshow("input", input);
  // cv::waitKey(10);

  //BIP : undistort, get_binary_image -> sobel and channel selection for HLS skipped

  cv::Size s = input.size();
  // std::vector<std::vector<cv::Point> > v;
  auto w = s.width;
  auto h = s.height;
  // Detect all objects within the HSV range
  // cv::Mat img_hsv;
  // cv::Mat img_mask;
  // Detect all objects within the HLS range
  cv::Mat img_hls;
  cv::Mat img_mask_hls;

  // cv::cvtColor(input, img_hsv, CV_BGR2HSV); //HSV is covers less the lines than HLS, and when blue paint on turns, distinct it more but we dont want that
  // cv::namedWindow("img_hsv");
  // imshow("img_hsv", img_hsv);
  // cv::waitKey(10);
  //LowerYellow and UpperYellow in BGR format
  // cv::Scalar LowerYellow = {10,100,100}; //before {10,100,100}
  // cv::Scalar UpperYellow = {30, 255, 255};
  // cv::inRange(img_hsv, LowerYellow, UpperYellow, img_mask);
  // //img_mask(cv::Rect(0, 0, w, 0.8*h)) = 0;
  // cv::namedWindow("mask on HSV");
  // imshow("mask on HSV", img_mask);
  // cv::waitKey(10);

  cv::cvtColor(input, img_hls, CV_RGB2HLS); //CV_BGR2HLS
  // cv::namedWindow("img_hls");
  // imshow("img_hls", img_hls);
  // cv::waitKey(10);

  cv::Scalar LowerRed = {10, 0, 100};
  cv::Scalar UpperRed = {30, 70, 255};
  cv::inRange(img_hls, LowerRed, UpperRed, img_mask_hls);
  //img_mask(cv::Rect(0, 0, w, 0.8*h)) = 0; //BIP commented bc all the view interest us
  // cv::namedWindow("mask on HLS");
  // imshow("mask on HLS", img_mask_hls);
  // cv::waitKey(10);

  // Mask image to limit the future turns affecting the output
  // img_mask(cv::Rect(0.7*w, 0, 0.3*w, h)) = 0;
  // img_mask(cv::Rect(0, 0, 0.3*w, h)) = 0;
  return img_mask_hls;
}
