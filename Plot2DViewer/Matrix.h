#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

using namespace std;


template <typename Cell = double>


class Matrix
{
private:
	int rows; //���������� ����� �������
	int cols; //���������� �������� �������
	Cell** cells;
	void AllocateCells(int, int); // ��������� ������ ��� �������
	void FreeCells();
public:
	Matrix() : rows(0), cols(0), cells(nullptr) {}	// ����������� �� ���������
	Matrix(const Matrix&);					// ����������� �����������
	Matrix(int, int);							// ����������� ������� �������
	Matrix(int, int, Cell*);						// ����������� ������� �� ������
	~Matrix();								// ����������

	Cell& operator()(int i, int j) { return cells[i - 1][j - 1]; }

	Matrix& operator = (const Matrix&);		// ���������� ��������� ������������
	Matrix  operator + (const Matrix&);		// �������� ������
	Matrix  operator - (const Matrix&);		// ��������� ������
	Matrix  operator * (const Matrix&);		// ��������� ������

	friend istream& operator >> <> (istream&, Matrix&);			// ���������� ��������� >> ��� ����� �������
	friend ostream& operator << <> (ostream&, const Matrix&);	// ���������� ��������� << ��� ������ �������
	int GetRows() { return rows; }
	int GetCols() { return cols; }
};


template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.rows, M.cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int Rows, int Cols)
{
	AllocateCells(Rows, Cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int Rows, int Cols, Cell* list)
{
	AllocateCells(Rows, Cols);
	int count = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; count++, j++)
			cells[i][j] = list[count];
}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if (!(rows == M.rows && cols == M.cols))
	{
		FreeCells();
		AllocateCells(M.rows, M.cols);
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && cols == M.cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && cols == M.cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				res.cells[i][j] -= M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	Matrix<Cell> res(rows, M.cols);
	if (cols == M.rows)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < M.cols; j++)
			{
				Cell summ = 0;
				for (int k = 0; k < cols; k++)
					summ += cells[i][k] * M.cells[k][j];
				res.cells[i][j] = summ;
			}
		}
	}
	return res;
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int Rows, int Cols)
{
	cells = new Cell * [Rows];
	for (int i = 0; i < Rows; i++)
		cells[i] = new Cell[Cols];
	rows = Rows;
	cols = Cols;
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i = 0; i < rows; i++)
		delete cells[i];
	delete cells;
	rows = cols = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i = 0; i < M.rows; i++)
		for (int j = 0; j < M.cols; j++)
			fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i = 0; i < M.rows; i++)
	{
		fo << "  ";
		for (int j = 0; j < M.cols; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

#endif MATRIX_H
