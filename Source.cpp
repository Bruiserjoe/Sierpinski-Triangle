#define OLC_PGE_APPLICATION
#include <iostream>
#include <array>
#include <cstdint>
#include <algorithm>
#include "olcPixelGameEngine.h"
struct Triangle {
	int x1;
	int x2;
	int x3;
	int y1;
	int y2;
	int y3;
};
Triangle start = { 400, 10, 790, 50, 780, 780};
std::vector<Triangle> triangles;
std::vector<Triangle> drawtr;
//Push back new triangles into vector above and remove the old triangle used to make them
class Bruh : public olc::PixelGameEngine
{
public:
	Bruh() {
		sAppName = "Sierpinski";
	}
public:
	bool OnUserCreate() override {
		DrawTriangle(start.x1, start.y1, start.x2, start.y2, start.x3, start.y3);
		triangles.push_back(start);
		return true;
	}
	bool OnUserUpdate(float fElaspedTime) override {
		std::vector<Triangle> tlist;
		//Optimize it now
		for (int i = 0; i < triangles.size(); i++) {
			int ychange1 = (triangles[i].y1 + triangles[i].y2) / 2;
			//if (ychange1 > 200) {
				int xchange2 = (triangles[i].x1 + triangles[i].x2) / 2;
				int xchange3 = (triangles[i].x3 + triangles[i].x1) / 2;
				int xchange4 = (triangles[i].x2 + triangles[i].x3) / 2;
				std::cout << ychange1 << std::endl;
				Triangle t1 = { triangles[i].x1, xchange2, xchange3, triangles[i].y1, ychange1, ychange1 };
				Triangle t2 = { xchange2, triangles[i].x2, xchange4, ychange1, triangles[i].y2, triangles[i].y2 };
				Triangle t3 = { xchange3, xchange4, triangles[i].x3, ychange1, triangles[i].y2, triangles[i].y2 };
				tlist.push_back(t1);
				tlist.push_back(t2);
				tlist.push_back(t3);
			
			triangles.erase(triangles.begin() + i);
			
		}
		for (int i = 0; i < tlist.size(); i++) {
			DrawTriangle(tlist[i].x1, tlist[i].y1, tlist[i].x2, tlist[i].y2, tlist[i].x3, tlist[i].y3);
			triangles.push_back(tlist[i]);
		}
		return true;
	}
};



int main() {
	Bruh b;
	if (b.Construct(800, 800, 1, 1)) {
		b.Start();
	}


	return 0;
}
