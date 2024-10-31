/*
* MIT License
* Copyright (c) 2024 BlockyDeer<blockydeer@outlook.com>
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*/
#include "vector.hpp"

namespace AhogeUtil {
Result<size_t> array_vec_to_index(Vector2i const &array_vec, size_t x_width) {
	if (array_vec.x < 0 || array_vec.y < 0) {
		return Result<size_t>();
	} else {
		return array_vec.y * x_width + array_vec.x;
	}
}

bool is_point_in_rect(Vector2d const &point, Vector2d const &rect_top_left,
		      Vector2d const &rect_bottom_right) {
	bool x = point.x >= rect_top_left.x && point.x <= rect_bottom_right.x;
	bool y = point.y >= rect_top_left.y && point.y <= rect_bottom_right.y;
	return x && y;
}
}  // namespace AhogeUtil
