#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>
#include <map>
#include <filesystem>
#include <algorithm>
#include <unistd.h>

#ifndef STRINGIFY
#define STRINGIFY(s) #s
#endif

#ifndef STRINGIFY_MACRO
#define STRINGIFY_MACRO(s) STRINGIFY(s)
#endif

#ifndef APPNAME
#define APPNAME unknown
#endif

#ifndef APPNAME_STR
#define APPNAME_STR STRINGIFY_MACRO(APPNAME)
#endif

namespace common {

	using char_type = std::string::value_type;

	template <class T>
	class lowercase_map;

	struct padding {
		size_t width;
		common::char_type fill = ' ';

		#if __cplusplus < 202002L
		padding(size_t width) : width(width) {}
		padding(size_t width, common::char_type fill) : width(width), fill(fill) {}
		#endif
	};

	struct duration {

	private:

		template<typename Rep, typename Period>
		void create(const std::chrono::duration<Rep, Period>& d);

	public:

		int hours, minutes, seconds, ms;
		long timestamp;

		template<typename Clock>
		duration(const std::chrono::time_point<Clock>& point,
				const std::chrono::time_point<Clock>& since);

		template<typename Rep, typename Period>
		duration(const std::chrono::duration<Rep, Period> &d);
	};

	static const std::string whitespace = " \t\n\r\f\v";

	uint64_t mix(const char& m, const uint64_t& s);
	uint64_t hash(const char *m);
	std::string to_string(common::char_type& ch);

	template<typename... Ts>
	std::string fmt(const std::string& fmt, Ts... vs);

	bool has_prefix(const std::string& str, const std::string& prefix);
	bool has_suffix(const std::string& str, const std::string& suffix);

	std::string str_first(const std::string& str, const common::char_type& delim = ' ');

	std::string trimmed(std::string& str, const std::string& trimchars);
	std::string trimmed(const std::string& str, const std::string& trimchars);

	std::vector<std::string> lines(const std::string& str, const std::string& delim = "\n",
		const std::string& trimchars = "\r");
	std::vector<std::string> lines(const std::string& str, const common::char_type& delim,
		const std::string& trimchars = "\r");

	std::vector<std::string> split(const std::string& str, const std::string& delim = "\n",
		const std::string& trimchars = "\r");
	std::vector<std::string> split(const std::string& str, const common::char_type& delim,
		const std::string& trimchars = "\r");

	std::string to_lower(std::string& str);
	std::string to_lower(const std::string& str);
	std::string to_upper(std::string& str);
	std::string to_upper(const std::string& str);
	std::string to_hex(const unsigned char& number, size_t minimum_length = 0);
	std::string int_to_hex(const unsigned int& number);

	double to_KiB(unsigned long int bytes);
	double to_MiB(unsigned long int bytes);
	double to_GiB(unsigned long int bytes);

	// return file size / capacity in human readable format
	std::string HumanReadable(const double &d);

	std::string join_vector(const std::vector<std::string>& vec, const std::string& delim = ", ");
	std::string join_vector(const std::vector<std::string>& vec, const common::char_type& delim);

	bool is_number(const std::string& s);
	bool is_float(const std::string& s);
	bool is_hex(const std::string& s);

	bool is_whitespace(const common::char_type& ch);
	bool is_space(const common::char_type& ch);
	bool is_digit(const common::char_type& ch);
	bool is_alpha(const common::char_type& ch);
	bool is_alnum(const common::char_type& ch);

	// test if string's first char is in criteria.. renamed from:
	// is_whitespace, is_space, is_digit, is_alpha and is_alnum
	bool starts_with_whitespace(const std::string& s);
	bool starts_with_space(const std::string& s);
	bool starts_with_digit(const std::string& s);
	bool starts_with_alpha(const std::string& s);
	bool starts_with_alnum(const std::string& s);

	std::string erase_prefix(std::string& s, size_t n);
	common::char_type erase_front(std::string &s);
	std::string to_string(const double& d);

	std::string unquoted(std::string& s, bool trimmed = true);
	std::string unquoted(const std::string& s, bool trimmed = true);

	std::string unquoted_and_trimmed(const std::string& s, bool lowercased = false);

	// trim from end of string (right)
	std::string rtrim_ws(const std::string& s, const std::string& ws = common::whitespace);

	// trim from beginning of string (left)
	std::string ltrim_ws(const std::string& s, const std::string& ws = common::whitespace);

	// trim from both ends of string (right then left)
	std::string trim_ws(const std::string& s, const std::string& ws = common::whitespace);

	std::string trim_leading(const std::string& str, int count = 1);

	double round(double val);
	std::string memToStr(double amount, bool gigabytes = false);

	template <typename T>
	inline std::string to_string(const T& value, const int precision = 6);

	std::string time_str(const std::time_t& t);
	std::string uptime_str(const std::time_t& t, bool longdesc = false, bool seconds = true);

	std::chrono::milliseconds get_millis();

	// why this? std::map already has contains method..
	template<typename K, typename V>
	inline bool map_contains(K key, const std::map<K, V> Map);
	template<typename T>
	inline bool vector_contains(const T& value, const std::vector<T>& values);

	common::lowercase_map<std::string> parseFile(const std::string& filename, const common::char_type& delim = ':');

	long int timezone_diff(); // current timezone diff in seconds
	std::chrono::system_clock::time_point mk_time_point(double d);
	std::chrono::seconds mk_duration(std::chrono::system_clock::time_point tp = std::chrono::system_clock::now());
	std::chrono::seconds mk_duration(double d);

	std::string put_time(const std::string& format, double d);
	std::string put_time(const std::string& format, const std::chrono::seconds &s);
	std::string put_time(const std::string& format, const std::chrono::system_clock::time_point& tp);
	std::string put_time(const std::string& format, const time_t& t);

	struct tm to_tm(const std::chrono::time_point<std::chrono::system_clock>& tp = std::chrono::system_clock::now());

	template<typename T>
	bool is_any_of(const T& value, const std::vector<T>& values);

	template<typename Iter>
	void rotate_one(Iter first, Iter last);

	std::vector<gid_t> get_groups();
	std::vector<std::string> get_netdevs();

	std::filesystem::path selfexe();
	std::filesystem::path selfpath();
	std::filesystem::path selfbasename();

}

std::ostream& operator <<(std::ostream& os, const common::padding& p);

template<typename Rep, typename Period>
void common::duration::create(const std::chrono::duration<Rep, Period>& d) {

	std::chrono::milliseconds millis =
		std::chrono::duration_cast<std::chrono::milliseconds>(d);

	this -> timestamp = millis.count();
	auto _hours = std::chrono::duration_cast<std::chrono::hours>(millis);
	this -> hours = _hours.count();
	millis -= _hours;
	auto _minutes = std::chrono::duration_cast<std::chrono::minutes>(millis);
	this -> minutes = _minutes.count();
	millis -= _minutes;
	auto _seconds = std::chrono::duration_cast<std::chrono::seconds>(millis);
	this -> seconds = _seconds.count();
	millis -= _seconds;
	this -> ms = millis.count();
}

template<typename Clock>
common::duration::duration(const std::chrono::time_point<Clock>& point,
	const std::chrono::time_point<Clock>& since) {
	this -> create(point.time_since_epoch() - since.time_since_epoch());
}

template<typename Rep, typename Period>
common::duration::duration(const std::chrono::duration<Rep, Period> &d) {
	this -> create(d);
}

template<typename... Ts>
std::string common::fmt(const std::string& fmt, Ts... vs) {

	size_t size = snprintf(nullptr, 0, fmt.c_str(), vs...);
	std::string buf;
	buf.reserve(size + 1);
	buf.resize(size);
	snprintf(&buf[0], size + 1, fmt.c_str(), vs...);
	return buf;
}

template <typename T>
inline std::string common::to_string(const T& value, const int precision) {

	std::ostringstream res;

	res.precision(precision);
	res << std::fixed << value;
	return res.str();
}

template<typename K, typename V>
inline bool common::map_contains(K key, const std::map<K, V> m) {
	return m.find(key) != m.end();
}

template<typename T>
bool common::vector_contains(const T& value, const std::vector<T>& values) {
	return common::is_any_of(value, values);
}

template<typename T>
bool common::is_any_of(const T& value, const std::vector<T>& values) {

	return std::find(values.begin(), values.end(), value) != values.end();
}

// This awesome snippet is not written by me, it is from here:
// https://stackoverflow.com/a/51660916/1314831
template<typename Iter>
void common::rotate_one(Iter first, Iter last) {

	using Value = typename Iter::value_type;

	if (first != last) {

		Value temp = std::move(*first);
		for ( Iter next = std::next(first); next != last; first = next, next = std::next(next))
			*first = std::move(*next);
		*first = std::move(temp);
	}
}
