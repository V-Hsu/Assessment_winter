#include"matrix.h"
Matrix::Matrix(int rows,int cols)
{
    this->rows=rows;
    this->cols=cols;
}

Matrix::~Matrix()
{
    this->rows=0;
    this->cols=0;
}

std::istream& operator>>(std::istream& in, Matrix& matrix)
{
    std::cout<<"rows = "<<std::endl;
    in>>matrix.rows;
    std::cout<<"cols = "<<std::endl;
    in>>matrix.cols;
    return in;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    os<<"rows = "<<matrix.rows<<" cols = "<<matrix.cols;
    return os;
}

Matrix Matrix::operator*(Matrix &other)
{
    Matrix temp(this->rows*other.rows,this->cols*other.cols);
    return temp;
}