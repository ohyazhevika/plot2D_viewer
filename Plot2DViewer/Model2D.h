#pragma once
#ifndef MODEL_2D_H
#define MODEL_2D_H

#include <string>
#include "Matrix.h"
#include "AffineTransform.h"


class Model2D
{
private:
	Matrix <> Vertices; // Матрица вершин
	Matrix <int> Edges; // Матрица рёбер
	Matrix <> CumulativeAT; // Накапливающее аффинное преобразование
	Matrix<> InitialVertices; // Начальное состояние матрицы вершин 
	int P; // Точка опоры - задаётся своим номером в матрице вершин
	double Xp, Yp; // Координаты точки опоры в текущий момент
	double psi=0; // Угол поворота целой модели отн-но исх. положения
	double phi; // Угол поворота части модели относительно исходного положения
	double kx, ky; // Коэффициенты масштабирования вдоль локальных горизонтальной и вертикальной осей, проходящих через точку опоры
	double mx, my; // Флаги отражения относительно локальных осей
public:
	Model2D() : Vertices(), Edges(), CumulativeAT(Identity()), InitialVertices(), P(0), phi(0), kx(0), ky(0), mx(0), my(0), Xp(0), Yp(0)
	{}
	Model2D
	(const Matrix<> Vertices, const Matrix <int> Edges, 
	int P = 0, double Xp=0, double Yp=0, double phi = 0, double kx=1, double ky=1, double mx=1, double my=1 ) :
		Vertices(Vertices), Edges(Edges), CumulativeAT(Identity()), InitialVertices(Vertices), 
		P(P), Xp(Xp), Yp(Yp), phi(phi), kx(kx), ky(ky), mx(mx), my(my) {}
	Model2D(int, int, string, string, int P=0);

	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }

	double GetVertexX(int);
	double GetVertexY(int);
	double GetPsi() { return psi; }

	void Apply(Matrix<>);
	void UpdateVertices(); // подстановка новых зависящих от опорной точки параметров, описвающих положение модели

	void PivotRotation(double); // Вращение относительно опорной точки
	void PivotTranslation(double, double); // Перенос опорной точки модели на вектор
	void PivotScaling(double, double); // Масштабирование модели относительно горизонтальной и вертикальной локальных осей
	void PivotRotation(double, double, double);
};

Model2D::Model2D(int v_cnt, int e_cnt, string fv_name, string fe_name, int P) : CumulativeAT(Identity()), P(P), phi(0), kx(1), ky(1), mx(1), my(1)
{
	Vertices = Matrix<>(3, v_cnt);
	Edges = Matrix<int>(e_cnt, 2);
	ifstream
		fv(fv_name),
		fe(fe_name);
	if (fv.is_open())
	{
		fv >> Vertices;
	}
	fv.close();
	if (fe.is_open())
	{
		fe >> Edges;
	}
	InitialVertices = Vertices;
}
double Model2D::GetVertexX(int v) {
	return Vertices(1, v) / Vertices(3, v) ;
}
double Model2D::GetVertexY(int v)
{
	return Vertices(2, v) / Vertices (3, v);
}
void Model2D::Apply(Matrix<> A)
{
	CumulativeAT = A * CumulativeAT;
	//Vertices = CumulativeAT * InitialVertices;
	
	UpdateVertices();
}
void Model2D::UpdateVertices() //UpdateVertices the vertices
{
	Vertices = CumulativeAT * Translation(Xp, Yp) * Rotation(phi) * Scaling(kx, ky) * Scaling (mx, my) * InitialVertices;
}

void Model2D::PivotRotation(double Phi)
{
	phi += Phi;
}
void Model2D::PivotTranslation(double deltaX, double deltaY)
{
	Xp += deltaX;
	Yp += deltaY;
}
void Model2D::PivotScaling(double Kx, double Ky)
{
	kx *= Kx;
	ky *= Ky;
}
void Model2D::PivotRotation(double Psi, double X, double Y)
{
	psi += Psi;
}
#endif MODEL_2D_H