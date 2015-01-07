#ifndef _STD_MATH_VECTOR3_H_
#define _STD_MATH_VECTOR3_H_



namespace std
{

	namespace math
	{
		class Matrix;

		class Vector3
		{
		public:
			union
			{
				struct
				{
					float x;
					float y;
					float z;
				};
				float c[3];
			};

			Vector3(void)															: x(0), y(0), z(0)					{}
			Vector3(float _x, float _y, float _z)									: x(_x), y(_y), z(_z)				{}
			Vector3(const float f)													: x(f), y(f), z(f)					{}
			Vector3(const Vector3& vec)												: x(vec.x), y(vec.y), z(vec.z)		{}
			Vector3(const float *lpf)												: x(lpf[0]), y(lpf[1]), z(lpf[2])	{}

			operator float*	()														{ return (float*)(c); }
			operator void*  ()														{ return (void*)(c); }
			operator const float* () const											{ return (float*)c; }

			Vector3& operator =  (const Vector3& v)									{ x = v.x; y = v.y; z = v.z; return *this; }
			Vector3& operator += (const Vector3& v)									{ x += v.x; y += v.y; z += v.z; return *this; }
			Vector3& operator -= (const Vector3& v)									{ x -= v.x; y -= v.y; z -= v.z; return *this; }
			Vector3& operator *= (const Vector3& v)									{ x *= v.x; y *= v.y; z *= v.z; return *this; }
			Vector3& operator /= (const Vector3& v)									{ x /= v.x; y /= v.y; z /= v.z; return *this; }

			Vector3& operator /= (const float& f)									{ x /= f; y /= f; z /= f; return *this; }
			Vector3& operator *= (const float& f)									{ x *= f; y *= f; z *= f; return *this; }
		};

		inline Vector3 operator + (const Vector3& a, const Vector3& b)					{ return Vector3 (a.x + b.x, a.y + b.y, a.z + b.z); }
		inline Vector3 operator - (const Vector3& a, const Vector3& b)					{ return Vector3 (a.x - b.x, a.y - b.y, a.z - b.z); }
		inline Vector3 operator - (const Vector3& a)										{ return Vector3 (-a.x, -a.y, -a.z); }
		inline Vector3 operator * (const Vector3& a,const Vector3& b)						{ return Vector3 (a.x * b.x, a.y * b.y, a.z * b.z); }
		inline Vector3 operator * (const Vector3& a, const float& b)						{ return Vector3 (a.x * b, a.y * b, a.z * b); }
		inline Vector3 operator * (const float& a,const Vector3& b)						{ return Vector3 (a * b.x, a * b.y, a * b.z); }
		inline Vector3 operator / (const Vector3& a,const Vector3& b)						{ return Vector3 (a.x / b.x, a.y / b.y, a.z / b.z); }
		inline Vector3 operator / (const float& a,const Vector3& b)						{ return Vector3 (a / b.x, a / b.y, a / b.z); }
		inline Vector3 operator / (const Vector3& a,const float& b)						{ return Vector3 (a.x / b, a.y / b, a.z / b); }

		inline bool operator == (const Vector3& a, const Vector3& b)						{ return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z)); }
		inline bool operator != (const Vector3& a, const Vector3& b)						{ return ((a.x != b.x) && (a.y != b.y) && (a.z != b.z)); }
		inline bool operator <= (const Vector3& a, const Vector3& b)						{ return ((a.x <= b.x) && (a.y <= b.y) && (a.z <= b.z)); }
		inline bool operator >= (const Vector3& a, const Vector3& b)						{ return ((a.x >= b.x) && (a.y >= b.y) && (a.z >= b.z)); }
		inline bool operator < (const Vector3& a, const Vector3& b)							{ return ((a.x < b.x) && (a.y < b.y) && (a.z < b.z)); }
		inline bool operator > (const Vector3& a, const Vector3& b)							{ return ((a.x > b.x) && (a.y > b.y) && (a.z > b.z)); }

		inline float	 Vector3LenghtSq(const Vector3& v)									{ return (v.x * v.x + v.y * v.y + v.z * v.z); }
		inline float	 Vector3Lenght(const Vector3& v)									{ return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
		inline Vector3 	 Vector3Normalize(const Vector3& v)									{ return v / sqrtf(float(v.x * v.x + v.y * v.y + v.z * v.z)); }
		inline Vector3   Vector3NormalizeEx(const Vector3& v)								{ return v / (sqrtf(float(v.x * v.x + v.y * v.y + v.z * v.z)) + 0.0001f); }
		inline Vector3   Vector3Cross(const Vector3& v1, Vector3& v2)						{ return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
																											   v1.x * v2.y - v1.y * v2.x); }
		inline float	 Vector3Dot(const Vector3& v1, const Vector3& v2)					{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}
		inline float	 Vector3Angle(const Vector3& v1, const Vector3& v2)				{ return acosf(float((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)) /
																											   sqrtf(float((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z)) * float((v2.x * v2.x + v2.y * v2.y + v2.z * v2.z)))); }
		inline Vector3   Vector3InterpolateCoords(const Vector3& v1, const Vector3& v2,
													const float p)								{ return v1 + p * (v2 - v1); }
		inline Vector3   Vector3InterpolateNormal(const Vector3& v1, const Vector3& v2,
													const float p)								{ return Vector3Normalize(v1 + p * (v2 - v1)); }

	}
}
#endif