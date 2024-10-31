/*
* MIT License
* Copyright (c) 2024 BlockyDeer<blockydeer@outlook.com>
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*/
#pragma once

#include "vector.hpp"

namespace AhogeUtil {
namespace Collision {
bool is_point_in_rect(Vector2d const &point, Vector2d const &rect_top_left,
		      Vector2d const &rect_bottom_right);
}
}  // namespace AhogeUtil
