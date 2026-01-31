#include "Point.hpp"
#include <cmath>

static Fixed abs(Fixed value) {
	return (value < Fixed(0)) ? value * Fixed(-1) : value;
}

static Fixed area(Point const a, Point const b, Point const c) {
	Fixed result = (a.getX() * (b.getY() - c.getY()) + 
					b.getX() * (c.getY() - a.getY()) + 
					c.getX() * (a.getY() - b.getY())) / Fixed(2);
	return abs(result);
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
	Fixed totalArea = area(a, b, c);
	Fixed area1 = area(point, a, b);
	Fixed area2 = area(point, b, c);
	Fixed area3 = area(point, c, a);
	
	if (area1 == Fixed(0) || area2 == Fixed(0) || area3 == Fixed(0))
		return false;
	
	return (area1 + area2 + area3) == totalArea;
}