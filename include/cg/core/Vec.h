
#pragma once
#include <array>
#include <cmath>
#include <initializer_list>
#include <cassert>
#include <algorithm>
#include <stdexcept>

//Namespaces prevent name collisions in large projects.
namespace cg::core
{
	template<typename T, size_t N>
	class Vec
	{
	private:
		std::array<T, N> m_vec;


	public:

		constexpr Vec<T, N>() { m_vec.fill(T{0}); }

		Vec<T,N>(std::initializer_list<T> list)
		{
			assert(list.size() == N);
			std::copy(list.begin(), list.end(), m_vec.begin());
		}

		constexpr T& operator[](size_t i) { 
			return m_vec[i];				
		}

		constexpr const T& operator[](size_t i)  const { return m_vec[i]; }
		//There are two consts here. The last const is method constness. This means method does not modify objects. 
		//It allows you to access elements from const vectors.

		//Provide both methods. This is called const correctness
		//T& operator[](size_t i);              // for modifying
		//const T& operator[](size_t i) const; // for reading

		//The first const  prevents accidental modification through the reference.

		//constexpr : Allows compile-time evaluation when possible

		//Addition operator overloading
		Vec<T, N> operator+(const Vec<T, N>& other) const
		{
			//Size check is unnecessary. This will always be true at compile time.
			// if (this->m_vec.size() != other.m_vec.size())
			// 	throw std::runtime_error("Size of vector do not match");

			Vec<T, N> result;
			for (int i = 0; i < this->m_vec.size(); ++i)
			{
				result.m_vec[i] = this->m_vec[i] + other.m_vec[i];
			}
			return result;
		}

		//Compound addition
		Vec<T,N>& operator+=(const Vec<T,N>& other) 
		{
			for (int i = 0; i < this->m_vec.size(); ++i)
			{
				this->m_vec[i] +=  other.m_vec[i];
			}
			return *this;
		}

		void PrintVec() const
		{
			for (const auto& elem : m_vec)
			{
				std::cout << elem << " ";
			}
			std::cout << std::endl;
		}
	};

	using Vec2D = Vec<double, 2>;
	using Vec3D = Vec<double, 3>;

	using Vec2F = Vec<float, 2>;
	using Vec3F = Vec<float, 3>;

	using Vec2I = Vec<int, 2>;
	using Vec3I = Vec<int, 3>;
	
}

