#pragma once
#ifndef PINWHEEL_H
#define PINWHEEL_H

#include "Model2D.h"

struct Pinwheel {
	Model2D Spinner;
	Model2D Stick;
	Pinwheel(Model2D sp, Model2D st) : Spinner(sp), Stick(st) {}
	void Rotation(double phi)
	{
		Spinner.PivotRotation(phi);
	}
	void Rotation(double psi, double x, double y)
	{   
		this->Translation(-x, -y);
		Spinner.UpdateVertices();
		Stick.UpdateVertices();
		Spinner.PivotRotation(psi);
		Stick.PivotRotation(psi);
		this->Translation(x, y);
	}
	void Apply(Matrix<> A)
	{
		Spinner.Apply(A);
		Stick.Apply(A);
	}
	void Scaling(double kx, double ky)
	{
		Spinner.PivotScaling(kx, ky);
		Stick.PivotScaling(kx, ky);
	}
	void Translation(double deltaX, double deltaY)
	{
		Spinner.PivotTranslation(deltaX, deltaY);
		Stick.PivotTranslation(deltaX, deltaY);
	}
};
#endif PINWHEEL_H 