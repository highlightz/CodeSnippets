
// BM Algotithm based disparity map calculation
// Revised on Sep 8, 2015
// By Zhang Gaoming

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
	// Load rectified image pair from command line
	const char *imgL_filename = argv[1];
	const char *imgR_filename = argv[2];
	Mat imgL = imread( imgL_filename, 0 );
	Mat imgR = imread( imgR_filename, 0 );

	// Initialize relevant parameters concerning BM algorithm
	StereoBM bm;

	Size img_size = imgL.size(  );
	Rect roi1, roi2;

	bm.state->roi1 = roi1;
	bm.state->roi2 = roi2;
	bm.state->preFilterCap = 31;
	bm.state->SADWindowSize = 15;

	// minDisparity: a small disparity corresponds to a big distance
	bm.state->minDisparity = 0;

	// numberOfDisparities:
	int numberOfDisparities = 48;
	// ( img_size.width / 8 + 15 ) & -16 = 80
	numberOfDisparities = numberOfDisparities > 0 ? numberOfDisparities : ((img_size.width/8) + 15) & -16;
	bm.state->numberOfDisparities = numberOfDisparities;

	bm.state->textureThreshold = 10;

	// uniquenessRatio:
	bm.state->uniquenessRatio = 15;

	bm.state->speckleWindowSize = 100;
	bm.state->speckleRange = 32;
	bm.state->disp12MaxDiff = 1;

	// Disparity map matrix
	Mat disp;

	// Start timing
	int64 t = getTickCount( );
	// Compute the disparity map
	bm( imgL, imgR, disp, 3 );
	t = getTickCount( ) - t;
	
	Mat disp8;
	disp.convertTo( disp8, CV_8U );
	imshow( "disparity", disp8 );
	cvWaitKey( );
	const char *disparity_filename = argv[3];
	imwrite( disparity_filename, disp8 );
	
	cout << "Time elapsed: " << t * 1000 / getTickFrequency( ) << " ms." << endl;

	const int dispThresh = 20;  

	int leftWindowDisp = 0;
	int midWindowDisp = 0;
	int rightWindowDisp = 0;

	float leftWindowRate = 0;
	float midWindowRate = 0;
	float rightWindowRate = 0;

	// Central window
	for ( int i = 213; i < 427; i++ )
		for ( int j = 0; j < 480; j++ )
		{
			short pixVal = disp.at<short>( j, i );
			float disparity = pixVal / 16.0f;
			if ( disparity > dispThresh )
			{
				midWindowDisp++;
			}
		}
	// Left window
	for ( int i = 0; i < 213; i++ )
		for ( int j = 0; j < 480; j++ )
		{
			short pixVal = disp.at<short>( j, i );
			float disparity = pixVal / 16.0f;
			if ( disparity > dispThresh )
			{
				leftWindowDisp++;
			}
		}
	// right window
	for ( int i = 213; i < 640; i++ )
		for ( int j = 0; j < 480; j++ )
		{
			short pixVal = disp.at<short>( j, i );
			float disparity = pixVal / 16.0f;
			if ( disparity > dispThresh )
			{
				rightWindowDisp++;
			}
		}

	leftWindowRate = ( float )leftWindowDisp / (4.80 * 213.0);
	midWindowRate = ( float )midWindowDisp / (4.80 * 214.0);
	rightWindowRate = ( float )rightWindowDisp / (4.80 * 214.0);

	cout << "LeftNum: " << leftWindowDisp << std::endl;
	cout << "LeftRate: " << leftWindowRate << "%" << std::endl;

	cout << "MidNum: " << midWindowDisp << std::endl;
	cout << "MidRate: " << midWindowRate << "%" << std::endl;

	cout << "rightNum: " << rightWindowDisp << std::endl;
	cout << "rightRate: " << rightWindowRate << "%" << std::endl;

	return 0;
}
