#pragma once
#include<iostream>
class Matrix
{
    friend std::istream& operator>>(std::istream& in, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
private:
    int rows;
    int cols;
    int **matrix;

public:
    Matrix(int rows,int cols);
    ~Matrix();
    Matrix operator*(Matrix &other);
};
