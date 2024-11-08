/*
 * MIT License
 * Copyright (c) 2024 BlockyDeer<blockydeer@outlook.com>
 * Licensed under the MIT License. See LICENSE file in the project root for full
 * license information.
 */
#pragma once

#include <iconv.h>

#include <cstdint>
#include <functional>
#include <sstream>
#include <string>

#include "ahogedef.hpp"

namespace AhogeUtil {
extern const iconv_t ICONV_INIT_FAILED;
extern const size_t ICONV_FAILED;

extern iconv_t u8tou32;
extern iconv_t u32tou8;
constexpr size_t string_null_pos = UINT32_MAX;

rune to_rune(char ch) noexcept;
bool is_blank(rune r) noexcept;

class Error;

class String final {
private:
	std::vector<rune> data;

public:
	static Error init() noexcept;
	static void cleanup() noexcept;
	String() noexcept;
	String(rune r) noexcept;
	String(rune *ch) noexcept;
	String(std::u32string const &str) noexcept;
	String(std::vector<rune> &vec) noexcept;
	String(const char *str) noexcept;
	explicit String(String const &other) noexcept;
	String(String &&other) noexcept;
	String &operator=(String const &other) noexcept = default;
	String operator=(char *str) noexcept;
	String operator=(const char *str) noexcept;

	size_t size() const noexcept;
	bool is_empty() const noexcept;
	rune *raw() const noexcept;

	rune operator[](size_t index) noexcept;

	bool equals(String const &other) noexcept;
	bool operator==(String const &other) noexcept;

	String add(char *str) const noexcept;
	String add(std::string const &str) const noexcept;
	String add(String const &other) const noexcept;
	String operator+(String const &other) const noexcept;
	String operator+(char *str) const noexcept;
	String operator+(std::string const &str) const noexcept;

	friend std::ostringstream &operator<<(std::ostringstream &os,
					      String &str) noexcept;

	void for_each(std::function<void(rune &)> func) noexcept;

	String sub_string(size_t index_start) const noexcept;
	String sub_string(size_t index_start, size_t index_end) const noexcept;

	size_t find(rune r) noexcept;
	size_t find(String &str) noexcept;
	size_t find(char *str) noexcept;
	size_t find(const char *str) noexcept;

	size_t rfind(rune r) noexcept;

	String replace(String &str, String const &replace_str) noexcept;
	String replace_all(String &replace_str, String const &res_str) noexcept;

	std::vector<String> split(String const &str,
				  rune separator = to_rune(' ')) noexcept;

	AhogeUtil::String trim() noexcept;

	std::string to_utf8() noexcept;
	std::u32string to_utf32() const noexcept;
};

class StringBuffer final {
private:
	std::vector<String> list;

public:
	StringBuffer &add(String const &str) noexcept;
	ulong get_total_size() const noexcept;
	String to_string() const noexcept;
};

std::ostringstream &operator<<(std::ostringstream &os, String &str) noexcept;
}  // namespace AhogeUtil
