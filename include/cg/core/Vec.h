
#pragma once
#include <array>
#include <cmath>
#include <initializer_list>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <limits>

// Namespaces prevent name collisions in large projects.
namespace cg::core
{
	template <typename T>
	// constexpr T eps = static_cast<T>(1e-12);
	constexpr T eps = std::numeric_limits<T>::epsilon();

	enum class POSITION
	{
		LEFT,
		RIGHT,
		BEHIND,
		BEYOND,
		ORIGIN,
		DESTINATION,
		MIDDLE
	};

	template <typename T, size_t N>
	class Vec
	{
	private:
		std::array<T, N> m_vec;

	public:
		constexpr Vec<T, N>() { m_vec.fill(T{0}); }

		Vec<T, N>(std::initializer_list<T> list)
		{
			assert(list.size() == N);
			std::copy(list.begin(), list.end(), m_vec.begin());
		}

		constexpr T &operator[](size_t i)
		{
			return m_vec[i];
		}

		constexpr const T &operator[](size_t i) const { return m_vec[i]; }
		// There are two consts here. The last const is method constness. This means method does not modify objects.
		// It allows you to access elements from const vectors.

		// Provide both methods. This is called const correctness
		// T& operator[](size_t i);              // for modifying
		// const T& operator[](size_t i) const; // for reading

		// The first const  prevents accidental modification through the reference.

		// constexpr : Allows compile-time evaluation when possible

		// Addition operator overloading
		constexpr Vec<T, N> operator+(const Vec<T, N> &other) const
		{
			// Size check is unnecessary. This will always be true at compile time.
			//  if (this->m_vec.size() != other.m_vec.size())
			//  	throw std::runtime_error("Size of vector do not match");

			Vec<T, N> result;
			for (size_t i = 0; i < this->m_vec.size(); ++i)
			{
				result.m_vec[i] = this->m_vec[i] + other.m_vec[i];
			}
			return result;
		}

		// Compound addition
		constexpr Vec<T, N> &operator+=(const Vec<T, N> &other)
		{
			for (size_t i = 0; i < this->m_vec.size(); ++i)
			{
				this->m_vec[i] += other.m_vec[i];
			}
			return *this;
		}

		// Print vector elements
		void PrintVec() const
		{
			for (const auto &elem : m_vec)
			{
				std::cout << elem << " ";
			}
			std::cout << std::endl;
		}

		T NormSquared() const
		{
			T normSquared = T{0};

			for (const auto &elem : m_vec)
			{
				normSquared += elem * elem;
			}
			return normSquared;
		}

		T Magnitude() const
		{
			return sqrt(NormSquared());
		}

		Vec<T, N> &Normalise()
		{
			T magnitude = Magnitude();
			if (magnitude < eps<T>)
				throw std::runtime_error("Can not normalise zero vector");

			// for(size_t i=0; i<m_vec.size(); ++i)
			// {
			// 	m_vec[i] = m_vec[i]/magnitude;
			// }

			T invMagnitude = T{1} / magnitude;
			for (auto &elem : m_vec)
				elem = elem * invMagnitude;

				/*
				1. Division vs. Multiplication (The Performance Win)Floating-point division ($x / y$) is one 
					of the most computationally expensive arithmetic operations a CPU can perform, often taking anywhere 
					from 10 to 40 clock cycles depending on the architecture. Multiplication ($x \times y$), on the other hand, 
					usually takes only 3 to 5 clock cycles.First Method: Performs a division operation $N$ times (once for every 
					element in the vector).
					Second Method: Performs exactly one division (T{1} / magnitude) to get the reciprocal,
				 	and then performs $N$ multiplications.For a 3D vector ($N=3$), it's the difference between 3 divisions versus
				 	1 division + 3 multiplications. For larger dimensions, the performance savings multiply significantly.
				  
				2. Range-Based for Loop vs. Indexed LoopThe second method uses a range-based for loop (for (auto &elem : m_vec)),
				   which offers several advantages:No Out-of-Bounds Risks: It completely eliminates the risk of off-by-one errors or
				    indexing bugs because the compiler handles the bounds automatically.
					*/

			return *this;
		}

		constexpr Vec<T, N> operator-(const Vec<T, N> &other) const
		{
			Vec<T, N> result;
			// assert(this->m_vec.size() == other.m_vec.size());
			for (size_t i = 0; i < m_vec.size(); ++i)
				result[i] = m_vec[i] - other.m_vec[i];
			return result;

			// Below implementation is simple and avoids code duplication.
			// Vec<T,N> result(*this);
			// result -= other;
			// return result;
		}

		Vec<T, N> &operator-=(const Vec<T, N> &other)
		{
			for (size_t i = 0; i < m_vec.size(); ++i)
				m_vec[i] = m_vec[i] - other.m_vec[i];
			return *this;
		}

		constexpr Vec<T, N> operator*(const T value) const
		{
			Vec<T, N> result;
			for (size_t i = 0; i < m_vec.size(); ++i)
				result[i] = m_vec[i] * value;
			return result;
		}

		Vec<T, N> &operator*=(const T value)
		{
			for (size_t i = 0; i < m_vec.size(); ++i)
				m_vec[i] = m_vec[i] * value;
			return *this;
		}

		constexpr Vec<T, N> operator/(const T value) const
		{
			Vec<T, N> result;
			if (std::abs(value) <= eps<T>)
				throw std::runtime_error("Division by zero scalar");

			for (size_t i = 0; i < m_vec.size(); ++i)
				result[i] = m_vec[i] / value;
			return result;
		}

		Vec<T, N> &operator/=(const T value)
		{
			if (std::abs(value) <= eps<T>)
				throw std::runtime_error("Division by zero scalar");
			for (size_t i = 0; i < m_vec.size(); ++i)
				m_vec[i] = m_vec[i] / value;
			return *this;
		}

		constexpr bool operator==(const Vec<T, N> &other) const
		{
			for (size_t i = 0; i < m_vec.size(); ++i)
			{
				// 	if((m_vec[i] - other.m_vec[i])>eps<T>)	//doesnot compare for negetive values, Use abs(difference)
				// 	return false;

				T diff = m_vec[i] - other.m_vec[i];
				if (diff * diff > eps<T> * eps<T>) // use squared comparison. it is faster and advanced.
					return false;
			}
			return true;
		}

		constexpr bool operator!=(const Vec<T, N> &other) const
		{
			return !(*this == other);
		}
	};

	template <typename T, size_t N>
	static T dotProduct(const Vec<T, N> &a, const Vec<T, N> &b)
	{
		T result = T{0};
		for (size_t i = 0; i < N; ++i)
		{
			result += a[i] * b[i];
		}
		return result;
	}

	template <typename T>
	static T crossProd2D(const Vec<T, 2> &vec1, const Vec<T, 2> &vec2)
	{
		T result = vec1[0] * vec2[1] - vec2[0] * vec1[1];
		return result;
	}

	template <typename T>
	static Vec<T, 3> crossProd3D(const Vec<T, 3> &vec1, const Vec<T, 3> &vec2)
	{
		Vec<T, 3> result;
		result[0] = vec1[1] * vec2[2] - vec2[1] * vec1[2];
		result[1] = vec2[0] * vec1[2] - vec1[0] * vec2[2];
		result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

		return result;
	}

	/*
		Alignment:
			Alignment describes how closely two vectors "agree" on a path. It’s about parallelism.
				The Vibe: Are they pointing the same way?
					The Measure: This is what the Dot Product tracks.
						Example: If you are pushing a box, your force is "aligned" with the box's movement if you’re pushing it straight ahead.

						| Result       | Meaning                                     |
						| ------------ | ------------------------------------------- |
						| **Positive** | Vectors point roughly in the same direction |
						| **Zero**     | Vectors are perpendicular (90°)             |
						| **Negative** | Vectors point in opposite directions        |


		Orientation:
			Orientation describes how an object is positioned or rotated in space relative to a fixed frame. It’s about tilt and facing.
				The Vibe: Which way is "up" or "forward" for this specific object?
					The Measure: This is often defined using the Cross Product to find a "normal" vector (a line sticking straight out of a surface).
					Example: A smartphone knows its "orientation" (portrait vs. landscape) by sensing which way gravity is pulling relative to its screen.
		

						
						If
							result > 0 => a, b, c are in counter-clockwise direction
							result < 0 => a, b, c are in clockwise direction
							result == 0 => a,b,c are collinear
	*/
			
	template <typename T>
	constexpr static int orient(const Vec<T, 2> &a, const Vec<T, 2> &b, const Vec<T, 2> &c)
	{
		T result = crossProd2D(b - a, c - a);
		if (result > eps<T>)
			return 1;
		if (result < -eps<T>)
			return -1;
		return 0;
	}

	template <typename T>
	constexpr bool isCollinear(const Vec<T, 2> &a, const Vec<T, 2> &b, const Vec<T, 2> &c)
	{
		return orient(a, b, c) == 0;
	}

	template <typename T>
	constexpr bool intersectSegments(const Vec<T, 2> &p1,
									 const Vec<T, 2> &p2,
									 const Vec<T, 2> &p3,
									 const Vec<T, 2> &p4)
	{
		int o1 = orient(p1, p2, p3);
		int o2 = orient(p1, p2, p4);
		int o3 = orient(p3, p4, p1);
		int o4 = orient(p3, p4, p2);

		// Proper intersection
		if (o1 * o2 < 0 && o3 * o4 < 0)
			return true;

		// Collinear / endpoint cases
		if (o1 == 0 && isOnSegment(p1, p2, p3))
			return true;
		if (o2 == 0 && isOnSegment(p1, p2, p4))
			return true;
		if (o3 == 0 && isOnSegment(p3, p4, p1))
			return true;
		if (o4 == 0 && isOnSegment(p3, p4, p2))
			return true;

		return false;
	}

	template <typename T>
	constexpr POSITION orientationPosition(const Vec<T, 2> &a, const Vec<T, 2> &b, const Vec<T, 2> &c)
	{
		int res = orient(a, b, c);
		if (res > 0)
			return POSITION::LEFT;
		if (res < 0)
			return POSITION::RIGHT;

		if (res == 0)
		{
			if (a == c)
				return POSITION::ORIGIN;
			if (b == c)
				return POSITION::DESTINATION;

			const Vec<T, 2> ab = b - a;
			const Vec<T, 2> ac = c - a;
			T dotRes = dotProduct(ab, ac);

			if (dotRes > ab.NormSquared())
				return POSITION::BEYOND;
			if (dotRes < 0)
				return POSITION::BEHIND;
		}
		return POSITION::MIDDLE;
	}

	template <typename T>
	constexpr bool isOnSegment(const Vec<T, 2> &a, const Vec<T, 2> &b, const Vec<T, 2> &c)
	{
		POSITION pos = orientationPosition(a, b, c);
		return pos == POSITION::ORIGIN || pos == POSITION::DESTINATION || pos == POSITION::MIDDLE;
	}

	template <typename T>
	T AreaOfPolygon(const std::vector<Vec<T, 2>> &iListOf2DVectors)
	{
		T totalSum = T{0};
		for (int i = 0; i < iListOf2DVectors.size(); ++i)
		{
			T sum = crossProd2D(iListOf2DVectors[i], iListOf2DVectors[(i + 1) % iListOf2DVectors.size()]);
			totalSum += sum;
		}
		return totalSum * T{0.5};
	}

	template <typename T>
	constexpr T distancePointPoint(const Vec<T, 2> &a, const Vec<T, 2> &b)
	{
		return (b - a).Magnitude();
	}

	template <typename T>
	constexpr T distancePointInfiniteSegment(const Vec<T, 2> &p, const Vec<T, 2> &a, const Vec<T, 2> &b)
	{
		Vec<T, 2> ab = b - a;
		Vec<T, 2> ap = p - a;

		T areaOfParallelogram = crossProd2D(ab, ap);
		// Area of parallelogram = base * height
		// Base = ab
		// Height =  distance from point p to line ab

		return std::abs(areaOfParallelogram) / ab.Magnitude();
	}

	template<typename T>
	constexpr T distancePointSegment(const Vec<T,2> &p, const Vec<T,2> &a, const Vec<T,2> &b)
	{
		Vec<T,2> ab = b-a;
		Vec<T,2> ap = p-a;
		//res is the scalar projection of ap onto ab, scaled by |ab|.
		T res = dotProduct(ab, ap);
		if(res <=0)
			return ap.Megnitude();
		else if(res >= ab.NormSquared())
		//imagine point P is on the point B
		//ap.ab would result in ab2.
		

		//Not checking distance — checking position along AB.
			return (p-b).Magnitude();
		else
			return distancePointInfiniteSegment(p, a, b);
	}

	using Vec2D = Vec<double, 2>;
	using Vec3D = Vec<double, 3>;

	using Vec2F = Vec<float, 2>;
	using Vec3F = Vec<float, 3>;

	using Vec2I = Vec<int, 2>;
	using Vec3I = Vec<int, 3>;

	template<typename T>
	struct Line2
	{
		Vec<T, 2> point;
		Vec<T, 2> direction;

	};

	enum class LineIntersectiontype
	{
		Intersecting,
		Parallel,
		Coincident,
		NotIntersecting
	};

	template<typename T>
	struct IntersectionLinesResult
	{
		LineIntersectiontype type;
		Vec<T,2> point;
	};

	template<typename T>
	IntersectionLinesResult<T> IntersectLines(const Line2<T>& line1, const Line2<T>& line2 )
	{
		IntersectionLinesResult<T> result;

		//Get the data from lines
		Vec<T,2> line1Pt = line1.point;
		Vec<T,2> line1Dir = line1.direction;
		Vec<T,2> line2Pt = line2.point;
		Vec<T,2> line2Dir = line2.direction;

		//Take the cross product of directions
		//if the result is zero, => parallel or coincident
		//else intersecting.

		T crossRes = crossProd2D(line1Dir, line2Dir);

		if(abs(crossRes) < eps<T>)
		{
			//We need the orientation of two lines. 
			//Lets take a vector from point 1 to point 2. Compute the orientation of any one of the directions with this vector.
			//If the cross product result is zero, they are coincident lines.
			//else parallel lines.
			if(abs(crossProd2D((line2Pt - line1Pt), line1Dir ) )< eps<T>)
			{
				result.point = {};
				result.type = LineIntersectiontype::Coincident;
			} 
			else
			{
				result.point = {};
				result.type = LineIntersectiontype::Parallel;
			}
		}
		else
		{
			T t = crossProd2D((line2Pt - line1Pt), line1Dir) / crossRes;
			// Visit below notes to know how we arrived at above equation.
			/*

	===============================================================================
	2D Line–Line Intersection (Derivation Notes)
	===============================================================================

	Line representation (parametric form):
		L1(t) = p + t*r
		L2(u) = q + u*s

	where:
		p, q : points on the lines
		r, s : direction vectors
		t, u : scalar parameters

	At intersection:
		p + t*r = q + u*s

	Rearrange:
		t*r = (q - p) + u*s

	This is a vector equation with two unknowns (t, u).
	To solve for t, eliminate u using the 2D cross product.

	Key properties of 2D cross product:
		- cross(a, b) = 0  ⇔  a and b are parallel
		- cross(s, s) = 0
		- cross is linear

	Take cross product of both sides with s:

		cross(t*r, s) = cross((q - p) + u*s, s)

	Apply linearity:

		t*cross(r, s) = cross(q - p, s) + u*cross(s, s)

	Since:
		cross(s, s) = 0

	u vanishes, leaving:

		t*cross(r, s) = cross(q - p, s)

	If lines are not parallel:
		cross(r, s) ≠ 0

	Solve for t:

		t = cross(q - p, s) / cross(r, s)

	Intersection point:

		intersection = p + t*r

	Line classification:
		- cross(r, s) == 0 and cross(q - p, r) == 0 → Coincident
		- cross(r, s) == 0 and cross(q - p, r) != 0 → Parallel
		- cross(r, s) != 0 → Intersecting

	Rule of thumb:
		- To solve for t (line1 parameter), cross with s
		- To solve for u (line2 parameter), cross with r
	===============================================================================
	*/

			result.point = line1Pt + (t * line1Dir);
			result.type = LineIntersectiontype::Intersecting;
		}
		return result;

	}

	template<typename T>
	IntersectionLinesResult<T> IntersectLineAndSegment(const Line2<T>& line1, const Vec<T,2>& pt1, const Vec<T,2>& pt2 )
	{
		IntersectionLinesResult<T> result;

		//Get the data from lines
		Vec<T,2> line1Pt = line1.point;
		Vec<T,2> line1Dir = line1.direction;

		Vec<T,2> segmentVec = pt2-pt1;

		//get the cross product between 
		if(std::abs(crossProd2D(segmentVec, line1Dir))<eps<T>)
		{
			if(abs(crossProd2D((line1Pt-pt1),segmentVec))<eps<T>)
			{
				result.point = {};
				result.type = LineIntersectiontype::Coincident;
				return result;
			} 
			else
			{
				result.point = {};
				result.type = LineIntersectiontype::Parallel;
				return result;
			}

		}
		else
		{
			T u = crossProd2D((line1Pt -pt1), line1Dir) / crossProd2D(segmentVec, line1Dir );
			if (u >= T(0) && u <= T(1))
			{
				result.point = pt1 + (u * segmentVec);
				result.type = LineIntersectiontype::Intersecting;
			}
			else
			{
				result.point = {};
				result.type = LineIntersectiontype::NotIntersecting;
			}
		}

		return result;
	}


	template<typename T>
	IntersectionLinesResult<T> IntersectLineSegmentAndLineSegment(const Vec<T,2>& Line1Pt1, const Vec<T,2>& Line1Pt2, const Vec<T,2>& Line2Pt1,  const Vec<T,2>& Line2Pt2  )
	{
		IntersectionLinesResult<T> result;

		//Get the data from lines
		Vec<T,2> segmentVec1 = Line1Pt2 - Line1Pt1;
		Vec<T,2> segmentVec2 = Line2Pt2 - Line2Pt1;

		//L1(t) = Line1Pt1 + t * segmentVec1;
		//L2(u) = Line2Pt1 + u * segmentVec2;

		//get the cross product between 
		if(std::abs(crossProd2D(segmentVec1, segmentVec2))<eps<T>)
		{
			if(abs(crossProd2D((Line1Pt1-Line2Pt1),segmentVec2))<eps<T>)
			{
				result.point = {};
				result.type = LineIntersectiontype::Coincident;
				//Need some more cases to manage. Disjoint and overlap cases
				return result;
			} 
			else
			{
				result.point = {};
				result.type = LineIntersectiontype::Parallel;
				return result;
			}

		}
		else
		{
			T t = crossProd2D((Line2Pt1 - Line1Pt1), segmentVec2) / crossProd2D(segmentVec1, segmentVec2 );
			T u = crossProd2D((Line1Pt1 - Line2Pt1), segmentVec1) / crossProd2D(segmentVec2, segmentVec1 );
			if (u >= T(0) && u <= T(1) && t >= T(0) && t <= T(1))
			{
				result.point = Line2Pt1 + (u * segmentVec2);
				result.type = LineIntersectiontype::Intersecting;
			}
			else
			{
				result.point = {};
				result.type = LineIntersectiontype::NotIntersecting;
			}
		}

		return result;
	}

}


