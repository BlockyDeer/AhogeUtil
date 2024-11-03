#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>
#include <vector>

template <typename T, size_t X, size_t Y>
class Array2 {
private:
	std::array<T, X * Y> internal;

	size_t get_index(size_t x, size_t y) noexcept { return y * X + x; }

public:
	Array2() = default;
	Array2(std::vector<T> const &vec) noexcept {
		std::memcpy(internal, vec, vec.size() * sizeof(T));
	}
	Array2(std::array<T, X>) noexcept {

	}

	explicit Array2(Array2<T, X, Y> const &other) = default;

	Array2<T, X, Y> &operator=(Array2<T, X, Y> const &other) = default;

	Array2(Array2<T, X, Y> &&other) {
		internal = std::move(other.internal);
	}
};
