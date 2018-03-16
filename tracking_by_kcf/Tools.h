#pragma once
#include<Eigen/dense>
#include <opencv2/core.hpp>

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<io.h>

#include "Parameters.h"

using namespace std;
using namespace cv;
using namespace Eigen;
typedef Matrix<int, 1, 2> RowVector2i;

void getFiles(string path, vector<string>& files);
void getGroundTruth(string video_path,int img_number,Mat& ground_truth);

/*video_path:	the path of video
 *img_files:	the p of images
 *initial_pos:	the postion of the first box
 *target_sz:	[y,x]
 *ground_truth:	[x,y,box_width,box_height]
*/
void load_video_info(/*Input*/string video_path, /*Output*/vector<string>& img_files, int * initial_pos, int * target_sz, Mat& ground_truth);

//[positions, time] = tracker(video_path, img_files, pos, target_sz, ...
//	padding, kernel, lambda, output_sigma_factor, interp_factor, ...
//	cell_size, features, show_visualization);

void tracker(/*Input*/string video_path, const vector<string>& img_files, int * initial_pos, int * target_sz,/*Output*/Mat& positions, double time);






void getFiles(string path, vector<string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void getGroundTruth(string video_path, int img_number,Mat& ground_truth)
{
	ifstream in(video_path+"\\groundtruth_rect.txt");
	string filename;
	string line;
	if (in) // 有该文件  
	{
		ground_truth.create(img_number, 4, CV_32S);
		int i = 0;
		int x, y, box_width, box_height;
		while (getline(in, line)) // line中不包括每行的换行符  
		{
			//cout << line << endl;
			//处理line
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == ',') line[i] = ' ';
			}

			stringstream integer(line);
			integer >> x; integer >> y;	integer >> box_width; integer >> box_height;
			//ground_truth.row(i++) = { x,y,box_width,box_height };
			ground_truth.at<int>(i, 0) = x;
			ground_truth.at<int>(i, 1) = y;
			ground_truth.at<int>(i, 2) = box_width;
			ground_truth.at<int>(i, 3) = box_height;
			i++;
		}

		in.close();
	}
	else // 没有该文件  
	{
		cout << "no file 'ground_truth.txt' " << endl;
	}
}

/*video_path:	the path of video
 *img_files:	the p of images
 *initial_pos:	the postion of the first box	[y,x]
 *target_sz:	[height,width]
 *ground_truth:	[x,y,box_width,box_height]
*/
void load_video_info(string video_path, vector<string>& img_files, int * initial_pos, int * target_sz, Mat& ground_truth)
{
	string img_path = video_path + "\\img";
	getFiles(img_path, img_files);
	getGroundTruth(video_path, img_files.size(),ground_truth);
//	target_sz = [ground_truth(1, 4), ground_truth(1, 3)];
//	pos = [ground_truth(1, 2), ground_truth(1, 1)] + floor(target_sz / 2);
	target_sz[0] = ground_truth.at<int>(1, 3);
	target_sz[1] = ground_truth.at<int>(1, 2);
	initial_pos[0] = ground_truth.at<int>(1, 1) + (int) floor(target_sz[0] / 2);
	initial_pos[1] = ground_truth.at<int>(1, 0) + (int) floor(target_sz[1] / 2);
}

void tracker(/*Input*/string video_path, const vector<string>& img_files, int * initial_pos, int * target_sz,/*Output*/Mat& positions, double time)
{
	Parameters params;

	//if the target is large, lower the resolution, we don't need that much
	bool resize_image = sqrt(target_sz[0] * target_sz[1]) >= 100;
	if (resize_image)
	{
		initial_pos[0] = floor(initial_pos[0] / 2);
		initial_pos[1] = floor(initial_pos[1] / 2);
		target_sz[0] = floor(target_sz[0] / 2);
		target_sz[1] = floor(target_sz[1] / 2);
	}

	int window_sz[2];
	window_sz[0] = floor(target_sz[0] * (1 + params.pre_processing.padding));
	window_sz[1] = floor(target_sz[0]*(1 + params.pre_processing.padding));
	
}