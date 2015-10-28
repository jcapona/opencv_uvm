/**
Saves the result of applying a mask to an image. 
*/

#include <iostream>
#include <cv.h>
#include <highgui.h>

unsigned int histogram[256][256][256];

int main(int argc, char **argv)
{
  if(argc != 3)
  {
   std::cerr << "Use: $./mask image mask\n";
   return -1;
  }
  
  cv::Mat image = cv::imread(argv[1],1); // Read image
  if(!image.data) // Check for invalid input
  {
   std::cerr << "Could not open or find the image\n";
   return -1;
  }
 
  cv::Mat mask = cv::imread(argv[2],1); // Read image
  if(!mask.data) // Check for invalid input
  {
   std::cerr << "Could not open or find the mask image\n";
   return -1;
  }
 
 cv::Mat output = cv::Mat(cv::Size(image.cols, image.rows), CV_8UC3);
 image.copyTo(output, mask); // Performs mask operation

 cv::namedWindow("Original",cv::WINDOW_NORMAL);
 cv::imshow("Original", image);
 cv::namedWindow("Mask",cv::WINDOW_NORMAL);
 cv::imshow("Mask", mask);
 cv::namedWindow("Result",cv::WINDOW_NORMAL);
 cv::imshow("Result", output); 

 try
 {
  cv::imwrite("mask_result.jpg", output);
 }
 catch(std::runtime_error& ex) 
 {
   std::cout << "Exception saving images: " << ex.what() <<"\n";
   return 1;
 }
 
 cv::waitKey(0);
 return 0;
}
