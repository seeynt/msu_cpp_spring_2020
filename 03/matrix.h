#include <cstddef>
#include <stdlib.h>
#include <stdexcept>

class Matrix {
	std::size_t rows;
	std::size_t cols;

	class Row {
		int* A;
		std::size_t cols;
	public:
		Row(std::size_t c);
		const int& operator[](std::size_t j) const;
    	int& operator[](std::size_t j);
    	~Row();
	};

	Row** B;

public:
	Matrix(std::size_t r, std::size_t c);
	std::size_t getRows() const;
	std::size_t getCols() const;
	~Matrix();

    const Row& operator[](std::size_t i) const;
    Row& operator[](std::size_t i);
    void operator*=(int d);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};