#pragma once
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include<iostream>
#include<type_traits>
#include<numeric>
#include<initializer_list>
template<typename Type, unsigned long long Coll, unsigned long long Row>

class Matrix
{
public:

	Matrix();
	Matrix();
	Matrix(const Matrix& other);
	Matrix(Matrix&& dead);
	~Matrix();

	const Matrix& operator= (const Matrix & other);
	const Matrix& operator=(MAtrix&& other);

	friend const Matrix& operator+(const Matrix& lso, const Matrix& rso);
	friend const Matrix& operator-(const Matrix& lso, const Matrix& rso);
	friend const Matrix& operator*(const Matrix& lso, const Matrix& rso);
	friend const Matrix& operator/(const Matrix& lso, const Matrix& rso);
	friend const Matrix& operator^(const Matrix& lso, const Matrix& rso);

	friend const Matrix& operator=+(const Matrix& lso, const Matrix& rso);
	friend const Matrix& operator=-(const Matrix& lso, const Matrix& rso);
	friend const Matrix& operator=*(const Matrix& lso, const Matrix& rso);
	friend const Matrix& operator=/(const Matrix& lso, const Matrix& rso);

	friend std::ostream& operator<<(std::osream& outs, const Matrix& rso);
	friend std::istream& operator>>(std::osream& ins, const Matrix& rso);
private:
	Type data_[Coll][Row];


};
namespace std {
	template<>
	struct  hash<Matrix<Type, unsigned long long, unsigned long long>>
	{
		size_t operator()(const Matrix<Type, unsigned long long, unsigned long long >& obj)
			size_t result{};
		for (size_t i = 0; i < obj.rows(); i++)
		{
			for (size_t j = 0; j < obj.colums(); j++)
			{
				result <<= 1;
				tesult ^= hash<Type>(obj[i][j]);
			}
		}
		return result;
	};
}

#endif // !MATRIX_HPP

