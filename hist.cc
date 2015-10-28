/**
Displays 3d histogram from image passed as argument in form:

blue green red value

Ex: 0 255 255 2

Means there are 2 pixels in the image where green = 255 and red = 255

To save results to a file:
$ ./hist picture.jpg > log.csv

*/ 

#include <iostream>
#include <cv.h>
#include <highgui.h>

// allocate memory for no of pixels for each intensity value
unsigned int histogram[256][256][256];

int main(int argc, char **argv)
{
 if(argc == 1)
 {
  std::cerr << "Enter image name to process\n";
  return -1;
 }
 
 cv::Mat image = cv::imread(argv[1]); // Read image
 if(!image.data) // Check for invalid input
 {
  std::cerr << "Could not open or find the image\n";
  return -1;
 }

 // initialize all intensity values to 0
 for(int i = 0; i < 255; i++)
  for(int j = 0; j < 255; j++)
   for(int k = 0; k < 255; k++)
    histogram[i][j][k] = 0;

 int r=0,g=0,b=0;
 
 // calculate the number of pixels for each intensity values
 for(int y = 0; y < image.rows; y++)
  for(int x = 0; x < image.cols; x++)
  {
   cv::Vec3b intensity = image.at<cv::Vec3b>(y, x);
   b = intensity.val[0];
   g = intensity.val[1];
   r = intensity.val[2];
   histogram[b][g][r] += 1;
   b=0;g=0;r=0;
  }

 std::cout << "b g r count\n";
 // print results
 for(int i = 0; i < 255; i++)
  for(int j = 0; j < 255; j++)
   for(int k = 0; k < 255; k++)
    if(histogram[i][j][k] > 0)
     std::cout << i << " " << j << " " << k << " " << histogram[i][j][k] << "\n";
    
 return 0;
}
