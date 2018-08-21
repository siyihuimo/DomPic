#include "MyTrangle.h"

Vector2d::Vector2d(double x, double y) :x_(x), y_(y) {}

Vector2d::Vector2d() :x_(0), y_(0) {}

double Vector2d::CrossProduct(const Vector2d vec)
{
	return x_*vec.y_ - y_*vec.x_;
}

//二维向量点积
double Vector2d::DotProduct(const Vector2d vec)
{
	return x_ * vec.x_ + y_ * vec.y_;
}

//二维向量减法
Vector2d Vector2d::Minus(const Vector2d vec) const
{
	return Vector2d(x_ - vec.x_, y_ - vec.y_);
}

//判断点M,N是否在直线AB的同一侧
bool Vector2d::IsPointAtSameSideOfLine(const Vector2d &pointM, const Vector2d &pointN,
	const Vector2d &pointA, const Vector2d &pointB)
{
	Vector2d AB = pointB.Minus(pointA);
	Vector2d AM = pointM.Minus(pointA);
	Vector2d AN = pointN.Minus(pointA);

	//等于0时表示某个点在直线上
	return AB.CrossProduct(AM) * AB.CrossProduct(AN) >= 0;
}



Triangle::Triangle(Vector2d point1, Vector2d point2, Vector2d point3)
	:pointA_(point1), pointB_(point2), pointC_(point3)
{
	//todo 判断三点是否共线
}

Triangle::Triangle(Point2f point1, Point2f point2, Point2f point3)
	:pointA_(point1.x,point1.y),pointB_(point2.x,point2.y),pointC_(point3.x,point3.y)
{
	
}

double Triangle::ComputeTriangleArea()
{
	//依据两个向量的叉乘来计算，可参考http://blog.csdn.net/zxj1988/article/details/6260576
	Vector2d AB = pointB_.Minus(pointA_);
	Vector2d BC = pointC_.Minus(pointB_);
	return fabs(AB.CrossProduct(BC) / 2.0);
}

bool Triangle::IsPointInTriangle1(const Vector2d pointP)
{
	double area_ABC = ComputeTriangleArea();
	double area_PAB = Triangle(pointP, pointA_, pointB_).ComputeTriangleArea();
	double area_PAC = Triangle(pointP, pointA_, pointC_).ComputeTriangleArea();
	double area_PBC = Triangle(pointP, pointB_, pointC_).ComputeTriangleArea();

	if (fabs(area_PAB + area_PBC + area_PAC - area_ABC) < 0.000001)
		return true;
	else return false;
}

bool Triangle::IsPointInTriangle(const Vector2d pointP)
{
	Vector2d PA = pointA_.Minus(pointP);
	Vector2d PB = pointB_.Minus(pointP);
	Vector2d PC = pointC_.Minus(pointP);
	double t1 = PA.CrossProduct(PB);
	double t2 = PB.CrossProduct(PC);
	double t3 = PC.CrossProduct(PA);
	return t1*t2 >= 0 && t1*t3 >= 0;
}