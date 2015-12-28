//------------------------------------------------------------
// <copyright file="Vector2.hpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#ifndef TEASER_MATH_VECTOR2_HPP
#define TEASER_MATH_VECTOR2_HPP

#include <Teaser/Common.hpp>
#include <Teaser/Math/Angle.hpp>

namespace Teaser
{
class Vector2
{
public:
	Vector2()
	: x(0)
	, y(0)
	{
	}

	explicit Vector2(f32 xy)
	: x(xy)
	, y(xy)
	{
	}

	Vector2(f32 x, f32 y)
	: x(x)
	, y(y)
	{
	}

	~Vector2() {}

	union {
		f32 data[2];
		struct
		{
			f32 x, y;
		};
		struct
		{
			f32 r, g;
		};
		struct
		{
			f32 u, v;
		};
	};

	inline f32 lenthSquared() const { return x * x + y * y; }

	inline f32 length() const { return sqrtf(lenthSquared()); }

	inline void normalize()
	{
		f32 l = length();
		x /= l;
		y /= l;
	}

	inline f32 dot(const Vector2& vec)const { return x * vec.x + y * vec.y; }

	Angle angle(const Vector2& other) const
	{
		float angle = acos(dot(other) / (length() * other.length()));
		return Angle(angle, Angle::Radians);
	}

	/*Operators*/
	Vector2& operator*=(f32 f)
	{
		x *= f;
		y *= f;

		return *this;
	}

	Vector2& operator/=(f32 f)
	{
		x /= f;
		y /= f;

		return *this;
	}

	Vector2& operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	f32 operator[](int index) const { return data[index]; }
	f32& operator[](int index) { return data[index]; }

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);

};

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << "Vector2( " << vec.x << ", " << vec.y << ")" << std::endl;
	return stream;
}

Vector2 operator*(const Vector2& vec, f32 f)
{
	return Vector2(vec.x * f, vec.y * f);
}

Vector2 operator*(f32 f, const Vector2& vec)
{
	return Vector2(vec.x * f, vec.y * f);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

} // Teaser

#endif // TEASER_MATH_VECTOR2_HPP