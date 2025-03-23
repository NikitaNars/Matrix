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

	unsigned long long rows() const { return Row; }
	unsigned long long columns() const { return Coll; }

	template<unsigned long long Coll1, unsigned long long Row1>
	friend const Matrix operator+(const Matrix<Type, Coll, Row>& lso, const Matrix < Type, Coll1, Row1 > & rso)
	{
		if (lso.columns() == rso.columns() && lso.rows() == rso.rows())
		{
			Matrix<Type, Coll, Row> res;
			for (unsigned long long i = 0; i < lso.rows(); i++)
			{
				for (unsigned long long j = 0; j < lso.columns(); j++)
				{
					res(i, j) = lso(i, j) + rso(i, j);
				}
			}
			return res;
		}
		
		
	}
	template<unsigned long long Coll1, unsigned long long Row1>
	friend const Matrix operator-(const Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll1, Row1>& rso)
	{
		if (lso.columns() == rso.columns() && lso.rows() == rso.rows())
		{
			Matrix<Type, Coll, Row> res;
			for (unsigned long long i = 0; i < Row; i++)
			{
				for (unsigned long long j = 0; j < Coll; j++)
				{
					res[i][j] = lso[i][j] - rso[i][j];
				}
			}
			return res;
		}

	}
	template<unsigned long long Coll1, unsigned long long Row1>
	friend const Matrix operator*(const Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll1, Row1>& rso)
	{
		if (lso.columns() != rso.rows() || lso.columns() != rso.columns())
		{
			throw std::exception("Умножение невозможно");
		}
		Matrix<Type, Coll, Row>res;
		if (lso.columns() == rso.rows())
		{
			for (unsigned long long i = 0; i < lso.rows(); ++i) {
				for (unsigned long long j = 0; j < rso.columns(); ++j) {
					for (unsigned long long k = 0; k < lso.columns(); ++k) {
						res(i, j) += lso(i, k) * rso(k, j);
					}
				}
			}

			return res;
		}
		else
		{
			Matrix<Type, Row, Coll> reverseMatrix{};
			for (unsigned long long  i = 0; i < rso.rows(); i++)
			{
				for (unsigned long long  j = 0; j < rso.columns(); j++)
				{
					reverseMatrix[j][i] = rso[i][j];
				}
			}
			for (unsigned long long  i = 0; i < lso.rows(); i++)
			{
				for (unsigned long long  j = 0; j < reverseMatrix.columns(); j++)
				{
					for (unsigned long long  k = 0; k < lso.columns(); k++)
					{
						res[i][j] += lso[i][k] * reverseMatrix[k][j];
					}
				}
			}
			return res;
		}
	}
	template<typename Type, unsigned long long Coll, unsigned long long Row>

	friend const Matrix operator/(const Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll, Row>& rso) {
		// Вычисляем обратную матрицу для rso
		Matrix<Type, Coll, Row> inverse_rso = rso.inverse();

		// Умножаем lso на обратную матрицу rso
		return lso * inverse_rso;
	}
	

	template<unsigned long long Coll1, unsigned long long Row1>
	friend const Matrix& operator+=( Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll1, Row1>& rso)
	{
		return lso = lso + rso;

	}
	template<unsigned long long Coll1, unsigned long long Row1>
	friend const Matrix& operator-=( Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll1, Row1>& rso)
	{
		return lso = lso - rso;
	}
	template<unsigned long long Coll1, unsigned long long Row1>
	friend const Matrix& operator*=( Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll1, Row1>& rso)
	{
		return lso = lso * rso;
	}
	template<unsigned long long Coll1, unsigned long long Row1>
	friend const Matrix& operator/=( Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll1, Row1>& rso)
	{
		
	}
	Type& operator()(unsigned long long i, unsigned long long j) {
		return data_[i][j];
	}


	Matrix<Type, Coll, Row> inverse() const
	{
		if (Coll != Row) {
			throw std::invalid_argument("Обратная матрица существует только для квадратных матриц");
		}

		if (Coll == 2 && Row == 2) {
			Type det = data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
			if (det == 0) {
				throw std::invalid_argument("Матрица вырождена, обратной матрицы не существует");
			}

			Matrix<Type, Coll, Row> inv;
			inv(0, 0) = data_[1][1] / det;
			inv(0, 1) = -data_[0][1] / det;
			inv(1, 0) = -data_[1][0] / det;
			inv(1, 1) = data_[0][0] / det;

			return inv;
		}
		else {
			throw std::invalid_argument("Обратная матрица для матриц большего размера не реализована");
		}
	}
	template<unsigned long long Coll1, unsigned long long Row1>
	friend bool operator==(const Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll1, Row1>& rso) {
		if (lso.columns() == rso.columns() && lso.rows() == rso.rows()) {
			for (unsigned long long i = 0; i < lso.columns(); i++) {
				for (unsigned long long j{}; j < lso.rows(); j++) {
					if (lso[i][j] != rso[i][j]) {
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}
	template<unsigned long long Coll1, unsigned long long Row1>
	friend bool operator!=(const Matrix<Type, Coll, Row>& lso, const Matrix<Type, Coll1, Row1>& rso) {
		return !(a == b);
	}
	const Type& operator()(unsigned long long i, unsigned long long j) const {
		return data_[i][j];
	}
	Type* operator[](unsigned long long i) {
		if (i >= Coll) {
			throw std::out_of_range("Row index out of range");
		}
		return data_[i];
	}


	const Type* operator[](unsigned long long i) const {
		if (i >= Coll) {
			throw std::out_of_range("Row index out of range");
		}
		return data_[i];
	}

	const Type& at(unsigned long long i, unsigned long long j) const {
		if (i >= Coll || j >= Row) {
			throw std::out_of_range("Index out of range");
		}
		return data_[i][j];
	}
	Type& at(unsigned long long i, unsigned long long j) {
		if (i >= Coll || j >= Row) {
			throw std::out_of_range("Index out of range");
		}
		return data_[i][j];
	}

	friend std::ostream& operator<<(std::ostream& outs, const Matrix& rso)
	{
		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Coll; j++)
			{
				outs << rso[i][j] << " ";
			}
			outs << "\n";
		}
		return outs;
	}
	/*friend std::istream& operator>>(std::osream& ins, const Matrix& rso)
	{

	}*/
private:
	Type data_[Coll][Row];


};
namespace std {
	template<typename Type, unsigned long long Coll, unsigned long long Row>
	struct hash<Matrix<Type, Coll, Row>> {
		size_t operator()(const Matrix<Type, Coll, Row>& obj) const {
			size_t result = 0;
			for (unsigned long long i = 0; i < obj.rows(); ++i) {
				for (unsigned long long j = 0; j < obj.columns(); ++j) {
					result = (result << 1) ^ std::hash<Type>()(obj[i, j]);
				}
			}
			return result;
		}
	};
}
#endif // !MATRIX_HPP

