/*
 * MIT License
 * Copyright (c) 2024 BlockyDeer<blockydeer@outlook.com>
 * Licensed under the MIT License. See LICENSE file in the project root for full
 * license information.
 */
#include "ahoge_string.hpp"

#include <asm-generic/errno.h>
#include <iconv.h>
#include <uchar.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "ahogedef.hpp"
#include "error.hpp"

namespace AhogeUtil {
const iconv_t ICONV_INIT_FAILED = (iconv_t)-1;
const size_t ICONV_FAILED = (size_t)-1;

iconv_t u8tou32;
iconv_t u32tou8;

Error String::init() noexcept {
	u8tou32 = iconv_open("UTF-32LE", "UTF-8");
	u32tou8 = iconv_open("UTF-8", "UTF-32");
	if (u8tou32 == ICONV_INIT_FAILED) {
		return Error("Fail to init iconv u8tou32.");
	}
	if (u32tou8 == ICONV_INIT_FAILED) {
		return Error("Fail to init iconv u32tou8.");
	}
	return Error();
}

void String::cleanup() noexcept {
	iconv_close(u32tou8);
	iconv_close(u8tou32);
}

String::String() noexcept {}

String::String(const char *str) noexcept {
	std::string std_str(str);
	size_t in_bytes_left = std_str.size();
	size_t out_bytes_left = in_bytes_left * sizeof(uint32_t);

	char *in_buf = new char[std_str.size()];
	char *in_buf_mem = in_buf;
	std::memcpy(in_buf, std_str.data(), std_str.size());

	data.resize(std_str.size() * sizeof(uint32_t));
	char *out_buf = (char *)data.data();

	if (iconv(u8tou32, &in_buf, &in_bytes_left, &out_buf,
		  &out_bytes_left) == ICONV_FAILED) {
		// TODO: 错误处理
	}
	data.resize((std_str.size() * sizeof(uint32_t) - out_bytes_left) /
		    sizeof(uint32_t));

	delete[] in_buf_mem;
}

String::String(std::u32string const &str) noexcept {
	data.reserve(str.size());
	for (char32_t ch : str) {
		data.push_back(ch);
	}
}

// String::String(std::string const &str) noexcept : String((char *)str.c_str())
// {}

String::String(String &&other) noexcept { data = std::move(other.data); }

String::String(rune r) noexcept { data.push_back(r); }

String::String(String const &other) noexcept {
	data = std::vector<rune>(other.data);
}

String String::operator=(char *str) noexcept { return String(str); }

String String::operator=(const char *str) noexcept { return String(str); }

size_t String::size() const noexcept { return data.size(); }

bool String::is_empty() const noexcept { return data.empty(); }

rune *String::raw() const noexcept { return (rune *)data.data(); }

String String::add(char *str) const noexcept {
	String res(*this);
	res.data.insert(res.data.end(), str, str + std::strlen(str));
	return res;
}

String String::add(std::string const &str) const noexcept {
	String res(*this);
	res.data.insert(res.data.end(), str.begin(), str.end());
	return res;
}

String String::add(String const &other) const noexcept {
	String res(*this);
	res.data.insert(res.data.end(), other.data.begin(), other.data.end());
	return res;
}

String String::operator+(String const &other) const noexcept {
	return add(other);
}

String String::operator+(char *str) const noexcept { return add(str); }

String String::operator+(std::string const &str) const noexcept {
	return add(str);
}

std::ostringstream &operator<<(std::ostringstream &os, String &str) noexcept {
	os << str.to_utf8();
	return os;
}

void String::for_each(std::function<void(rune &)> func) noexcept {
	for (size_t i = 0; i < data.size(); i++) {
		func(data[i]);
	}
}

String String::sub_string(size_t index_start) const noexcept {
	return sub_string(index_start, data.size());
}

String String::sub_string(size_t index_start, size_t index_end) const noexcept {
	String res;
	res.data = std::vector<rune>(data.begin() + index_start,
				     data.begin() + index_end);
	return res;
}

rune String::operator[](size_t index) noexcept { return data[index]; }

bool String::equals(String const &other) noexcept {
	return data == other.data;
}

bool String::operator==(String const &other) noexcept {
	return equals(other);
}

size_t String::find(rune r) noexcept {
	auto iter = std::find(data.begin(), data.end(), r);
	if (iter == data.end()) {
		return string_null_pos;
	} else {
		return iter - data.begin();
	}
}

size_t String::find(String &str) noexcept {
	auto iter = std::search(data.begin(), data.end(), str.data.begin(),
				str.data.end());
	if (iter == data.end()) {
		return string_null_pos;
	} else {
		return iter - data.begin();
	}
}

size_t String::find(char *str) noexcept {
	String s(str);
	return find(s);
}

size_t String::find(const char *str) noexcept {
	String s(str);
	return find(s);
}

String String::replace(String &str, String const &replace_str) noexcept {
	size_t index = find(str);
	StringBuffer sb;

	sb.add(sub_string(0, index));
	sb.add(replace_str);
	sb.add(sub_string(index + str.size(), size()));

	return sb.to_string();
}

String String::replace_all(String &str, String const &replace_str) noexcept {
	size_t iter = 0;
	String s(*this);
	while (iter != string_null_pos) {
		s = s.replace(str, replace_str);
		iter = s.find(str);
	}
	return s;
}

std::string String::to_utf8() noexcept {
	size_t in_bytes_left = data.size() * sizeof(uint32_t);
	size_t out_bytes_left = in_bytes_left;

	std::vector<char> v(out_bytes_left);

	char *in_buf = reinterpret_cast<char *>(data.data());
	char *out_buf = v.data();

	if (iconv(u32tou8, &in_buf, &in_bytes_left, &out_buf,
		  &out_bytes_left) == ICONV_FAILED) {
		// TODO: 错误处理
	}
	v.resize(data.size() * sizeof(uint32_t) - out_bytes_left);
	return std::string(v.begin(), v.end());
}

std::u32string String::to_utf32() const noexcept {
	return std::u32string(data.begin(), data.end());
}

size_t StringBuffer::add(String const &str) noexcept {
	list.push_back(str);
	return list.size() - 1;
}

ulong StringBuffer::get_total_size() const noexcept {
	ulong sum = 0;
	for (String const &s : list) {
		sum += s.size();
	}
	return sum;
}

String StringBuffer::to_string() const noexcept {
	// TODO: 暂时先用这个实现
	String s;
	for (size_t i = 0; i < list.size(); i++) {
		s = s + list[i];
	}
	return s;
}

rune to_rune(char ch) noexcept { return (rune)ch; }
}  // namespace AhogeUtil
