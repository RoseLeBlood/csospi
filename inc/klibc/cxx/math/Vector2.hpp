#ifndef _STD_MATH_VECTOR2_H_
#define _STD_MATH_VECTOR2_H_

namespace std
{
	namespace math
	{
		class Vector2
		{
		public:
			union
			{
				struct
				{
					float x;
					float y;
				};
				float c[2];
			};
			Vector2() 														{}
			Vector2(float _x, float _y)		: x(_x), y(_y)				{}
			Vector2(float _f)					: x(_f), y(_f)				{}
			Vector2(const Vector2& vec)			: x(vec.x), y(vec.y)			{}
			Vector2(const float* lpvec)			: x(lpvec[0]), y(lpvec[1])	{}

			operator float* ()				{ return (float*)(c); }
			operator void* ()				{ return (void*)(c); }

			Vector2& operator =  (const Vector2& v)					{ x = v.x; y = v.y; return *this; }
			Vector2& operator += (const Vector2& v)					{ x += v.x; y += v.y; return *this; }
			Vector2& operator -= (const Vector2& v)					{ x -= v.x; y -= v.y; return *this; }
			Vector2& operator *= (const Vector2& v)					{ x *= v.x; y *= v.y; return *this; }
			Vector2& operator /= (const Vector2& v)					{ x /= v.x; y /= v.y; return *this; }

			Vector2& operator /= (const float& f)						{ x /= f; y /= f; return *this; }
			Vector2& operator *= (const float& f)						{ x *= f; y *= f; return *this; }
		};

		inline Vector2 operator + (const Vector2& a, const Vector2& b)	{ return Vector2(a.x + b.x, a.y + b.y); }
		inline Vector2 operator - (const Vector2& a, const Vector2& b)	{ return Vector2(a.x - b.x, a.y - b.y); }
		inline Vector2 operator * (const Vector2& a, const Vector2& b)	{ return Vector2(a.x * b.x, a.y * b.y); }
		inline Vector2 operator / (const Vector2& a, const Vector2& b)	{ return Vector2(a.x / b.x, a.y / b.y); }
		inline Vector2 operator + (const float& f, const Vector2& b)		{ return Vector2(f + b.x, f + b.y); }
		inline Vector2 operator - (const float& f, const Vector2& b)		{ return Vector2(f - b.x, f - b.y); }
		inline Vector2 operator * (const float& f, const Vector2& b)		{ return Vector2(f * b.x, f * b.y); }
		inline Vector2 operator / (const float& f, const Vector2& b)		{ return Vector2(f / b.x, f / b.y); }
		inline Vector2 operator - (const Vector2& a, const float& f)		{ return Vector2(a.x - f, a.y - f); }
		inline Vector2 operator / (const Vector2& a, const float& f)		{ return Vector2(a.x / f, a.y / f); }

		inline bool operator == (const Vector2& a, const Vector2& b)		{ return ((a.x == b.x) && (a.y == b.y)); }
		inline bool operator != (const Vector2& a, const Vector2& b)		{ return ((a.x != b.x) && (a.y != b.y)); }
		inline bool operator <= (const Vector2& a, const Vector2& b)		{ return ((a.x <= b.x) && (a.y <= b.y)); }
		inline bool operator >= (const Vector2& a, const Vector2& b)		{ return ((a.x >= b.x) && (a.y >= b.y)); }
		inline bool operator <  (const Vector2& a, const Vector2& b)		{ return ((a.x < b.x) && (a.y < b.x)); }
		inline bool operator >  (const Vector2& a, const Vector2& b)		{ return ((a.x > b.x) && (a.y > b.y)); }

		inline float	 Vector2Lenght(const Vector2& v)									{ return (v.x * v.x + v.y * v.y ); }
		inline float	 Vector2LenghtSq(const Vector2& v)									{ return sqrtf(v.x * v.x + v.y * v.y ); }
		inline Vector2 Vector2Normalize(const Vector2& v)									{ return v / (float)sqrtf(v.x * v.x + v.y * v.y ); }
		inline Vector2 Vector2NormalizeEx(const Vector2& v)								{ return v / (float)sqrtf((float)(v.x * v.x + v.y * v.y ) + (float)0.0001f); }

		inline float	 Vector2Dot(const Vector2& v1, const Vector2& v2)					{ return (float)(v1.x * v2.x + v1.y * v2.y);}
		inline float	 Vector2Angle(const Vector2& v1, const Vector2& v2)				{ return (float)acosf((v1.x * v2.x + v1.y * v2.y ) /
																											   (float)sqrtf((v1.x * v1.x + v1.y * v1.y ) * (v2.x * v2.x + v2.y * v2.y))); }
		inline Vector2 Vector2InterpolateCoords(const Vector2& v1, const Vector2& v2,
													const float p)								{ return v1 + p * (v2 - v1); }
		inline Vector2 Vector2InterpolateNormal(const Vector2& v1, const Vector2& v2,
													const float p)								{ return Vector2Normalize(v1 + p * (v2 - v1)); }
		inline bool		 Vector2NearEqual(const Vector2& v1, Vector2& v2,
											const Vector2& epsilon)							{ return (( abs((float)(v1.x - v2.x )) <= epsilon) && (abs((float)(v1.y - v2.y)) <= epsilon)); }
	}
}
#endif
