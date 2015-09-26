#include <opencv2/opencv.hpp>
using namespace cv;

#include <string>
using std::string;

#include <iostream>
using std::cout;

#include <stdio.h>

void drawCurrentHeading( cv::Mat& bkground );

int main( int argc, char** argv )
{
   // In Linux, this is a right way of string assignment,
   // when in Windows, adjust it to be right.
   string dir = "/home/highlight/Projects/laserOA/build-laserOA-unknown-Debug/dateset150814";
   for ( int i = 100; i < 2000; i++ )
   {
       try{
       // Prepare file name
       char base_name[256]; sprintf( base_name, "%d.jpg", i );
       string image_name = dir + "/L_" + base_name;
       
       Mat raw = imread( image_name );
       
       // Prepare data
       Point pt1( 320, 420 );
       Point pt2( 280, 460 );
       Point pt3( 360, 460 );

       line( raw, pt1, pt2, Scalar( 0, 255, 0 ), 30 );
       line( raw, pt1, pt3, Scalar( 0, 255, 0 ), 30 );
       line( raw, pt3, pt2, Scalar( 0, 255, 0 ), 30 );
       drawCurrentHeading( raw );
       imshow( "raw", raw );
       waitKey( 60 );
       }
       catch( ... )
       {
       }
   }

   return 0;
}

void drawCurrentHeading( cv::Mat& bkground )
{
   const int WIDTH = 640;
   const int HEIGHT = 480;
   bkground.create( cv::Size( WIDTH, HEIGHT ), CV_8UC3 );

   string text1( "Green area is specified as ground" );

   int fontFace = cv::FONT_HERSHEY_PLAIN;
   double fontScale = 2;
   int thickness = 2;
   cv::Point textOrg1( 25, 110 );
   cv::putText( bkground,
                text1,
                textOrg1,
                fontFace,
                fontScale,
                cv::Scalar( 255, 0, 255 ),
                thickness, 8 );

   string text2( "plane. This is done by experience." );
   cv::Point textOrg2( 25, 150 );
   cv::putText( bkground,
                text2,
                textOrg2,
                fontFace,
                fontScale,
                cv::Scalar( 255, 0, 255 ),
                thickness, 8 );
}
