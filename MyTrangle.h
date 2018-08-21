#pragma once

#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
//类定义：二维向量
class Vector2d
{
public:
	Vector2d(double x, double y);
	Vector2d();

	//二维向量叉乘, 叉乘的结果其实是向量，方向垂直于两个向量组成的平面，这里我们只需要其大小和方向
	double CrossProduct(const Vector2d vec);

	//二维向量点积
	double DotProduct(const Vector2d vec);

	//二维向量减法
	Vector2d Minus(const Vector2d vec) const;

	//判断点M,N是否在直线AB的同一侧
	static bool IsPointAtSameSideOfLine(const Vector2d &pointM, const Vector2d &pointN,
		const Vector2d &pointA, const Vector2d &pointB);
public:
	double x_;
	double y_;
};

//三角形类
class Triangle
{
public:
	Triangle(Vector2d point1, Vector2d point2, Vector2d point3);

	Triangle(Point2f point1, Point2f point2, Point2f point3);

	bool IsPointInTriangle(const Vector2d pointP);
	bool IsPointInTriangle1(const Vector2d pointP);
	double ComputeTriangleArea();

private:
	Vector2d pointA_, pointB_, pointC_;
};

