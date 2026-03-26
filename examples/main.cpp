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

	c = c+b;
	c.PrintVec();

	double magnitude = c.Magnitude();

	std::cout<<"Magnitude = "<<magnitude<<std::endl;

	c.Normalise();
	c.PrintVec();

	double mag = c.Magnitude();

	std::cout<<"Magnitude = "<<mag<<std::endl;

	cg::core::Vec2D vec2d1 = {2,3};
	cg::core::Vec2D vec2d2 = {4,5};

	double res = crossProd2D(vec2d1, vec2d2);
	std::cout<<"Cross prod 2d res = " << res <<std::endl;

	
	cg::core::Vec3D res3d = crossProd3D(a, b);
	std::cout<<"Cross prod 3d res = "<<std::endl;
	res3d.PrintVec();

	bool rc = a==b;

	bool sc = a!=b;

	//bool kc = vec2d1 == b;


	return 0;
}

