/**
This will open an image, and perform a threshold operation on the 
channel passed as argument when calling the program.

Basically, it creates an image by copying the values from the selected 
channel to the others, and performs the threshold operation on this new image.

You can save the displayed image by pressing 's'
*/

#include <iostream>
#include <cv.h>
#include <highgui.h>

int main( int argc, char** argv )
{
 if(argc != 3)
 {
  std::cout << "Use:\n\t./threshold filename colour\n\twhere\n\t\tfilename: file with the image to open\n\t\tcolour: 'r','g' or 'b'; main channel for threshold\n";
  return -1;
 }
 if( (*argv[2]!='r')&&(*argv[2]!='g')&&(*argv[2]!='b'))
 {
  std::cout << "Invalid colour. Enter r, g or b\n"<<argv[2];
  return -1;
 }
 
 cv::Mat image = cv::imread(argv[1],1); // Read image
 if(!image.data ) // Check for invalid input
 {
  std::cerr << "Could not open or find the image\n";
  return -1;
 }

 // Converts image to grayscale
 cv::Mat image_gray, image_mod; 


 int threshold_value = 0;
 const char* window_name = "Threshold Demo";
 
 // Create a window to display results
 cv::namedWindow( window_name, CV_WINDOW_AUTOSIZE );
 // Trackbar to play with threshold
 cv::createTrackbar("Value", window_name, &threshold_value, 255, NULL);


 // Split the image into different channels
 std::vector<cv::Mat> rgbChannels(3);
 cv::split(image, rgbChannels);
   
 int colour;
 if(*argv[2] == 'r')
  colour = 2;
 else if(*argv[2] == 'g')
  colour = 1;
 else colour = 0;

 std::vector<cv::Mat> channels;
 channels.push_back(rgbChannels[colour]);
 channels.push_back(rgbChannels[colour]);
 channels.push_back(rgbChannels[colour]);
 merge(channels, image_gray); // Merges channels 
  
 int c;
 while(true)
 {
   image_mod = image_gray < threshold_value; //
   cv::imshow(window_name, image_mod);
   
   c = cv::waitKey(20);
   if((char)c == 's')
    cv::imwrite("threshold_"+std::to_string(threshold_value)+".jpg",image_mod);
   
   if((char)c == 27)
    break; 
 }
 return 0;
}

