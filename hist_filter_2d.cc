#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cv.h>
#include <highgui.h>

// allocate memory for no of pixels for each intensity value
unsigned int histogram[256][256][256];


int main(int argc, char **argv)
{
 // initialize all intensity values to 0
 for(int i = 0; i < 255; i++)
  for(int j = 0; j < 255; j++)
   for(int k = 0; k < 255; k++)
    histogram[i][j][k] = 0;
    
    
 // Loads CSV data file
 std::vector<std::vector<int> > bgrVect;
 std::ifstream fin("apple_3_mask.csv");
 std::string line;
 while (std::getline(fin, line)) 
 {
  std::vector<int> lineData;
  int val;
  std::istringstream lineStream(line); 
  while (lineStream >> val) 
  {
    lineData.push_back(val);
  }
  bgrVect.push_back(lineData);
 }
 
 for(unsigned int j=0; j<bgrVect.size(); j++) 
 {
  for(unsigned int i=0; i<bgrVect[j].size(); i++)
  {
   histogram[bgrVect[j][0]][bgrVect[j][1]][bgrVect[j][2]] = bgrVect[j][3];
  }
 }
 
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

 cv::Mat output = cv::Mat(cv::Size(image.cols, image.rows), CV_8UC3);
  
 int r=0,g=0,b=0;
 
 // calculate the number of pixels for each intensity values
 for(int y = 0; y < image.rows; y++)
  for(int x = 0; x < image.cols; x++)
  {
   cv::Vec3b intensity = image.at<cv::Vec3b>(y, x);
   b = intensity.val[0];
   g = intensity.val[1];
   r = intensity.val[2];

   if (histogram[b][g][r] > 0)
   {
    output.at<cv::Vec3b>(y,x) = intensity;
   }
  }
         
 cv::namedWindow("Original",cv::WINDOW_NORMAL);
 cv::imshow("Original", image);
 cv::namedWindow("Result",cv::WINDOW_NORMAL);
 cv::imshow("Result", output); 

 try
 {
  cv::imwrite("hist_filter_2d_result.jpg", output);
 }
 catch(std::runtime_error& ex) 
 {
   std::cout << "Exception saving images: " << ex.what() <<"\n";
   return 1;
 }
 
 cv::waitKey(0);
 return 0;
}
