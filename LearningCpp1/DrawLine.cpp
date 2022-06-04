#include "DrawLine.h"
void DrawTheLine(int x1, int y1, int x2, int y2)
{
	std::cout << "x1= " << x1 << " || "
		<< "y1= " << y1 << " || "
		<< "x2= " << x2 << " || "
		<< "y2= " << y2 << '\n';
}

void DrawTheLine(Point start, Point end)
{
	std::cout << "start.x= " << start.x << " || "
		<< "start.y= " << start.y << " || "
		<< "end.x= " << end.x << " || "
		<< "end.y= " << end.y << '\n';
}