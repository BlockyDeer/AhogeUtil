/*
* MIT License
* Copyright (c) 2024 BlockyDeer<blockydeer@outlook.com>
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*/
#pragma once

#include <glog/logging.h>

#include <string>

#include "error.hpp"

namespace AhogeUtil {
template <typename Content_t>
class Result final {
private:
	Content_t content;
	bool not_nil;

public:
	Result() { not_nil = false; }
	Result(Content_t const &content) {
		this->content = content;
		not_nil = true;
	}

	bool is_not_nil() { return not_nil; }

	bool operator()() { return !not_nil; }

	Content_t &get() {
		if (!not_nil) {
			LOG(FATAL) << "Null content";
		}
		return content;
	}
	Content_t release() {
		if (not_nil) {
			not_nil = false;
		}
		return content;
	}

	void set_content(Content_t const &content) {
		if (!not_nil) {
			not_nil = true;
		}
		this->content = content;
	}

	void panic_if_nil(std::string const &msg) const {
		if (!not_nil) {
			LOG(FATAL) << msg;
		}
	}

	Content_t &wrap(std::string const &error_msg = "") {
		panic_if_nil(error_msg);
		return content;
	}
};
}  // namespace AhogeUtil
