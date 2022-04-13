#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include<iostream>
#include <cmath>
#include<cassert>
#include<vector>
template<typename T, size_t LEN> struct Vector {};
template<typename T> struct Vector<T, 2>
{
	union
	{
		struct { T u, v; };
		struct { T x, y; };
		T raw[2];
	};
	Vector() : x(0), y(0) {}
	Vector(T x0, T y0) : x(x0), y(y0) {}
	Vector(const Vector<T, 2>& v)
	{
		x = v.x;
		y = v.y;
	}
	void operator=(const Vector<T,2>& v)
	{
		x = v.x;
		y = v.y;
	}
	inline Vector<T, 2> cwiseProduct(const Vector<T, 2>& v)
	{	//Vector * Vector
		return Vector<T, 2>(x * v.x, y * v.y);
	}

	T& operator[](const size_t i) { assert(i < 2); return i <= 0 ? x : y; }
	const T& operator[](const size_t i) const { assert(i < 2); return i <= 0 ? x : y; }

	template <typename > friend std::ostream& operator<<(std::ostream& s, Vector<T, 2>& v);
};
template<typename T> struct Vector<T, 3>
{
	union
	{
		struct { T x, y, z; };
		struct { T ivert, iuv, inorm; };
		T raw[3];
	};

	Vector() : x(0), y(0), z(0) {};
	Vector(T x0, T y0, T z0) : x(x0), y(y0), z(z0) {}
	Vector(const Vector<T, 3>& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	void operator=(const Vector<T, 3>& v) { 
		x = v.x;
		y = v.y;
		z = v.z;
	}
	T& operator[](const size_t i) { assert(i < 3); return i <= 0 ? x : (1 == i ? y : z); }
	const T& operator[](const size_t i) const { assert(i < 3); return i <= 0 ? x : (1 == i ? y : z); }

	inline Vector<T, 3> cwiseProduct(const Vector<T, 3>& v) const
	{	//Vector * Vector
		return Vector<T, 3>(x * v.x, y * v.y, z * v.z);
	}
	inline Vector<T, 3> cross(const Vector<T, 3>& v) const { return Vector<T, 3>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	float norm() const { return std::sqrt(x * x + y * y + z * z); }
	Vector<T, 3>& normalize(T l = 1) { *this = (*this) * (l / norm()); return *this; }

	template <typename > friend std::ostream& operator<<(std::ostream& s, Vector<T, 3>& v);
};
template<typename T> struct Vector<T, 4>
{
	T x, y, z, w;
	Vector() : x(0), y(0), z(0) {};
	Vector(T x0, T y0, T z0, T w0) : x(x0), y(y0), z(z0), w(w0) {}
	Vector(const Vector<T, 4>& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	void operator=(const Vector<T, 3>& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	T& operator[](const size_t i) { assert(i < 4); return i <= 0 ? x : (1 == i ? y : (2==i ? z : w)); }
	const T& operator[](const size_t i) const { assert(i < 4); return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w)); }

	inline Vector<T, 4> cwiseProduct(const Vector<T, 4>& v) const
	{	//Vector * Vector
		return Vector<T, 4>(x * v.x, y * v.y, z * v.z, w*v.w);
	}

	float norm() const { return std::sqrt(x * x + y * y + z * z + w * w); }
	Vector<T, 4>& normalize(T l = 1) { *this = (*this) * (l / norm()); return *this; }
	template <typename > friend std::ostream& operator<<(std::ostream& s, Vector<T, 4>& v);
};

template<typename T, size_t LEN>
inline Vector<T, LEN> operator+(Vector<T, LEN> res, const Vector<T, LEN>& v)
{	//
	for (size_t i = LEN; i--; res[i] += v[i]);
	return res;
};
template<typename T, size_t LEN>
inline Vector<T, LEN> operator-(Vector<T, LEN> res, const Vector<T, LEN>& v)
{
	for (size_t i = LEN; i--; res[i] -= v[i]);
	return res;
};
template<typename T, size_t LEN>
inline Vector<T, LEN> operator*(Vector<T, LEN> res, T f)
{   //broadcast f
	for (size_t i = LEN; i--; res[i] *= f);
	return res;
};
template<typename T, size_t LEN>
inline Vector<T, LEN> operator*(T f, Vector<T, LEN> res)
{   //broadcast f
	for (size_t i = LEN; i--; res[i] *= f);
	return res;
};
template<typename T, size_t LEN>
inline T operator*(const Vector<T, LEN>& res, const Vector<T, LEN>& v)
{	// Vector * Vector and + return T;
	T t = 0;
	for (size_t i = LEN; i--; t += res[i] * v[i]);
	return t;
};
template<typename T, size_t LEN>
inline Vector<T, LEN> operator/(Vector<T, LEN> res, T f)
{   //broadcast f
	for (size_t i = LEN; i--; res[i] /= f);
	return res;
};
template<typename T>
std::ostream& operator<<(std::ostream& s, Vector<T, 2>& v)
{
	s << "(" << v.x << ", " << v.y << ")\n";
	return s;
}
template<typename T>
std::ostream& operator<<(std::ostream& s, Vector<T, 3>& v)
{
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}
template<typename T>
std::ostream& operator<<(std::ostream& s, Vector<T, 4>& v)
{
	s << "(" << v.x << ", " << v.y << ", " << v.z << ", " <<v.w << ")\n";
	return s;
}
typedef Vector<int, 2> Vector2i;
typedef Vector<float, 2> Vector2f;
typedef Vector<int, 3> Vector3i;
typedef Vector<float, 3> Vector3f;
typedef Vector<int, 4> Vector4i;
typedef Vector<float, 4> Vector4f;
//Matrix-------------------------------------------------------

template<typename T, size_t NROW, size_t NCOL> struct Matrix 
{
	Matrix();
	Matrix(T);
	Matrix(const Matrix<T, NROW, NCOL>& );
	virtual ~Matrix();
	T& operator()(const size_t i, const size_t j) { assert(i < NROW && j<NCOL); return m[i][j]; }
	const T& operator()(const size_t i, const size_t j) const { assert(i < NROW && j < NCOL); return m[i][j]; }
	void clear();
	void identity();
	void transpose();
	void show();
	Matrix<T, NROW, NCOL>& operator=(const Matrix<T, NROW, NCOL>&);
	Matrix<T, NROW, NCOL>& operator+=(const Matrix<T, NROW, NCOL>&);
	Matrix<T, NROW, NCOL>& operator-=(const Matrix<T, NROW, NCOL>&);
	Matrix<T, NROW, NCOL>& operator*=(const Matrix<T, NROW, NCOL>&);
	Matrix<T, NROW, NCOL>& operator*=(T);
	Matrix<T, NROW, NCOL> operator*(const Matrix<T, NROW, NCOL>&) const; //*�Ĳ���Ҫ���ؿ������󣬲�����ԭ�������޸�����û��&
	Matrix<T, NROW, NCOL> operator*(T) const;
	Vector4f operator*(Vector4f& v) const;
	Matrix<T, NROW, NCOL> operator+(const Matrix<T, NROW, NCOL>&) const;
	Matrix<T, NROW, NCOL> operator-(const Matrix<T, NROW, NCOL>&) const;
	template <typename > friend void operator<<(Matrix<T, NROW, NCOL>&, std::vector<T>);
	T ** m = nullptr;
};

template<typename T, size_t NROW, size_t NCOL> Matrix<T, NROW, NCOL>::Matrix()
{
	m = new T * [NROW];
	for (int i = 0; i < NROW; i++)
	{
		m[i] = new T[NCOL];
	}
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			m[i][j] = 0;
		}
	}
}

template<typename T, size_t NROW, size_t NCOL> Matrix<T, NROW, NCOL>::Matrix(T t)
{
	m = new T * [NROW];
	for (int i = 0; i < NROW; i++)
	{
		m[i] = new T[NCOL];
	}
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			m[i][j] = t;
		}
	}
}

template<typename T, size_t NROW, size_t NCOL> Matrix<T, NROW, NCOL>::Matrix(const Matrix<T, NROW, NCOL>& mcpy)
{
	m = new T * [NROW];
	for (int i = 0; i < NROW; i++)
	{
		m[i] = new T[NCOL];
	}
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			m[i][j] = mcpy.m[i][j];
		}
	}
}

template<typename T, size_t NROW, size_t NCOL> Matrix<T, NROW, NCOL>::~Matrix()
{
	for (int i = 0; i < NROW; i++)
	{
		delete[] m[i];
	}
	delete[] m;
	m = nullptr;
}

template<typename T, size_t NROW, size_t NCOL>
void Matrix<T, NROW, NCOL>::clear()
{
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			m[i][j] = 0;
		}
	}
}

template<typename T, size_t NROW, size_t NCOL>
void Matrix<T, NROW, NCOL>::transpose()
{
	for (int i = 0; i < NROW; i++)
	{
		for (int j = i + 1; j < NCOL; j++)
		{
			std::swap(m[i][j], m[j][i]);
		}
	}
};

template<typename T, size_t NROW, size_t NCOL>
void Matrix<T, NROW, NCOL>::identity()
{
	for (int i = 0, j = 0; i < NROW && j < NCOL; i++, j++)
	{
		m[i][j] = 1;
	}
};

template<typename T, size_t NROW, size_t NCOL>
void Matrix<T, NROW, NCOL>::show()
{
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			std::cout << m[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL>& Matrix<T, NROW, NCOL>::operator=(const Matrix<T, NROW, NCOL>& mcpy)
{
	if (!m)
	{
		m = new T * [NROW];
		for (int i = 0; i < NROW; i++)
		{
			m[i] = new T[NCOL];
		}
	}
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			m[i][j] = mcpy.m[i][j];
		}
	}
	return *this;
};
template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL>& Matrix<T, NROW, NCOL>::operator+=(const Matrix<T, NROW, NCOL>& mcpy)
{
	assert(m);
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			m[i][j] += mcpy.m[i][j];
		}
	}
	return *this;
};

template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL>& Matrix<T, NROW, NCOL>::operator-=(const Matrix<T, NROW, NCOL>& mcpy)
{
	assert(m);
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			m[i][j] -= mcpy.m[i][j];
		}
	}
	return *this;
};

template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL>& Matrix<T, NROW, NCOL>::operator*=(const Matrix<T, NROW, NCOL>& mcpy)
{
	assert(m);
	Matrix tmp;
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			for (int k = 0; k < NCOL; k++)
			{
				tmp.m[i][j] += m[i][k] * mcpy.m[k][j];
			}
		}
	}
	*this = tmp;
	return *this;
};

template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL>& Matrix<T, NROW, NCOL>::operator*=(T f)
{
	assert(m);
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			m[i][j] *= f;
		}
	}
	return *this;
};

template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL> Matrix<T, NROW, NCOL>::operator*(const Matrix<T, NROW, NCOL>& mcpy) const
{
	assert(m);
	Matrix<T, NROW, NCOL> tmp;
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			for (int k = 0; k < NCOL; k++)
			{
				tmp.m[i][j] += m[i][k] * mcpy.m[k][j];
			}
		}
	}
	return tmp;
};

template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL> Matrix<T, NROW, NCOL>::operator*(T f) const
{
	Matrix<T, NROW, NCOL> tmp;
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			tmp.m[i][j] *= f;
		}
	}
	return tmp;
};
template<typename T, size_t NROW, size_t NCOL>
Vector4f Matrix<T, NROW, NCOL>::operator*(Vector4f& v) const
{
	assert(NROW == 4 && NCOL == 4);
	Vector4f res(0, 0, 0, 0);
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			res[i] += m[i][j] * v[j];
		}
	}
	return res;
};

template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL> Matrix<T, NROW, NCOL>::operator+(const Matrix<T, NROW, NCOL>& mcpy) const
{
	assert(m);
	Matrix<T, NROW, NCOL> tmp;
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			tmp.m[i][j] = m[i][j] + mcpy.m[i][j];
		}
	}
	return tmp;
};

template<typename T, size_t NROW, size_t NCOL>
Matrix<T, NROW, NCOL> Matrix<T, NROW, NCOL>::operator-(const Matrix<T, NROW, NCOL>& mcpy) const
{
	assert(m);
	Matrix<T, NROW, NCOL> tmp;
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			tmp.m[i][j] = m[i][j] - mcpy.m[i][j];
		}
	}
	return tmp;
};

template<typename T, size_t NROW, size_t NCOL>
void operator<<(Matrix<T, NROW, NCOL>& res, std::vector<T> v)
{
	assert(v.size() == NROW * NCOL);
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			res.m[i][j] = v[i * NCOL + j];
		}
	}
};


typedef Matrix<int, 2, 2> Matrix2i;
typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<int, 4, 4> Matrix4i;
typedef Matrix<float, 4, 4> Matrix4f;

#endif //__GEOMETRY_H__
