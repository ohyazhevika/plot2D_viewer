#define _USE_MATH_DEFINES
#include <cmath>
#include "Matrix.h"

double					// Исходные значения параметров X0, Y0, px, py
X0 = 200,
Y0 = 200,
//px = 30,
//py = 40;
px = 25,
py=30;

double
circle_phi_min = 0,
circle_phi_max = M_PI * 2,
arch_spiral_phi_min = 0,
arch_spiral_phi_max = M_PI * 8,
flower_phi_min = 0,
flower_phi_max = M_PI * 8,
polar_rose_phi_min = 0,
polar_rose_phi_max = M_PI * 2;


double spinnerVertices[39] =
{
	-3, -3, 0, 3, 3, 3, 0, -3, 0, -1.5, 1.5, 1.5, -1.5,
	0, 3, 3, 3, 0, -3, -3, -3, 0, 1.5, 1.5, -1.5, -1.5,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
Matrix<> SpinnerVertices(3, 13, spinnerVertices);
int spinnerEdges[40] =
{
	1, 2,
	1, 9, 
	2, 10,
	9, 10, 
	3, 10,
	3, 9,
	3, 4,
	4, 11, 
	9, 11, 
	5, 11, 
	5, 9,
	5, 6,
	6, 12,
	9, 12,
	7, 12, 
	7, 9, 
	7, 8,
	8, 13, 
	9, 13, 
	1, 13
};
Matrix <int> SpinnerEdges(20, 2, spinnerEdges);

double stickVertices[6] = 
{
	0, 0,
	0, -7,
	1, 1
};
Matrix<> StickVertices(3, 2, stickVertices);

int stickEdges[2] =
{
	1, 2
};
Matrix<int> StickEdges(1, 2, stickEdges);
double Sinusoid(double x)
{
	return sin(x);
}
double Circle(double phi)
{
	return 5;
}

double ArchimedeanSpiral(double phi)
{
	return 0.5 * phi;
}

double Flower(double phi)
{
	return sin(7 * phi / 4);
}

double PolarRose(double phi)
{
	return sin(6 * phi);
}
