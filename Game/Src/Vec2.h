#pragma once

template<typename T>
class _Vec2
{
public:
	_Vec2() = default;
	_Vec2( T x,T y ) noexcept
		:
		x( x ),
		y( y )
	{}
	_Vec2( const _Vec2& rhs ) noexcept
		:
		x( rhs.x ),
		y( rhs.y )
	{}
	_Vec2& operator=( const _Vec2& rhs ) noexcept
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	_Vec2 operator+( const _Vec2& rhs ) const noexcept
	{
		return { x + rhs.x,y + rhs.y };
	}
	_Vec2& operator+=( const _Vec2& rhs ) noexcept
	{
		return *this = *this + rhs;
	}
	_Vec2 operator-( const _Vec2& rhs ) const noexcept
	{
		return { x - rhs.x,y - rhs.y };
	}
	_Vec2& operator-=( const _Vec2& rhs ) noexcept
	{
		return *this = *this - rhs;
	}
	_Vec2 operator*( T rhs ) const noexcept
	{
		return { x * rhs,y * rhs };
	}
	_Vec2& operator*=( T rhs ) noexcept
	{
		return *this = *this * rhs;
	}
	bool operator==( const _Vec2& rhs ) noexcept
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=( const _Vec2& rhs ) noexcept
	{
		return !(*this == rhs);
	}
	T x;
	T y;
};

typedef _Vec2<float> Vec2;
typedef _Vec2<int> Vei2;