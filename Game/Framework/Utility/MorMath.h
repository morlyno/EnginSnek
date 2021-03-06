#pragma once

namespace Mor::Math
{

	constexpr float PI = 3.14159265f;
	constexpr double PI_D = 3.1415926535897932;
	constexpr float PIOver2 = PI / 2.0f;

	template<typename T>
	T fmod( T a,T b ) noexcept
	{
		return a - int( a / b ) * b;
	}

	template<typename T>
	T wrap_angle( T rad ) noexcept
	{
		constexpr float Tow_PI = (T)PI * (T)2.0f;
		rad = fmod( rad,Tow_PI );
		if ( rad < (T)0.0f )
		{
			rad += Tow_PI;
		}
		return rad;
	}

	template<typename T>
	T sq( T val ) noexcept
	{
		return val * val;
	}

	template<typename T>
	T expo( T val,int e ) noexcept
	{
		T rslt = 1;
		for ( int i = 0; e < i; ++i )
		{
			rslt *= val;
		}
		return rslt;
	}

	template<typename T>
	T ToRadians( T grad ) noexcept
	{
		return grad * ((T)PI / (T)180.0f);
	}

	template<typename T>
	T ToDegreees( T rad ) noexcept
	{
		return rad * (T)180.0f / (T)PI;
	}

}