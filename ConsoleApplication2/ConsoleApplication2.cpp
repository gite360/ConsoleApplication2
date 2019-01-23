// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <math.h>
#include <algorithm>
#include <iterator>
#include <queue>
#include <string>
#include <cassert>
#include <iostream>
#include <functional> 
#include <numeric>

#include <time.h>
#include <Windows.h> 
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <cmath>
#include <complex>
#include <numeric>
#include <algorithm>
#include <vector>
#include <boost/math/special_functions/chebyshev.hpp>
#include <boost/math/constants/constants.hpp>
//#include <boost/interprocess/mapped_region.hpp>
#include <boost/static_assert.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/polygon/polygon.hpp>
namespace bg = boost::geometry;
namespace bp = boost::polygon;
using namespace boost::polygon::operators;

using namespace std;


 

struct Point
{
public:
	double x=0;
	double y=0;
	Point(double xx, double yy) : x(xx), y(yy) {}
	Point() : x(0), y(0) {}
	~Point();
	inline friend ostream& operator<<(ostream& output, const Point& point)
	{
		output << "[" << point.x << ", " << point.y << "]";
		return output;
	}
};
Point::~Point() { ; }
Point center(0,0);

bool PointCmp(const Point &a, const Point &b)
{
	if (a.x >= 0 && b.x < 0)
		return true;
	if (a.x == 0 && b.x == 0)
		return a.y > b.y;
	//向量OA和向量OB的叉积
	int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
	if (det < 0)
		return true;
	if (det > 0)
		return false;
	//向量OA和向量OB共线，以距离判断大小
	int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
	int d2 = (b.x - center.x) * (b.x - center.y) + (b.y - center.y) * (b.y - center.y);
	return d1 > d2;
}
bool Cmp(const Point &a, const Point &b) {
	return PointCmp(a, b);
}


Point Gravity(vector <Point>& p, int n) {
	double area = 0;
	Point center(0,0);
	center.x = 0;
	center.y = 0;
	for (int i = 0; i < n - 1; i++) {
		area += (p[i].x*p[i + 1].y - p[i + 1].x*p[i].y) / 2;
		center.x += (p[i].x*p[i + 1].y - p[i + 1].x*p[i].y) * (p[i].x + p[i + 1].x);
		center.y += (p[i].x*p[i + 1].y - p[i + 1].x*p[i].y) * (p[i].y + p[i + 1].y);
	}
	area += (p[n - 1].x*p[0].y - p[0].x*p[n - 1].y) / 2;
	center.x += (p[n - 1].x*p[0].y - p[0].x*p[n - 1].y) * (p[n - 1].x + p[0].x);
	center.y += (p[n - 1].x*p[0].y - p[0].x*p[n - 1].y) * (p[n - 1].y + p[0].y);
	center.x /= 6 * area;
	center.y /= 6 * area;
	std::vector<Point>::iterator it = p.begin();
	double sum_x = 0, sum_y = 0;
	for (auto&&i:p) {
		sum_x += i.x;
		sum_y += i.y;
	}
	//center.x = sum_x / p.size();
	//center.y = sum_y / p.size();
	return center;
}

void ClockwiseSortPoints(vector <Point>& vPoints, int n){
	//计算重心
	center = Gravity(vPoints, n);
	cout << "center: [" << center.x << ", " << center.y << "]"<<endl;
	sort(vPoints.begin(), vPoints.begin()+n, Cmp);
}


/* get quadrant from 12 o'clock*/
int get_quadrant(const Point& p){
	int result = 4; //origin

	if (p.x > 0 && p.y > 0)
		return 1;
	else if (p.x < 0 && p.y > 0)
		return 2;
	else if (p.x < 0 && p.y < 0)
		return 3;
	//else 4th quadrant
	return result;
}

double get_clockwise_angle(const Point& p)
{
	double angle = 0.0;
	int quadrant = get_quadrant(p);

	/*making sure the quadrants are correct*/
	cout << "Point: " << p << " is on the " << quadrant << " quadrant" << endl;

	/*calculate angle and return it*/
	angle = -atan2(p.x, -p.y);
	return angle;
}
bool compare_points(const Point& a, const Point& b)
{
	/*if (a.x <= 0 && b.x > 0) return true;
	else if (a.x == 0 && b.x == 0) return a.y < b.y;
	else if (get_clockwise_angle(a) == get_clockwise_angle(b))
		return a.x*a.x + a.y*a.y > b.x*b.x + b.y*b.y;
	else*/
	//if (get_clockwise_angle(a) == get_clockwise_angle(b))
		//return a.x*a.x + a.y*a.y > b.x*b.x + b.y*b.y;
	return (get_clockwise_angle(a) < get_clockwise_angle(b));
}
int main(int argc, char const *argv[])
{
	std::vector <Point> points;
	
	//points.push_back(Point(0, 0));
	points.push_back(Point(0, 1));
	points.push_back(Point(1, 6));
	points.push_back(Point(2, 10));
	points.push_back(Point(3, 2));
	std::vector <Point> myvector(points.size());
	std::copy(points.begin(), points.end(), myvector.begin());
	

	cout << "\nBefore sorting" << endl;
	for (int i = 0; i < points.size(); ++i)
	{
		cout << points.at(i) << endl;
	}

	std::sort(points.begin(), points.end(), compare_points);

	cout << "\nAfter sorting" << endl;
	for (int i = 0; i < points.size(); ++i)
	{
		cout << points.at(i) << endl;
	}


	/*double x, y, result;
	x = -10.0;
	y = -10;
	result = atan2(y, x) * 180 / 3.1415926;
	printf("The arc tangent for (x= PI%f, y=%f) is %f degrees\n", x, y, result);*/

	cout << "\nBefore sorting" << endl;
	for (int i = 0; i < myvector.size(); ++i)
	{
		cout << myvector.at(i) << endl;
	}
	
	ClockwiseSortPoints(myvector, 4);

	

	cout << "\nAfter sorting" << endl;
	for (int i = 0; i < myvector.size(); ++i)
	{
		cout << myvector.at(i) << endl;
	}


		typedef bg::model::d2::point_xy<double> point_type;
		bg::model::polygon<point_type, true, true> poly;
		bg::model::polygon<point_type, true, true> poly1;
		/*bg::append(poly.outer(), point_type(0.0, 0.0));
		bg::append(poly.outer(), point_type(5.0, 5.0));
		bg::append(poly.outer(), point_type(0.0, 5.0));
		bg::append(poly.outer(), point_type(5.0, 0.0));
		bg::append(poly.outer(), point_type(0.0, 0.0));*/
		for (auto&&i : points) {
			bg::append(poly1.outer(), point_type(i.x, i.y));

		}
		bg::append(poly1.outer(), point_type(points[0].x, points[0].y));
		double a = bg::area(poly1);
		cout << "AAAAAAAAAAAAAA    " << a << endl;




		for (auto&&i : myvector) {
			bg::append(poly.outer(), point_type(i.x,i.y));

		}
		bg::append(poly.outer(), point_type(myvector[0].x, myvector[0].y));
		double b = bg::area(poly);
		cout << "BBBBBBBBBBBBBB    " << b << endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
