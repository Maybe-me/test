#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

int edgeThresh = 1;
Mat image, gray, edge, cedge;

// define a trackbar callback
static void onTrackbar(int, void*)
{
	blur(gray, edge, Size(3, 3));

	// Run the edge detector on grayscale
	Canny(edge, edge, edgeThresh, edgeThresh * 3, 3);
	cedge = Scalar::all(0);

	image.copyTo(cedge, edge);
	imshow("Edge map", cedge);
}

static void help()
{
	printf("\nThis sample demonstrates Canny edge detection\n"
		"Call:\n"
		"   /.edge [image_name -- Default is ../data/fruits.jpg]\n\n");
}

const char* keys =
{
	"{help h||}{@image |../data/fruits.jpg|input image name}"

};

int main(int argc, const char** argv)
{
	CommandLineParser parser(argc, argv, keys);
	if (parser.has("help"))
	{
		help();
		return 0;
	}
	//！！！！这里将 filename 换成你自己图片的绝对路径就可以了，只要修改这一处！！！！
	string filename = "F:/VS2019/test/AM.png";


	image = imread(filename, 1);
	if (image.empty())
	{
		printf("Cannot read image file: %s\n", filename.c_str());
		help();
		return -1;
	}
	cedge.create(image.size(), image.type());
	cvtColor(image, gray, COLOR_BGR2GRAY);

	// Create a window
	namedWindow("Edge map", 1);

	// create a toolbar
	createTrackbar("Canny threshold", "Edge map", &edgeThresh, 100, onTrackbar);

	// Show the image
	onTrackbar(0, 0);

	// Wait for a key stroke; the same function arranges events processing
	waitKey(0);
	system("pause");
	return 0;
}
