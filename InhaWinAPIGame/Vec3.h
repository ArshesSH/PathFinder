#pragma once

#include "MathSH.h"

template <typename T>
class Vec3 : public Vec2<T>
{
public:
	Vec3() {}
	Vec3( T x,T y,T z )
		:
		Vec2( x,y ),
		z( z )
	{}
	Vec3( const Vec3& vect )
		:
		Vec3( vect.x,vect.y,vect.z )
	{}
	template <typename T2>
	explicit operator Vec3<T2>() const
	{
		return{ (T2)x,(T2)y,(T2)z };
	}
	T		LenSq() const
	{
		return sq( *this );
	}
	T		Len() const
	{
		return sqrt( LenSq() );
	}
	Vec3&	Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}
	Vec3	GetNormalized() const
	{
		Vec3 norm = *this;
		norm.Normalize();
		return norm;
	}
	Vec3	operator-() const
	{
		return Vec3( -x,-y,-z );
	}
	Vec3&	operator=( const Vec3 &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	Vec3&	operator+=( const Vec3 &rhs )
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	Vec3&	operator-=( const Vec3 &rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	T		operator*( const Vec3 &rhs ) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	Vec3	operator+( const Vec3 &rhs ) const
	{
		return Vec3( *this ) += rhs;
	}
	Vec3	operator-( const Vec3 &rhs ) const
	{
		return Vec3( *this ) -= rhs;
	}
	Vec3&	operator*=( const T &rhs )
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}
	Vec3	operator*( const T &rhs ) const
	{
		return Vec3( *this ) *= rhs;
	}
	Vec3&	operator/=( const T &rhs )
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}
	Vec3	operator/( const T &rhs ) const
	{
		return Vec3( *this ) /= rhs;
	}
	bool	operator==( const Vec3 &rhs ) const
	{
		return x == rhs.x && y == rhs.y && rhs.z = z;
	}
	bool	operator!=( const Vec3 &rhs ) const
	{
		return !(*this == rhs);
	}
	static Vec3 GetCrossProduct( const Vec3& lhs, const Vec3& rhs )
	{
		return
		{
			Vec3(
				lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x 
			)
		};
	}
public:
	T z;
};