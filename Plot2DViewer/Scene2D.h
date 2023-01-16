#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include "Model2D.h"
#include "Pinwheel.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
	void Render(HDC, Model2D);
public:
	Model2D spinner;
	Pinwheel pinwheel;
	Scene2D(double X0, double Y0, double px, double py) :
		Camera2D(X0, Y0, px, py),
		spinner(SpinnerVertices, SpinnerEdges, 9, 0, 0),
		pinwheel(Model2D(13, 20, "SpinnerVertices.txt", "SpinnerEdges.txt", 9), Model2D(2, 1, "StickVertices.txt", "StickEdges.txt"))
	{}
	void Plot(HDC dc, Func f, bool axes=true)
	{
		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
		if (axes)
			Axes(dc);
		double h = 1 / px;
		MoveTo(L(), f(L()));
		for (double x = L() + h; x < R() + h; x += h)
		{
			LineTo(dc, x, f(x));
		}
	}
	double GetX(double phi, double r)
	{
		return r * cos(phi);
	}
	double GetY(double phi, double r)
	{
		return r * sin(phi);
	}
	void PolarPlot(HDC dc, Func f, double phi_min, double phi_max, bool axes = true, bool grid = true)
	{
		if (axes)
			Axes(dc);
		if (grid)
		{
			Grid(dc);
			Coordinates(dc);
		}
		
		double 
			phi = phi_min,
			r = f(phi),
			x = GetX(phi, r),
			y = GetY(phi, r);
		this->MoveTo(x, y);
		for (phi; phi < phi_max; phi += 0.01)
		{
			r = f(phi);
			x = GetX(phi, r),
			y = GetY(phi, r);
			this->LineTo(dc, x, y);
		}
		this->LineTo(dc, GetX(phi_max, f(phi_max)), GetY(phi_max, f(phi_max)));
	}
	void Render(HDC);
};

void Scene2D::Render(HDC dc, Model2D model)
{
	model.UpdateVertices();
	Matrix <int> mEdg = model.GetEdges();
	int edgCount = mEdg.GetRows();
	for (int i = 1; i <= edgCount; i++)
	{
		int v1 = mEdg(i, 1), v2 = mEdg(i, 2);
		double
			x1 = model.GetVertexX(v1),
			y1 = model.GetVertexY(v1),
			x2 = model.GetVertexX(v2),
			y2 = model.GetVertexY(v2);
		MoveTo(x1, y1);
		LineTo(dc, x2, y2);
	}
}
void Scene2D::Render(HDC dc)
{
	Render(dc, pinwheel.Spinner);
	Render(dc, pinwheel.Stick);
	Axes(dc);
	//Grid(dc);
	Coordinates(dc);
}
#endif SCENE_2D_H
