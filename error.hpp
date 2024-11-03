/*
 * MIT License
 * Copyright (c) 2024 BlockyDeer<blockydeer@outlook.com>
 * Licensed under the MIT License. See LICENSE file in the project root for full
 * license information.
 */
#pragma once

#include <glog/logging.h>

#include <string>

#include "ahoge_string.hpp"

namespace AhogeUtil {
class String;
class Error final {
private:
	String msg;

public:
	Error() = default;
	Error(String const &msg);
	~Error() = default;

	bool operator==(std::nullptr_t *p) const;
	bool operator!=(std::nullptr_t *p) const;
	bool operator()() const;

	String get_msg() const { return String(msg); }

	void print_to_logger(
		google::LogSeverity severity = google::GLOG_INFO);

	void panic();
	void warning();
};

void panic(String &msg);
}  // namespace AhogeUtil
