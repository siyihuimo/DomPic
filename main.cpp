#if 1
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include "MyTrangle.h"

using namespace cv;
using namespace std;

int CalcBoundBox(Point2f *pointArr, int size,Point2f& minPoint, Point2f& maxPoint)
{
	if (pointArr==nullptr)
	{
		cout << "trangle vertex is null" << endl;
		return -1;
	}
	//最小坐标，最大坐标
	minPoint.x = pointArr[0].x;
	minPoint.y = pointArr[0].y;
	maxPoint.x = pointArr[0].x;
	maxPoint.y = pointArr[0].y;

	for (int i = 1; i < size; i++)
	{
		minPoint.x = min(minPoint.x, pointArr[i].x);
		maxPoint.x = max(maxPoint.x, pointArr[i].x);
		minPoint.y = min(minPoint.y, pointArr[i].y);
		maxPoint.y = max(maxPoint.y, pointArr[i].y);
	}
	return 0;
}

int main()
{
	Mat pic = imread("1.jpg");		//小图片
	Mat img = imread("4.jpg");

	if (pic.empty() || img.empty())
	{
		cout << "pic load failed" << endl;
		return -1;
	}
	

	Point2f pointPic[3];			//第一幅图片上的三个关键点
	pointPic[0] = Point2f(pic.cols / 3.0, pic.rows / 3.0);
	pointPic[1] = Point2f(pic.cols / 3.0, pic.rows * 2 / 3.0);
	pointPic[2] = Point2f(pic.cols * 2 / 3.0, pic.rows * 2 / 3.0);

	Point2f pointImg[3];			//第二幅图上的三个关键点
	pointImg[0] = Point2f(img.cols / 3.0,	img.rows / 3.0);
	pointImg[1] = Point2f(img.cols * 2 / 3.0, img.rows / 3.0);
	pointImg[2] = Point2f(img.cols * 2 / 3.0, img.rows * 2 / 3.0);

	imshow("pic", pic);
	imshow("img", img);

	Mat warp(2, 3, CV_64FC1);
	warp = getAffineTransform(pointPic, pointImg);		//计算仿射变换关系    //getAffineTransform 返回值为 CV_64FC1类型

	//将三角形三个顶点传入，构造三角形
	Triangle tri(pointPic[0], pointPic[1], pointPic[2]);

	//将此三角面片细分切割
	Point2f minPoint;
	Point2f maxPoint;
	CalcBoundBox(pointPic, sizeof(pointPic) / sizeof(pointPic[0]), minPoint, maxPoint);

	double unit = 0.01;

	float xOff;
	float yOff;

	Mat pointVector(3, 1, CV_64FC1, Scalar(255));
	Mat newPointVec;
	for (xOff = minPoint.x; xOff < maxPoint.x; xOff += unit)
	{
		for (yOff = minPoint.y; yOff < maxPoint.y; yOff += unit)
		{
			Vector2d pointInTran(xOff, yOff);
			
			if (tri.IsPointInTriangle(pointInTran))
			{
				pointVector.at<double>(0, 0) = xOff;
				pointVector.at<double>(1, 0) = yOff;
				pointVector.at<double>(2, 0) = 1.0;
				
				newPointVec = warp*pointVector;

				img.at<Vec3b>(newPointVec.at<double>(1, 0), newPointVec.at<double>(0, 0))[0] =
					pic.at<Vec3b>(yOff, xOff)[0];

				img.at<Vec3b>(newPointVec.at<double>(1, 0),newPointVec.at<double>(0, 0))[1] =
					pic.at<Vec3b>(yOff, xOff)[1];

				img.at<Vec3b>(newPointVec.at<double>(1, 0),newPointVec.at<double>(0, 0))[2] =
					pic.at<Vec3b>(yOff, xOff)[2];
			}
		}
	}
	cout << "out pic" << endl;
	imshow("out", img);

	waitKey(0);
	return 0;
}
#endif