#include <stdio.h>
#include <string>
using std::string;
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv )
{
	VideoCapture cap;
	if ( argc > 1 ) cap.open( string( argv[1] )); else cap.open( 0 );
	Mat frame; 
	namedWindow( "raw video", 1 );
	namedWindow( "processed video", 1 );
	for ( ;; )
	{
		cap >> frame;

		// Access matrix elements
		//Mat dyImage( frame.size( ), frame.type( ) );
		//for ( int y = 1; y < frame.rows - 1; y++ )
		//{
		//	Vec3b* prevRow = frame.ptr< Vec3b >( y - 1 );
		//	Vec3b* nextRow = frame.ptr< Vec3b >( y + 1 );

		//	for ( int x = 0; x < frame.cols; x++ )
		//	{
		//		for ( int c = 0; c < 3; c++ )
		//		{
		//			dyImage.at< Vec3b >( y, x )[ c ] = 
		//				saturate_cast< uchar >( nextRow[x][c]-prevRow[x][c] );
		//		}
		//	}
		//}

		///*Mat_< Vec3b >::iterator it = dyImage.begin< Vec3b >( ),
		//	itEnd = dyImage.end< Vec3b >( );
		//for ( ; it != itEnd; ++it )
		//	(*it)[0] ^= 255;*/
		//
		//if ( !dyImage.data ) break;
		//imshow( "video", dyImage ); if ( waitKey( 30 ) >= 0 ) break;

		if ( !frame.data ) break;

		imshow( "raw video", frame );

		Mat imgroi = frame( Rect( 50, 60, 330, 340 ) );
		GaussianBlur( imgroi, imgroi, Size( 5, 5 ), 15.5, 15.5 );
		
		imshow( "processed video", frame ); if ( waitKey( 30 ) >= 0 ) break;
	}

	
	
	/*if ( argc != 2 )
	{
		printf("usage: DisplayImage.out <Image_Path>\n");
		return -1;
	}

	Mat image;
	image = imread( argv[1], 1 );
	if ( !image.data )
	{
		printf("No image data \n");
		return -1;
	}
	namedWindow("Display Image", CV_WINDOW_AUTOSIZE );
	imshow("Display Image", image);
	waitKey(0);*/
	return 0;
}
