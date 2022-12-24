#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace cv;

class Vertex{
public:
  Vertex(double x_in, double y_in): x(x_in), y(y_in){};

  void setX(double pX){ x=pX; }
  void setY(double pY){ y=pY; }
  double getX(){ return x; }
  double getY(){ return y; }

private:
  double x,y;
};

void readPNG(const std::string& filename, Mat& img){
  try
  {
    img = imread(filename);
  }
  catch(const std::exception& e)
  {
    std::cerr << "read error" << '\n';
  }
}


void changeToBlackWhite(Mat& img){

  // Vec3b& intensity;
  for (int y=1; y < img.rows; ++y){
    for (int x=1; x < img.cols; ++x){
      Vec3b& intensity = img.at<Vec3b>(y,x);
      // printf("===> [%u,%u,%u]\n", intensity.val[0], intensity.val[1], intensity.val[2]);
      if((intensity.val[0] == (uchar)255) && (intensity.val[1] == (uchar)255) && (intensity.val[2] == (uchar)255)){
        continue;
      }
      else{
        intensity.val[0] = uchar(0);
        intensity.val[1] = uchar(0);
        intensity.val[2] = uchar(0);
      }
    }
  }
  imwrite("./car_blackAndWrite.png", img);
}

void getEdge(const Mat& img, Mat& img_edge){

	Canny(img, img_edge, 0, 0);
  // Canny(img, img_edge, 500, 500);

  Mat dilated_cv;

  Mat element;
  element = getStructuringElement(MORPH_RECT, Size(15, 15));
  dilate(img_edge, dilated_cv, element);

  imwrite("./car_edge.png", img_edge);
  imwrite("./car_edge_bigger.png", dilated_cv);
}

void convert2Point(Mat& img_edge){
  std::fstream fout;
  fout.open("./point.txt");
  double p_x, p_y;
  double max_x=-1, max_y=-1;
  double min_x=img_edge.cols, min_y=img_edge.rows;


  for (int y=0; y < img_edge.rows; ++y){
    for (int x=0; x < img_edge.cols; ++x){

      Vec3b& intensity = img_edge.at<Vec3b>(y,x);
      // printf("[%u,%u,%u]\n", intensity.val[0], intensity.val[1], intensity.val[2]);
      if((intensity.val[0] == (uchar)255) && (intensity.val[1] == (uchar)255) && (intensity.val[2] == (uchar)255)){
        // printf("[%d,%d]\n", x, y);
      }

      if (max_x < x) max_x = x;
      if (max_y < y) max_y = y;

      if (min_x > x) min_x = x;
      if (min_y > y) min_y = y;
    }
  }

  double range_x = max_x - min_x;
  double range_y = max_y - min_y;

  for (int y=0; y < img_edge.rows; ++y){
    for (int x=0; x < img_edge.cols; ++x){

    Vec3b& intensity = img_edge.at<Vec3b>(y,x);
    if((intensity.val[0] == (uchar)255) && (intensity.val[1] == (uchar)255) && (intensity.val[2] == (uchar)255)){
      p_x = (double)x/range_x;
      p_y = (double)y/range_y;

      fout<<p_x<<" "<<p_y<<std::endl; 
    }
  }
}
  fout.close();
}


int main(int argc, char** argv){
  std::string filename = argv[1];
  Mat img;
  readPNG(filename, img);

  printf("rows= %d, cols=%d, size=%d\n", img.rows, img.cols, img.rows*img.cols);
  printf("img channels=%d\n", img.channels());

  changeToBlackWhite(img);

	Mat img_edge = Mat(img.size(), CV_8U, Scalar(0));
  getEdge(img, img_edge);

  
  convert2Point(img_edge);



	return 0;
}

