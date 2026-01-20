#include<iostream>
#include<cg/core/Vec.h>

//using cg::core::Vec;

int main()
{
	cg::core::Vec<double, 3> a{ 1,2,3 };
	std::cout << a[0] << ", " << a[1] << ", " << a[2] << std::endl;
}

