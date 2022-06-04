#pragma once
#include <iostream>
struct Point
{
	int x, y;
};

void DrawTheLine(int x1, int y1, int x2, int y2);
void DrawTheLine(Point start, Point end);

