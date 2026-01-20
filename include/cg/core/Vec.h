
#pragma once
#include <array>
#include <cmath>
#include <initializer_list>
#include <cassert>
#include <algorithm>


//Namespaces prevent name collisions in large projects.
namespace cg::core
{
	template<typename T, size_t N>
	class Vec
	{
	private:
		std::array<T, N> m_vec;


	public:

		constexpr Vec() { m_vec.fill(T{0}); }

		Vec(std::initializer_list<T> list)
		{
			assert(list.size() == N);
			std::copy(list.begin(), list.end(), m_vec.begin());
		}

		constexpr T& operator[](size_t i) { return m_vec[i]; }

		constexpr const T& operator[](size_t i)  const { return m_vec[i]; }
		//There are two consts here. The last const is method constness. This means method does not modify objects. 
		//It allows you to access elements from const vectors.

		//Provide both methods. This is called const correctness
		//T& operator[](size_t i);              // for modifying
		//const T& operator[](size_t i) const; // for reading

		//The first const  prevents accidental modification through the reference.

		//constexpr : Allows compile-time evaluation when possible
	};
	
}

