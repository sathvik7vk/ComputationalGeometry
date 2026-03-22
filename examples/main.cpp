#include<iostream>
#include<cg/core/Vec.h>

//using cg::core::Vec;

int main()
{
	cg::core::Vec3D a{ 1,2,3 };
	cg::core::Vec3D b{ 1,2,3 };
	cg::core::Vec3D c = a+b;	//addition
	

	c.PrintVec();

	c+=b; // compound addition
	c.PrintVec();

	return 0;
}

