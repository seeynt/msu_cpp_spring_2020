#include "matrix.h"

Matrix::Row::Row(std::size_t c) {
    cols = c;
    A = new int[cols];
}

const int& Matrix::Row::operator[](std::size_t j) const {
    if (j >= cols)
        throw std::out_of_range("Out of range error in j");
    return A[j];
}

int& Matrix::Row::operator[](std::size_t j) {
    if (j >= cols)
        throw std::out_of_range("Out of range error in j");
    return A[j];
}

Matrix::Row::~Row() {
    delete[] A;
}

Matrix::Matrix(std::size_t r, std::size_t c) {
    Row* ptr;
    rows = r, cols = c;

    B = new Row*[rows];

    for (std::size_t i = 0; i < rows; ++i) {
        try {
            ptr = new Matrix::Row(cols);
        }
        catch(std::bad_alloc& ba) {
            for (std::size_t j = 0; j < i; ++j)
                delete B[j];

            delete[] B;
            throw ba;
        }
        B[i] = ptr;
    }
}

std::size_t Matrix::getRows() const {
    return rows;
}

std::size_t Matrix::getCols() const {
    return cols;
}

const Matrix::Row& Matrix::operator[](std::size_t i) const {
    if (i >= rows)
        throw std::out_of_range("Out of range error in i");
    return *B[i];
}

Matrix::Row& Matrix::operator[](std::size_t i) {
    if (i >= rows)
        throw std::out_of_range("Out of range error in i");
    return *B[i];
}

void Matrix::operator*=(int d) {
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            (*this)[i][j] *= d;
}

bool Matrix::operator==(const Matrix& other) const {
    if (this == &other)
        return true;
    if (other.getCols() != cols || other.getRows() != rows)
        return false;

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            if ((*this)[i][j] != other[i][j])
                return false;

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix::~Matrix() {
    for (std::size_t j = 0; j < rows; ++j)
        delete B[j];
    delete[] B;
}
