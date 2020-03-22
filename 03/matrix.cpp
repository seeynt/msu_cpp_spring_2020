#include "matrix.h"

Matrix::Row::Row(std::size_t c) {
	this->cols = c;
	if (!(A = (int*)malloc(c * sizeof(int))))
		throw std::out_of_range("Allocation error in row");
}

const int& Matrix::Row::operator[](std::size_t j) const {
	if (j >= this->cols)
		throw std::out_of_range("Out of range error in j");
	return *(this->A + j);
}

int& Matrix::Row::operator[](std::size_t j) {
	if (j >= this->cols)
		throw std::out_of_range("Out of range error in j");
	return *(this->A + j);
}

Matrix::Row::~Row() {
	free(A);
}

Matrix::Matrix(std::size_t r, std::size_t c) {
	Matrix::Row* ptr;
	this->rows = r, this->cols = c;

	if (!(B = (Matrix::Row**)malloc(r * sizeof(Matrix::Row*))))
		throw std::out_of_range("Allocation error in matrix");

	for (std::size_t i = 0; i < r; ++i) {
		try {
			ptr = new Matrix::Row(c);
		}
		catch(std::out_of_range& oor) {
			for (int j = 0; j < i; ++j)
				delete B[j];
			free(B);
			throw oor;
		}
		B[i] = ptr;
	}
}

std::size_t Matrix::getRows() const {
	return this->rows;
}

std::size_t Matrix::getCols() const {
	return this->cols;
}

const Matrix::Row& Matrix::operator[](std::size_t i) const {
	if (i >= this->rows)
		throw std::out_of_range("Out of range error in i");
	return *(this->B[i]);
}

Matrix::Row& Matrix::operator[](std::size_t i) {
	if (i >= this->rows)
		throw std::out_of_range("Out of range error in i");
	return *(this->B[i]);
}

void Matrix::operator*=(int d) {
	for (std::size_t i = 0; i < this->rows; ++i)
    	for (std::size_t j = 0; j < this->cols; ++j)
        	(*this)[i][j] *= d;
}

bool Matrix::operator==(const Matrix& other) const {
    if (this == &other)
        return true;
    if (other.getCols() != this->cols || other.getRows() != this->rows)
    	return false;

    for (std::size_t i = 0; i < this->rows; ++i)
    	for (std::size_t j = 0; j < this->cols; ++j)
        	if ((*this)[i][j] != other[i][j])
        		return false;

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix::~Matrix() {
	for (std::size_t i = 0; i < this->rows; ++i)
		delete B[i];
	free(B);
}