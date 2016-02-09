/*------------------------------------------
* File:
* Author: xvAcid
* Copyright: (c) WSG 2011
* Date: 
*-----------------------------------------*/

#pragma once

#include <math.h>

class vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};

		float v[2];
	};

public:
	inline vec2f()
		:x	(0.0f),
		y	(0.0f)
	{
	}

	inline vec2f(const vec2f &_vector)
		:x	(_vector.x),
		y	(_vector.y)
	{
	}

	inline vec2f(const float *_v)
		:x	(_v[0]),
		y	(_v[1])
	{
	}

	inline vec2f(float _value)
		:x	(_value),
		y	(_value)
	{
	}

	inline vec2f(float _x, float _y)
		: x	(_x),
		y	(_y)
	{
	}
	
	inline float length()
	{
		float value = sqrtf(x * x + y * y);
		return value;
	}
	
	inline void normalize()
	{
		float scale = 1.0f / length();
		x	*= scale;
		y	*= scale;
	}

	inline vec2f &operator = (const vec2f &_vector)
	{
		x = _vector.x;
		y = _vector.y;
		return *this;
	}

	inline vec2f operator + (const vec2f &_vector) const
	{
		vec2f new_vector;
		new_vector.x = x + _vector.x;
		new_vector.y = y + _vector.y;
		return new_vector;
	}
	
	inline vec2f operator - (const vec2f &_vector) const
	{
		vec2f new_vector;

		new_vector.x = x - _vector.x;
		new_vector.y = y - _vector.y;
		return new_vector;
	}

	inline vec2f operator * (const vec2f &_vector) const
	{
		vec2f new_vector;
		new_vector.x = x * _vector.x;
		new_vector.y = y * _vector.y;
		return new_vector;
	}
	
	inline vec2f operator / (const vec2f &_vector) const
	{
		vec2f new_vector;
		new_vector.x = x / _vector.x;
		new_vector.y = y / _vector.y;
		return new_vector;
	}

	inline friend vec2f operator * (float _scale, const vec2f &_vector)
	{
		vec2f new_vector;
		new_vector.x = _vector.x * _scale;
		new_vector.y = _vector.y * _scale;
		return new_vector;
	}

	inline vec2f operator * (float _scale) const
	{
		vec2f new_vector;
		new_vector.x = x * _scale;
		new_vector.y = y * _scale;
		return new_vector;
	}

	inline vec2f operator / (float _scale) const
	{
		vec2f new_vector;
		new_vector.x = x / _scale;
		new_vector.y = y / _scale;
		return new_vector;
	}

	inline vec2f operator - (void) const
	{
		vec2f new_vector;
		new_vector.x = -x;
		new_vector.y = -y;
		return new_vector;
	}

	inline vec2f &operator += (const vec2f &_vector)
	{
		*this = *this + _vector;
		return *this;
	}

	inline vec2f &operator -= (const vec2f &_vector)
	{
		*this = *this - _vector;
		return *this;
	}
	
	inline vec2f &operator *= (const vec2f &_vector)
	{
		*this = *this  *_vector;
		return *this;
	}

	inline vec2f &operator /= (const vec2f &_vector)
	{
		*this = *this / _vector;
		return *this;
	}
	
	inline vec2f &operator *= (float _scale)
	{
		*this = *this  *_scale;
		return *this;
	}

	inline vec2f &operator /= (float _scale)
	{
		*this = *this / _scale;
		return *this;
	}

	inline bool operator <= (const vec2f &_vector) const
	{
		if (x > _vector.x || y > _vector.y)
			return false;
		return true;
	}

	inline bool operator >= (const vec2f &_vector) const
	{
		if (x < _vector.x || y < _vector.y)
			return false;
		return true;
	}

	inline bool operator < (const vec2f &_vector) const
	{
		if (x >= _vector.x || y >= _vector.y)
			return false;
		return true;
	}

	inline bool operator > (const vec2f &_vector) const
	{
		if (x <= _vector.x || y <= _vector.y)
			return false;
		return true;
	}
};

static const vec2f vec2f_zero	= vec2f(0.0f);
static const vec2f vec2f_one	= vec2f(1.0f);