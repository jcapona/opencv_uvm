#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

int main(int argc, char **argv)
{
 if(argc == 1)
 {
  std::cout << "Enter image name to process\n";
  return -1;
 }
 
 cv::Mat image = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE); // Read image
 if(!image.data ) // Check for invalid input
 {
  std::cerr << "Could not open or find the image\n";
  return -1;
 }
 
 // allcoate memory for no of pixels for each intensity value
 int histogram[256];

 // initialize all intensity values to 0
 for(int i = 0; i < 255; i++)
 {
  histogram[i] = 0;
 }

 // calculate the no of pixels for each intensity values
 for(int y = 0; y < image.rows; y++)
  for(int x = 0; x < image.cols; x++)
   histogram[(int)image.at<uchar>(y,x)]++;

 for(int i = 0; i < 256; i++)
  std::cout<<i << " : " << histogram[i]<<"\n";

 // draw the histograms
 int hist_w = 512; int hist_h = 400;
 int bin_w = cvRound((double) hist_w/256);

 cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(255, 255, 255));

 // find the maximum intensity element from histogram
 int max = histogram[0];
 for(int i = 1; i < 256; i++){
  if(max < histogram[i]){
   max = histogram[i];
  }
 }

 // normalize the histogram between 0 and histImage.rows

 for(int i = 0; i < 255; i++){
  histogram[i] = ((double)histogram[i]/max)*histImage.rows;
 }


 // draw the intensity line for histogram
 for(int i = 0; i < 255; i++)
 {
  line(histImage, cv::Point(bin_w*(i), hist_h),
       cv::Point(bin_w*(i), hist_h - histogram[i]),
   cv::Scalar(0,0,0), 1, 8, 0);
 }

 // display histogram
 cv::namedWindow("Intensity Histogram", CV_WINDOW_AUTOSIZE);
 cv::imshow("Intensity Histogram", histImage);

 cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);
 cv::imshow("Image", image);
 cv::waitKey();
 return 0;
}
