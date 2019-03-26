//#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
//using namespace cv;
// COMPILE :
// g++ test.cpp -o output `pkg-config --cflags --libs opencv`

namespace basics{
  cv::Mat to_reverse(cv::Mat source){
    cv::Mat res = cv::Mat(source.size() , source.type());
    for(int row=0; row < source.rows; row++){
      for(int col=0; col < source.cols; col++){
        res.at<uchar>(row,col) = 255 - source.at<uchar>(row,col);
      }  
    }
    return res.clone();
  }

  cv::Mat logarithm(cv::Mat source){
    cv::Mat res = cv::Mat(source.size() , source.type());
    for(int row=0; row < source.rows; row++){
        for(int col=0; col < source.cols; col++){
          res.at<uchar>(row,col) = log(source.at<uchar>(row,col));
        }  
      }
      return res.clone();
  }

  cv::Mat inv_log(cv::Mat source){
    cv::Mat res = cv::Mat(source.size() , source.type());
    for(int row=0; row < source.rows; row++){
        for(int col=0; col < source.cols; col++){
          res.at<cv::Vec3b>(row,col)[0] = 1.0f / (float)log( source.at<cv::Vec3b>(row,col)[0] );
          res.at<cv::Vec3b>(row,col)[1] = 1.0f / (float)log( source.at<cv::Vec3b>(row,col)[1] );
          res.at<cv::Vec3b>(row,col)[2] = 1.0f / (float)log( source.at<cv::Vec3b>(row,col)[2] );
        }  
    }
    return res.clone();
  }

  cv::Mat square(cv::Mat source){
    cv::Mat res = cv::Mat(source.size() , source.type());
    for(int row=0; row < source.rows; row++){
        for(int col=0; col < source.cols; col++){
          res.at<uchar>(row,col) = sqrt(source.at<uchar>(row,col));
        }  
    }
    return res.clone();
  }

  cv::Mat power(cv::Mat source, double exp=5){
    cv::Mat res = cv::Mat(source.size() , source.type());
    for(int row=0; row < source.rows; row++){
        for(int col=0; col < source.cols; col++){
          res.at<uchar>(row,col) = pow(source.at<uchar>(row,col), exp);
        }  
    }
    return res.clone();
  }

  cv::Mat scale(cv::Mat source, int neww, int newh){
    double x_ratio = (double)source.cols / (double)neww;
    double y_ratio = (double)source.rows / (double)newh;
    cout << "new dims: " << neww << " " << newh << endl;
    cout << "scale ratio: " << x_ratio << " " << y_ratio << endl;
    cv::Mat res = cv::Mat(newh, neww , source.type());
    double px, py;
    for(int row=0; row < res.rows; row++){
        for(int col=0; col < res.cols; col++){
          px = floor(col*x_ratio);
          py = floor(row*y_ratio);
          res.at<uchar>(col,row) = source.at<uchar>(px,py);
        }  
    }
    return res.clone();
  }

  cv::Mat rotate(cv::Mat source, double angle=45){
    cv::Mat res = cv::Mat::zeros(source.rows, source.cols, CV_8UC1);
    const float pi=3.1415;
    int x, y;
    //Angle by which to rotate an Image
    //for (int a=0 ; a<360 ; a++){
      //Logic of Image Rotation
      for (float i=0; i<source.cols ; i++){
        for (float j=0 ; j<source.rows ; j++){
          //x'=(x-p)Cos(ϴ')-(y-q)Sin(ϴ')+p
          x=((i-source.cols/2)*cos(angle*pi/180)-(j-source.rows/2)*sin(angle*pi/180)+source.cols/2);
          //y'=(y-q)Cos(ϴ')+(x-p)Sin(ϴ')+q
          y=((i-source.cols/2)*sin(angle*pi/180)+(j-source.rows/2)*cos(angle*pi/180)+source.rows/2);
        
          if((x>=0 && x<source.cols) && (y>=0 && y<source.rows)){
            res.at<uchar>(x,y) = source.at<uchar>(i,j);
          }
        }
      }
    //}
    return res.clone();
  }
  
}
 
int main( int argc, char** argv ) {
  
  cv::Mat image = cv::imread("images/cameraman.jpg" , CV_LOAD_IMAGE_GRAYSCALE);
  cv::Mat res = cv::Mat(image.size(), image.type());

  if(! image.data ) {
      std::cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }
  
  cout << image.rows << " " << image.cols << endl;
  //res = basics::to_reverse(image);
  //res = basics::rotate(image);
  //res = basics::scale(image,500, 500);
  res = basics::power(image);

  cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
  cv::imshow( "Display window", res );
  
  cv::waitKey(0);
  return 0;
}