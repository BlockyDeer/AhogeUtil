/*
 * MIT License
 * Copyright (c) 2024 BlockyDeer<blockydeer@outlook.com>
 * Licensed under the MIT License. See LICENSE file in the project root for full
 * license information.
 */
#include "error.hpp"

#include <glog/logging.h>

#include "ahoge_string.hpp"

namespace AhogeUtil {
Error::Error(String const &msg) { this->msg = msg; }

bool Error::operator==(std::nullptr_t *) const { return msg.is_empty(); }
bool Error::operator!=(std::nullptr_t *) const { return !msg.is_empty(); }
bool Error::operator()() const { return *(this) != nullptr; }

void Error::print_to_logger(google::LogSeverity severity) {
	if (this->operator()()) {
		google::LogAtLevel(severity, msg.to_utf8());
	}
}

void Error::panic() {
	if (operator!=(nullptr)) {
		LOG(FATAL) << msg.to_utf8();
	}
}

void Error::warning() {
	if (operator!=(nullptr)) {
		LOG(WARNING) << msg.to_utf8();
	}
}

void panic(String &msg) {
	LOG(FATAL) << msg.to_utf8();
}
}  // namespace AhogeUtil
