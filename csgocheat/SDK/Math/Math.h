#pragma once
#include "../../stdafx.h"

#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square( x ) ( x * x )
#define  FORCEINLINE			__forceinline

inline float isqrt( float _Xx )
{
	return ( sqrtf( _Xx ) );
}

typedef float vec_t;

struct matrix3x4_t
{
	matrix3x4_t()
	{
	}

	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23 )
	{
		m_flMatVal[ 0 ][ 0 ] = m00;
		m_flMatVal[ 0 ][ 1 ] = m01;
		m_flMatVal[ 0 ][ 2 ] = m02;
		m_flMatVal[ 0 ][ 3 ] = m03;
		m_flMatVal[ 1 ][ 0 ] = m10;
		m_flMatVal[ 1 ][ 1 ] = m11;
		m_flMatVal[ 1 ][ 2 ] = m12;
		m_flMatVal[ 1 ][ 3 ] = m13;
		m_flMatVal[ 2 ][ 0 ] = m20;
		m_flMatVal[ 2 ][ 1 ] = m21;
		m_flMatVal[ 2 ][ 2 ] = m22;
		m_flMatVal[ 2 ][ 3 ] = m23;
	}

	void Init( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin )
	{
		m_flMatVal[ 0 ][ 0 ] = xAxis.x;
		m_flMatVal[ 0 ][ 1 ] = yAxis.x;
		m_flMatVal[ 0 ][ 2 ] = zAxis.x;
		m_flMatVal[ 0 ][ 3 ] = vecOrigin.x;
		m_flMatVal[ 1 ][ 0 ] = xAxis.y;
		m_flMatVal[ 1 ][ 1 ] = yAxis.y;
		m_flMatVal[ 1 ][ 2 ] = zAxis.y;
		m_flMatVal[ 1 ][ 3 ] = vecOrigin.y;
		m_flMatVal[ 2 ][ 0 ] = xAxis.z;
		m_flMatVal[ 2 ][ 1 ] = yAxis.z;
		m_flMatVal[ 2 ][ 2 ] = zAxis.z;
		m_flMatVal[ 2 ][ 3 ] = vecOrigin.z;
	}

	matrix3x4_t( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin )
	{
		Init( xAxis, yAxis, zAxis, vecOrigin );
	}

	float* operator[]( int i )
	{
		return m_flMatVal[ i ];
	}

	const float* operator[]( int i ) const
	{
		return m_flMatVal[ i ];
	}

	float* Base()
	{
		return &m_flMatVal[ 0 ][ 0 ];
	}

	const float* Base() const
	{
		return &m_flMatVal[ 0 ][ 0 ];
	}

	float m_flMatVal[3][4];
};

class CMath
{
public:
	static CMath* Singleton( void );

	bool WorldToScreen( Vector& vecOrigin, Vector& vecScreen );

	VOID sinCos( float radians, PFLOAT sine, PFLOAT cosine );

	void angleVectors( const Vector& angles, Vector& forward );

	float RandomFloat(float min, float max);

	Vector CalcAngle(Vector src, Vector dst);

	void VectorAngles(const Vector& forward, Vector &angles);

	float sseSqrt( float x );

	VOID vectorAngles( float* forward, float* angles );

	void vectorAnglesVec( Vector forward, Vector& angles );

	void VectorAngles3D( Vector& vecForward, Vector& vecAngles );

	float deg2rad( float deg );

	float DotProduct( const Vector& a, const Vector& b );

	void VectorTransform( const Vector in1, matrix3x4_t in2, Vector& out );

	void AngleMatrix( Vector& angles, matrix3x4_t& matrix );

	void VectorRotate( Vector& in1, Vector& in2, Vector& out );

	static Vector ExtrapolateTick(Vector p0, Vector v0);

	void Normalize( Vector& vIn, Vector& vOut );

	void Normalize2(Vector& v);

	void Normalize3(float& angle);

	void Normalize4(int& angle);

	void ClampAngles(Vector& v);

	inline float ClampYaw(float yaw);

	Vector RotatePoint( Vector p, Vector c, float ang );

	void VectorTransform2( const Vector in1, float in2[3][4], Vector& out );

	void VectorITransform( const float* in1, const matrix3x4_t& in2, float* out )
	{
		Assert(s_bMathlibInitialized);
		float in1t[3];

		in1t[ 0 ] = in1[ 0 ] - in2[ 0 ][ 3 ];
		in1t[ 1 ] = in1[ 1 ] - in2[ 1 ][ 3 ];
		in1t[ 2 ] = in1[ 2 ] - in2[ 2 ][ 3 ];

		out[ 0 ] = in1t[ 0 ] * in2[ 0 ][ 0 ] + in1t[ 1 ] * in2[ 1 ][ 0 ] + in1t[ 2 ] * in2[ 2 ][ 0 ];
		out[ 1 ] = in1t[ 0 ] * in2[ 0 ][ 1 ] + in1t[ 1 ] * in2[ 1 ][ 1 ] + in1t[ 2 ] * in2[ 2 ][ 1 ];
		out[ 2 ] = in1t[ 0 ] * in2[ 0 ][ 2 ] + in1t[ 1 ] * in2[ 1 ][ 2 ] + in1t[ 2 ] * in2[ 2 ][ 2 ];
	}

	void AngleNormalise( Vector& angle )
	{
		while( angle.y <= -180 )
			angle.y += 360;
		while( angle.y > 180 )
			angle.y -= 360;
		while( angle.x <= -180 )
			angle.x += 360;
		while( angle.x > 180 )
			angle.x -= 360;

		if( angle.x > 89.0 )
			angle.x = 89;
		if( angle.x < -89.0 )
			angle.x = -89;
		if( angle.y < -180 )
			angle.y = -179.999;
		if( angle.y > 180 )
			angle.y = 179.999;

		angle.z = 0;
	}

	//lazy, sorry! for dme chams.
	void MatrixGetColumn(const matrix3x4_t& in, int column, Vector& out)
	{
		out.x = in[0][column];
		out.y = in[1][column];
		out.z = in[2][column];
	}

	void MatrixSetColumn(const Vector& in, int column, matrix3x4_t& out)
	{
		out[0][column] = in.x;
		out[1][column] = in.y;
		out[2][column] = in.z;
	}

	void MatrixCopy(const matrix3x4_t& in, matrix3x4_t& out)
	{
		memcpy(out.Base(), in.Base(), sizeof(float) * 3 * 4);
	}

	void ConcatTransforms(const matrix3x4_t& in1, const matrix3x4_t& in2, matrix3x4_t& out)
	{
		if (&in1 == &out)
		{
			matrix3x4_t in1b;
			MatrixCopy(in1, in1b);
			ConcatTransforms(in1b, in2, out);
			return;
		}
		if (&in2 == &out)
		{
			matrix3x4_t in2b;
			MatrixCopy(in2, in2b);
			ConcatTransforms(in1, in2b, out);
			return;
		}
		out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
			in1[0][2] * in2[2][0];
		out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
			in1[0][2] * in2[2][1];
		out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
			in1[0][2] * in2[2][2];
		out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
			in1[0][2] * in2[2][3] + in1[0][3];
		out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
			in1[1][2] * in2[2][0];
		out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
			in1[1][2] * in2[2][1];
		out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
			in1[1][2] * in2[2][2];
		out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
			in1[1][2] * in2[2][3] + in1[1][3];
		out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
			in1[2][2] * in2[2][0];
		out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
			in1[2][2] * in2[2][1];
		out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
			in1[2][2] * in2[2][2];
		out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
			in1[2][2] * in2[2][3] + in1[2][3];
	}

	void MatrixMultiply(const matrix3x4_t& in1, const matrix3x4_t& in2, matrix3x4_t& out)
	{
		ConcatTransforms(in1, in2, out);
	}

	void MatrixAngles(const matrix3x4_t& matrix, Vector& angles)
	{
		float forward[3];
		float left[3];
		float up[3];

		//
		// Extract the basis vectors from the matrix. Since we only need the Z
		// component of the up vector, we don't get X and Y.
		//
		forward[0] = matrix[0][0];
		forward[1] = matrix[1][0];
		forward[2] = matrix[2][0];
		left[0] = matrix[0][1];
		left[1] = matrix[1][1];
		left[2] = matrix[2][1];
		up[2] = matrix[2][2];

		float xyDist = sqrtf(forward[0] * forward[0] + forward[1] * forward[1]);

		// enough here to get angles?
		if (xyDist > 0.001f)
		{
			// (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the X axis
			angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));

			// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
			angles[0] = RAD2DEG(atan2f(-forward[2], xyDist));

			// (roll)	z = ATAN( left.z, up.z );
			angles[2] = RAD2DEG(atan2f(left[2], up[2]));
		}
		else // forward is mostly Z, gimbal lock-
		{
			// (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
			angles[1] = RAD2DEG(atan2f(-left[0], left[1]));

			// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
			angles[0] = RAD2DEG(atan2f(-forward[2], xyDist));

			// Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
			angles[2] = 0;
		}
	}

	void AngleMatrix(const Vector& angles, matrix3x4_t& matrix)
	{
		auto SinCos = [](float radians, float* sine, float* cosine)
		{
			*sine = sin(radians);
			*cosine = cos(radians);
		};

		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);
		SinCos(DEG2RAD(angles[2]), &sr, &cr);

		// matrix = (YAW * PITCH) * ROLL
		matrix[0][0] = cp * cy;
		matrix[1][0] = cp * sy;
		matrix[2][0] = -sp;

		float crcy = cr * cy;
		float crsy = cr * sy;
		float srcy = sr * cy;
		float srsy = sr * sy;
		matrix[0][1] = sp * srcy - crsy;
		matrix[1][1] = sp * srsy + crcy;
		matrix[2][1] = sr * cp;

		matrix[0][2] = sp * crcy + srsy;
		matrix[1][2] = sp * crsy - srcy;
		matrix[2][2] = cr * cp;

		matrix[0][3] = 0.0f;
		matrix[1][3] = 0.0f;
		matrix[2][3] = 0.0f;
	}

	void AngleMatrix(const Vector& angles, const Vector& origin, matrix3x4_t& matrix)
	{
		AngleMatrix(angles, matrix);
		MatrixSetColumn(origin, 3, matrix);
	}
};

extern CMath g_Math;
