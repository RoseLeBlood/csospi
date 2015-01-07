#ifndef _STD_MATH_VECTOR3_H_
#define _STD_MATH_VECTOR3_H_

namespace std
{
	namespace math
	{
		class Vector4
		{
		public:
			union
			{
				struct
				{
					float x;
					float y;
					float z;
					float w;
				};
				float c[4];
			};
			Vector4(void)																		: x(0), y(0), z(0), w(0)							{}
			Vector4(const float _x, const float _y, const float _z, const float _w)	: x(_x), y(_y), z(_z), w(_w)					{}
			Vector4(const float f)															: x(f), y(f), z(f), w(f)							{}
			Vector4(const Vector4& vec)														: x(vec.x), y(vec.y), z(vec.z), w(vec.w)			{}
			Vector4(const float *lpf)														: x(lpf[0]), y(lpf[1]), z(lpf[2]), w(lpf[3])		{}

			operator float*	()														{ return (float*)(c); }
			operator void*  ()														{ return (void*)(c); }
			operator const float* () const											{ return (float*)c; }

			Vector4& operator =  (const Vector4& v)								{ x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
			Vector4& operator += (const Vector4& v)								{ x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
			Vector4& operator -= (const Vector4& v)								{ x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
			Vector4& operator *= (const Vector4& v)								{ x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
			Vector4& operator /= (const Vector4& v)								{ x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

			Vector4& operator /= (const float& f)								{ x /= f; y /= f; z /= f; w /= f; return *this; }
			Vector4& operator *= (const float& f)								{ x *= f; y *= f; z *= f; w *= f; return *this; }
		};
		inline Vector4 operator + (const Vector4& a, const Vector4& b)					{ return Vector4 (a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
		inline Vector4 operator - (const Vector4& a, const Vector4& b)					{ return Vector4 (a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.z); }
		inline Vector4 operator - (const Vector4& v)										{ return Vector4 (-v.x, -v.y, -v.x, -v.w); }
		inline Vector4 operator * (const Vector4& a,const Vector4& b)						{ return Vector4 (a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
		inline Vector4 operator * (const Vector4& a, const float& b)						{ return Vector4 (a.x * b, a.y * b, a.z * b, a.w * b); }
		inline Vector4 operator * (const float& a,const Vector4& b)						{ return Vector4 (a * b.x, a * b.y, a * b.z, a * b.w); }
		inline Vector4 operator / (const Vector4& a,const Vector4& b)						{ return Vector4 (a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
		inline Vector4 operator / (const float& a,const Vector4& b)						{ return Vector4 (a / b.x, a / b.y, a / b.z, a / b.w); }
		inline Vector4 operator / (const Vector4& a,const float& b)						{ return Vector4 (a.x / b, a.y / b, a.z / b, a.w / b); }

		inline bool operator == (const Vector4& a, const Vector4& b)						{ return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w)); }
		inline bool operator != (const Vector4& a, const Vector4& b)						{ return ((a.x != b.x) && (a.y != b.y) && (a.z != b.z) && (a.w != b.w)); }
		inline bool operator <= (const Vector4& a, const Vector4& b)						{ return ((a.x <= b.x) && (a.y <= b.y) && (a.z <= b.z) && (a.w <= b.w)); }
		inline bool operator >= (const Vector4& a, const Vector4& b)						{ return ((a.x >= b.x) && (a.y >= b.y) && (a.z >= b.z) && (a.w >= b.w)); }
		inline bool operator < (const Vector4& a, const Vector4& b)							{ return ((a.x < b.x) && (a.y < b.y) && (a.z < b.z) && (a.w < b.w)); }
		inline bool operator > (const Vector4& a, const Vector4& b)							{ return ((a.x > b.x) && (a.y > b.y) && (a.z > b.z) && (a.w > b.w)); }

		inline float	 Vector4LenghtSq(const Vector4& v)									{ return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
		inline float	 Vector4Lenght(const Vector4& v)									{ return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
		inline Vector4 Vector4Normalize(const Vector4& v)									{ return v / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
		inline Vector4 Vector4NormalizeEx(const Vector4& v)								{ return v / (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w) + 0.0001f); }

		inline float	 Vector4Dot(const Vector4& v1, const Vector4& v2)					{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;}
		inline float	 Vector4Angle(const Vector4& v1, const Vector4& v2)				{ return (float)acosf((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w) /
																											   (float)sqrtf((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z + v1.w * v1.w) * (v2.x * v2.x + v2.y * v2.y + v2.z * v2.z + v2.w * v2.w))); }
		inline Vector4 Vector4InterpolateCoords(const Vector4& v1, const Vector4& v2,
													const float p)								{ return v1 + p * (v2 - v1); }
		inline Vector4 Vector4InterpolateNormal(const Vector4& v1, const Vector4& v2,
													const float p)								{ return Vector4Normalize(v1 + p * (v2 - v1)); }
			
	}
}
#endif
