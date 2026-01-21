#include<iostream>
#include<cg/core/Vec.h>

//using cg::core::Vec;

int main()
{
	cg::core::Vec3D a{ 1,2,3 };
	cg::core::Vec3D b{ 1,2,3 };
	cg::core::Vec3D c = a+b;
	std::cout << c[0] << ", " << c[1] << ", " << c[2] << std::endl;
}

