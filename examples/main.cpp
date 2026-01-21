#include<iostream>
#include<cg/core/Vec.h>

//using cg::core::Vec;

int main()
{
	cg::core::Vec3D a{ 1,2,3 };
	cg::core::Vec3D b{ 1,2,3 };
	a + b;
	std::cout << a[0] << ", " << a[1] << ", " << a[2] << std::endl;
}

