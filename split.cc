#include <iostream>
#include <cv.h>
#include <highgui.h>

int main(int argc, char **argv)
{
  if(argc == 1)
  {
   std::cout << "Enter image name to process\n";
   return -1;
  }
  
  cv::Mat image = cv::imread(argv[1],1); // Read image
  if(!image.data ) // Check for invalid input
  {
   std::cerr << "Could not open or find the image\n";
   return -1;
  }
 
  // Split the image into different channels
  std::vector<cv::Mat> rgbChannels(3);
  cv::split(image, rgbChannels);

  // Show individual channels
  cv::Mat zero, img_red, img_green, img_blue;
  zero = cv::Mat::zeros(cv::Size(image.cols, image.rows), CV_8UC1);
  std::vector<cv::Mat> channels;
  
  // Red: leaves Green and Blue channels with zeros 
  channels.push_back(zero);
  channels.push_back(zero);
  channels.push_back(rgbChannels[2]);
  merge(channels, img_red); // Merges channels

  // Green: R+B in zero
  channels.clear();
  channels.push_back(zero);
  channels.push_back(rgbChannels[1]);
  channels.push_back(zero); 
  merge(channels, img_green);

  // Blue: R+G in zero
  channels.clear();
  channels.push_back(rgbChannels[0]);
  channels.push_back(zero);
  channels.push_back(zero);
  merge(channels, img_blue);
  
  // Display images
  cv::namedWindow("image",cv::WINDOW_NORMAL);
  cv::imshow("image",image);
  cv::namedWindow("Red",cv::WINDOW_NORMAL);
  cv::imshow("Red", img_red);
  cv::namedWindow("Green",cv::WINDOW_NORMAL);
  cv::imshow("Green", img_green);
  cv::namedWindow("Blue",cv::WINDOW_NORMAL);
  cv::imshow("Blue", img_blue);
  
  try
  {
   cv::imwrite("split_red.jpg", img_red);
   cv::imwrite("split_blue.jpg", img_blue);
   cv::imwrite("split_green.jpg", img_green);
  }
  catch(std::runtime_error& ex) 
  {
    std::cout << "Exception saving images: " << ex.what() <<"\n";
    return 1;
  }

  
  cv::waitKey(0);
  return 0;
}
