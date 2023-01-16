#pragma once
#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

#include "Matrix.h"
Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Identity()
{
	return Translation(0, 0);
}

Matrix<> Rotation(double t)
{
	double R[9] = {
		cos(t), -sin(t), 0,
		sin(t), cos(t), 0,
		0, 0, 1 };
	return Matrix<>(3, 3, R);
}

Matrix<> Rotation(double c, double s)
{
	double cs = 1 / sqrt(c * c + s * s);
	c *= cs;
	s *= cs;
	double R[9] = {
		c, -s, 0,
		s, c, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, R);
}

Matrix<> Scaling(double kx, double ky)
{
	double S[9] = {
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, S);
}

Matrix<> MappingOX()
{
	return Scaling(1, -1);
}

Matrix<> MappingOY()
{
	return Scaling(-1, 1);
}

Matrix<> MappingO()
{
	return Scaling(-1, -1);
}

Matrix<> Mapping(double mx, double my)
{
	if (abs(mx) != 1) mx = 1;
	if (abs(my) != 1) my = 1;
	return  Scaling(mx, my);
}
// Составные аффинные преобразования

Matrix<> Rotation(double t, double X, double Y) // Матрица поворота на угол t против ч.с. относительно точки
{
	return Translation(X, Y) * Rotation(t) * Translation(-X, -Y);
}

Matrix<> Mapping(double x1, double x2, double y1, double y2) // МАтрица отражения относительно прямой, проходящей через 2 точки
{
	/*if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}*/
	Matrix<>ans;
	double
		deltaX = x2 - x1,
		deltaY = y2 - y1,
		hyp = sqrt(deltaX * deltaX + deltaY * deltaY),
		c = deltaX,
		s = deltaY;
	if(y1==y2)
		ans = Translation(x1, y1) * MappingOX() * Translation(-x1, -y1);
	else
		if (x1==x2)
			ans = Translation(x1, y1) * MappingOY() * Translation(-x1, -y1);
		else
			ans = Translation(x1, y1) * Rotation(c, s) * MappingOX() * Rotation(c, -s) * Translation(-x1, -y1);
	ofstream fo("MatrixOutput.txt");
	if (fo.is_open())
	{
		fo << x1 << " " << y1 << '\n' << x2 << " " << y2;
	}
	return ans;
}


// Здесь требуется реализовать функции, возвращающие матрицы базовых АП:
// Identity() - тождественное АП;
// Rotation(t) - поворот на угол t;
// Rotation(c, s) - поворот на угол, косинус и синус которого пропорциональны величинам c и s;
// Scaling(kx, ky) - масштабирование;
// Mapping (различные виды отражений) - по желанию, для создания матриц отражения можно использовать функцию Scaling.

// В приведённом примере используется конструктор матрицы из списка.
// Приветствуются идеи о других способах создания матриц.
// Например, вызов функции, создающей единичную матрицу,
// с последующим переопределением некоторых её коэффициентов.

#endif AFFINE_TRANSFORM_H