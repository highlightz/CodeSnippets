#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sstream>
#include <time.h>
#include <stdlib.h>

#define random(x) (rand()%x)

int main( int argc, char** argv )
{
   srand((int)time(0));

   // Create image
   const int WIDTH = 640;
   const int HEIGHT = 480;
   cv::Mat bkground;
   bkground.create( cv::Size( WIDTH, HEIGHT ), CV_8UC3 );

   const double adjustableScale = 80.0;

   while ( 1 )
   {
       cv::line( bkground,
                 cv::Point( 10, bkground.rows / 2 ),
                 cv::Point( bkground.cols - 10, bkground.rows / 2 ),
                 cv::Scalar( 0, 255, 0 ), 2 );

       cv::line( bkground,
                 cv::Point( bkground.cols / 2, 10 ),
                 cv::Point( bkground.cols / 2, bkground.rows - 10 ),
                 cv::Scalar( 0, 255, 0 ), 2 );

       const double pi = 3.14;
       const double test_rad = pi / 6 * ( random(9) - 3 );
       double x_display = cos( test_rad ) * adjustableScale;
       double y_display = sin( test_rad ) * adjustableScale;

       double tmp = x_display;
       x_display = y_display;
       y_display = tmp;

       x_display = -x_display + bkground.cols / 2;
       y_display = -y_display + bkground.rows / 2;

       cv::line( bkground,
                 cv::Point( x_display, y_display ),
                 cv::Point( bkground.cols / 2, bkground.rows / 2 ),
                 cv::Scalar( 255, 0, 0 ), 4 );

       cv::circle( bkground,
                   cv::Point( x_display, y_display ),
                   6, cv::Scalar( 255, 255, 0 ), 4 );

       std::stringstream ss;
       ss << test_rad * 180 / pi;
       std::string text;
       ss >> text;
       int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
       double fontScale = 2;
       int thickness = 3;
       cv::Point textOrg(50, 70);
       cv::putText(bkground, text, textOrg, fontFace, fontScale, cv::Scalar::all(255), thickness,8);

       cv::circle( bkground, cv::Point( 190, 30 ), 6, cv::Scalar::all( 255 ), 2 );

       cv::imshow( "result", bkground );
       cv::waitKey( 300 );
       bkground.setTo( cv::Scalar::all(0) );
   }

   return 0;
}
