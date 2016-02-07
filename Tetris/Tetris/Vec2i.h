/*------------------------------------------
* File:
* Author: xvAcid
* Copyright: (c) WSG 2011
* Date: 
*-----------------------------------------*/

#pragma once

class vec2i
{
public:
	union
	{
		struct
		{
			int x, y;
		};

		int v[2];
	};

public:
	inline vec2i()
		:x	(0),
		y	(0)
	{
	}

	inline vec2i(const vec2i &_vector)
		:x	(_vector.x),
		y	(_vector.y)
	{
	}

	inline vec2i(const int *_v)
		:x	(_v[0]),
		y	(_v[1])
	{
	}

	inline vec2i(int _value)
		:x	(_value),
		y	(_value)
	{
	}

	inline vec2i(int _x, int _y)
		: x	(_x),
		y	(_y)
	{
	}

	inline float length_square(void) const
	{
		float length = static_cast<float>((x * x) + (y * y));
		return length;
	}

	inline float length(void) const
	{
		return sqrt(length_square());
	}
	
	inline vec2i &operator = (const vec2i &_vector)
	{
		x = _vector.x;
		y = _vector.y;
		return *this;
	}

	inline vec2i operator + (const vec2i &_vector) const
	{
		vec2i new_vector;
		new_vector.x = x + _vector.x;
		new_vector.y = y + _vector.y;
		return new_vector;
	}

	inline vec2i operator - (const vec2i &_vector) const
	{
		vec2i new_vector;

		new_vector.x = x - _vector.x;
		new_vector.y = y - _vector.y;
		return new_vector;
	}

	inline vec2i operator * (const vec2i &_vector) const
	{
		vec2i new_vector;
		new_vector.x = x * _vector.x;
		new_vector.y = y * _vector.y;
		return new_vector;
	}

	inline vec2i operator / (const vec2i &_vector) const
	{
		vec2i new_vector;
		new_vector.x = x / _vector.x;
		new_vector.y = y / _vector.y;
		return new_vector;
	}

	inline vec2i operator * (float _scale) const
	{
		vec2i new_vector;
		new_vector.x = static_cast<int>(x * _scale);
		new_vector.y = static_cast<int>(y * _scale);
		return new_vector;
	}

	inline vec2i operator / (float _scale) const
	{
		vec2i new_vector;
		new_vector.x = static_cast<int>(x / _scale);
		new_vector.y = static_cast<int>(y / _scale);
		return new_vector;
	}

	inline vec2i operator - (void) const
	{
		vec2i new_vector;
		new_vector.x = -x;
		new_vector.y = -y;
		return new_vector;
	}

	inline vec2i &operator += (const vec2i &_vector)
	{
		*this = *this + _vector;
		return *this;
	}

	inline vec2i &operator -= (const vec2i &_vector)
	{
		*this = *this - _vector;
		return *this;
	}

	inline vec2i &operator *= (const vec2i &_vector)
	{
		*this = *this  *_vector;
		return *this;
	}

	inline vec2i &operator /= (const vec2i &_vector)
	{
		*this = *this / _vector;
		return *this;
	}

	inline vec2i &operator *= (float _scale)
	{
		*this = *this  *_scale;
		return *this;
	}

	inline vec2i &operator /= (float _scale)
	{
		*this = *this / _scale;
		return *this;
	}

	inline bool operator <= (const vec2i &_vector) const
	{
		if (x > _vector.x || y > _vector.y)
			return false;
		return true;
	}

	inline bool operator >= (const vec2i &_vector) const
	{
		if (x < _vector.x || y < _vector.y)
			return false;
		return true;
	}

	inline bool operator < (const vec2i &_vector) const
	{
		if (x >= _vector.x || y >= _vector.y)
			return false;
		return true;
	}

	inline bool operator > (const vec2i &_vector) const
	{
		if (x <= _vector.x || y <= _vector.y)
			return false;
		return true;
	}
};

static const vec2i vec2i_zero	= vec2i(0.0f);
static const vec2i vec2i_one	= vec2i(1.0f);
