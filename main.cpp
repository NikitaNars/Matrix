#include "Matrix.hpp"
int main()
{
	Matrix<int, 2, 2>a;
	Matrix<int, 2, 2>b;

	a[0][0] = 10;
	a[0][1] = 15;
	a[1][0] = 8;
	a[1][1] = 7;

	b[0][0] = 101;
	b[0][1] = 15;
	b[1][0] = 8;
	b[1][1] = 7;
	bool c = a == b;
	std::cout << c;
	
	


}