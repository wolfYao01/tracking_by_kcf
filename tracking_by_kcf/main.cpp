#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "Tools.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void help()
{
	cout << "basic usage: ./main.exe [video-path]|all" << endl;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "no video path inputed" << endl;
		return -1;
	}

	string videoPath = argv[1];

	if (videoPath == "all")
	{

	}
	else
	{
		vector<string> img_files;
		int initial_position[2];
		int target_sz[2];
		Mat ground_truth;
		load_video_info(videoPath, img_files, initial_position, target_sz, ground_truth);

		//namedWindow(videoPath,WINDOW_GUI_NORMAL);
		//for (int i = 0; i < img_files.size(); i++)
		//{
		//	Mat image = imread(img_files[i], IMREAD_GRAYSCALE);
		//	imshow(videoPath,image);
		//	waitKey(1000 / 60);
		//}
	}

	system("pause");
	return 0;
}