#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

void drawGrid( cv::Mat& bkground, int gridSize )
{
	const int WIDTH = 640;
	const int HEIGHT = 480;

	bkground.create( HEIGHT, WIDTH, CV_8UC3 );

	// 绘制水平线阵
	for ( int i = gridSize; i < HEIGHT; i += gridSize )
	{
		cv::line( bkground, cv::Point( 0, i ), cv::Point( WIDTH, i ), cv::Scalar( 255, 255, 255 ) );
	}

	// 绘制垂直线阵
	for ( int j = gridSize; j < WIDTH; j += gridSize )
	{
		cv::line( bkground, cv::Point( j, 0 ), cv::Point( j, HEIGHT ), cv::Scalar( 255, 255, 255 ) );
	}
}

int main( )
{
	cv::Mat bkground;
	drawGrid( bkground, 32 );
	cv::imshow( "bkground", bkground );
	cv::waitKey( );
}
