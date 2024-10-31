/*
 * MIT License
 * Copyright (c) 2024 BlockyDeer<blockydeer@outlook.com>
 * Licensed under the MIT License. See LICENSE file in the project root for full
 * license information.
 */
#pragma once

#include <cmath>
#include <string>

#include "result.hpp"

namespace AhogeUtil {
template <typename T>
class Vector2 {
public:
	T x;
	T y;
	Vector2() {
		x = 0;
		y = 0;
	}
	Vector2(T x, T y) {
		this->x = x;
		this->y = y;
	}
	~Vector2() = default;

	bool operator==(Vector2<T> const &other) const {
		return ((*this) == other);
	}

	bool operator!=(Vector2<T> const &other) const {
		return !((*this) == other);
	}

	bool is_parallel(Vector2<T> const &other) const {
		if (other.x == 0 && other.y == 0) {
			return true;
		}
		return x / other.x == y / other.y;
	}

	Vector2<T> const add(Vector2<T> const &other) const {
		return Vector2<T>(x + other.x, y + other.y);
	}

	Vector2<T> const operator+(Vector2<T> const &other) const {
		return add(other);
	}

	Vector2<T> const sub(Vector2 const &other) const {
		return Vector2<T>(x - other.x, y - other.y);
	}

	Vector2<T> const operator-(Vector2 const &other) const {
		return sub(other);
	}

	Vector2<T> const opposite() const { return Vector2<T>(-(x), -(y)); }

	Vector2<T> const operator-() const { return opposite(); }

	Vector2<T> const multiply(double rate) const {
		return Vector2<T>(x * rate, y * rate);
	}

	Vector2<T> const operator*(double rate) const { return multiply(rate); }

	double dot(Vector2<T> const &other) const {
		return x * other.x + y * other.y;
	}

	double operator*(Vector2<T> const &other) const {
		return x * other.x + y * other.y;
	}

	Vector2<T> cross(Vector2<T> const &other) const {
		return Vector2<T>(x * other.y, y * other.x);
	}

	double mod() const { return std::sqrt((double)x * x + y * y); }

	void operator+=(Vector2 const &other) { *this = *this + other; }

	void operator-=(Vector2 const &other) { *this = *this - other; }

	Vector2<T> const normalize() const {
		double mod_val = this->mod();
		if (mod_val != 0) {
			return Vector2<T>(x / (T)mod_val, y / (T)mod_val);
		} else {
			return Vector2<T>(0, 0);
		}
	};
};

template <typename T>
class Vector3 {
public:
	T x;
	T y;
	T z;
	Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}
	Vector3(T x, T y) {
		this->x = x;
		this->y = y;
		this->z = 0;
	}
	Vector3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(Vector2<T> const &vec2, T z = 0) {
		x = vec2.x;
		y = vec2.y;
		this->z = z;
	}
	~Vector3() = default;

	bool operator==(Vector3<T> const &other) const {
		return ((*this) == other);
	}

	bool operator!=(Vector3<T> const &other) const {
		return !((*this) == other);
	}

	bool is_parallel(Vector3<T> const &other) {
		if (other.x == 0 && other.y == 0 && other.z == 0) {
			return true;
		}
		return (x / other.x == y / other.y) &&
		       (z / other.z == y / other.y);
	}

	Vector3<T> const add(T v) const {
		return Vector3<T>(x + v, y + v, z + v);
	}

	Vector3<T> const add(Vector3<T> const &other) const {
		return Vector3<T>(x + other.x, y + other.y, z + other.z);
	}

	Vector3<T> const add(Vector2<T> const &vec) const {
		return add(Vector3<T>(vec));
	}

	Vector3<T> const operator+(Vector3<T> const &other) const {
		return add(other);
	}

	Vector3<T> const sub(Vector3<T> const &other) const {
		return Vector3<T>(x - other.x, y - other.y, z - other.z);
	}

	Vector3<T> const sub(Vector2<T> const &other) const {
		return sub(Vector3<T>(other));
	}

	Vector3<T> opposite() { return Vector3<T>(-x, -y, -z); }

	Vector3<T> operator-(Vector3<T> const &other) { return sub(other); }

	Vector3<T> const operator-() { return opposite(); }

	Vector3<T> const multiply(double rate) const {
		return Vector3<T>(x * rate, y * rate, z * rate);
	}

	Vector3<T> const operator*(double rate) const { return multiply(rate); }

	double dot(Vector3<T> const &other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	double operator*(Vector3<T> const &other) const { return dot(other); }

	Vector3 cross(Vector3<T> const &other) const {
		return Vector3<T>(y * other.z + other.y * z,
				  -(x * other.z - other.x * z),
				  x * other.y + other.x * y);
	}

	double mod() const {
		return std::sqrt((double)(x * x + y * y + z * z));
	}

	void operator+=(Vector3<T> const &other) { *this = add(other); }

	void operator-=(Vector3<T> const &other) { *this = sub(other); }

	Vector3<T> normalize() const {
		double mod = this->mod();
		if (mod != 0) {
			return Vector3<T>(x / (T)mod, y / (T)mod, z / (T)mod);
		} else {
			return Vector3<T>(0, 0, 0);
		}
	}
};

using Vector2d = Vector2<double>;
using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2l = Vector2<long>;

using Vector3d = Vector3<double>;
using Vector3f = Vector3<float>;
using Vector3i = Vector2<int>;
using Vector3l = Vector3<long>;

Result<size_t> array_vec_to_index(Vector2i const &array_vec, size_t x_width);

template <typename SrcType, typename DestType>
Vector2<DestType> __base_vector_convert(Vector2<SrcType> const &vec) {
	return Vector2<DestType>((DestType)vec.x, (DestType)vec.y);
}
#define vector2i2d __base_vector_convert<int, double>
#define vector2d2i __base_vector_convert<double, int>
#define vector2l2d __base_vector_convert<long, double>
#define vector2d2l __base_vector_convert<double, long>

template <typename T>
std::string vec22std(Vector2<T> const &vec) {
	return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")";
}

template <typename T>
std::string vec32std(Vector2<T> const &vec) {
	return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) +
	       ", " + std::to_string(vec.z) + ")";
}

template <typename T>
T rooftop(T v, T roof = 0) {
	return v > roof ? roof : v;
}

template <typename T>
T lowest_floor(T v, T floor = 0) {
	return v < floor ? floor : v;
}

template <typename T>
Vector2<T> vec_rooftop(Vector2<T> const &vec, T roof = 0) {
	bool neg_x = vec.x < 0;
	bool neg_y = vec.y < 0;
	T abs_x = rooftop(std::abs(vec.x), roof);
	T abs_y = rooftop(std::abs(vec.y), roof);
	return Vector2<T>(neg_x ? -abs_x : abs_x, neg_y ? -abs_y : abs_y);
}
}  // namespace AhogeUtil
