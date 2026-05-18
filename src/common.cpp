#include <iostream>
#include <algorithm>
#include <utility>
#include <sstream>
#include <string>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <charconv>

#include "common.hpp"
#include "lowercase_map.hpp"

uint64_t common::mix(const char& m, const uint64_t& s) {
	return ((s<<7) + ~(s>>3)) + ~m;
}

uint64_t common::hash(const char *m) {
	return (*m) ? common::mix(*m,hash(m+1)) : 0;
}

std::string common::to_string(common::char_type& ch) {

	std::string s;
	s += ch;
	return s;
}

bool common::has_prefix(const std::string& str, const std::string& prefix) {

	#if __cplusplus >= 202002L
		return str.starts_with(prefix);
	#else
		return str.size() >= prefix.size() && str.substr(0, prefix.size()).compare(prefix) == 0;
	#endif
}

bool common::has_suffix(const std::string& str, const std::string& suffix) {

	#if __cplusplus >= 202002L
		return str.ends_with(suffix);
	#else
		return str.size() >= suffix.size() && str.substr(str.size() - suffix.size(), suffix.size()).compare(suffix) == 0;
	#endif
}

std::string common::str_first(const std::string& str, const common::char_type& delim) {

	if ( auto pos = str.find_first_of(delim); pos != std::string::npos )
		return str.substr(0, pos);

	return "";
}

std::string common::trimmed(std::string& str, const std::string& trimchars) {

	if ( str.empty() || trimchars.empty())
		return str;

	for ( const char &ch : trimchars )
		str.erase(std::remove(str.begin(), str.end(), ch), str.end());

	return str;
}

std::string common::trimmed(const std::string& str, const std::string& trimchars) {

	std::string s = str;
	return common::trimmed(s, trimchars);
}

std::vector<std::string> common::lines(const std::string& str, const std::string& delim, const std::string& trimchars) {

	if ( str.empty())
		return {};

	std::string s(str);
	std::vector<std::string> vec;
	size_t pos;

	if ( !trimchars.empty())
		while (( pos = s.find_first_of(trimchars)) != std::string::npos )
			s.erase(pos, 1);

	while (( pos = s.find_first_of(delim)) != std::string::npos ) {

		std::string tok = s.substr(0, pos);
		vec.push_back(s.substr(0, pos));
		s.erase(0, pos + delim.size());
	}

	return vec;
}

std::vector<std::string> common::lines(const std::string& str, const common::char_type& delim, const std::string& trimchars) {

	return common::lines(str, common::to_string(delim), trimchars);
}

std::vector<std::string> common::split(const std::string& str, const std::string& delim, const std::string& trimchars) {

	std::vector<std::string> vec = common::lines(str, delim, trimchars);
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](const std::string& s) { return s.empty(); }), vec.end());
	return vec;
}

std::vector<std::string> common::split(const std::string& str, const common::char_type& delim, const std::string& trimchars) {

	std::vector<std::string> vec = common::lines(str, delim, trimchars);
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](const std::string& s) { return s.empty(); }), vec.end());
	return vec;
}

std::string common::to_lower(std::string& str) {

	for ( auto& ch : str )
		if ( std::isupper(ch))
			ch ^= 32;
	return str;
}

std::string common::to_lower(const std::string& str) {

	std::string s = str;
	return common::to_lower(s);
}

std::string common::to_upper(std::string& str) {

	for ( auto& ch : str )
		if ( std::islower(ch))
			ch &= ~32;
	return str;
}

std::string common::to_upper(const std::string& str) {
	std::string s = str;
	return common::to_upper(s);
}

// to_hex: https://stackoverflow.com/a/72132640/1314831

std::string common::to_hex(const unsigned char& number, size_t minimum_length) {

	char addressStr[4] = { 0 };
	std::to_chars(std::begin(addressStr), std::end(addressStr), number, 16);
	std::string ret{addressStr};
	while ( ret.size() < minimum_length )
		ret = "0" + ret;
	return ret;
}

std::string common::int_to_hex(const unsigned int& number) {

	char addressStr[20] = { 0 };
	std::to_chars(std::begin(addressStr), std::end(addressStr), number, 16);
	return std::string{addressStr};
}

double common::to_KiB(unsigned long int bytes) {

	if ( bytes < 103 )
		return (double)0;

	double d = (double)(bytes) / 1024;
	unsigned long int b = (unsigned long int)((d * 10) + 0.5);
	return (double)b * 0.1;
}

double common::to_MiB(unsigned long int bytes) {

	if ( bytes < 104858 )
		return (double)0;

	double d = (double)(bytes) / 1048576;
	unsigned long int b = (unsigned long int)((d * 10) + 0.5);
	return (double)b * 0.1;
}

double common::to_GiB(unsigned long int bytes) {

	if ( bytes < 107374183 )
		return (double)0;

	double d = (double)(bytes) / 1073741824;
	unsigned long int b = (unsigned long int)((d * 10) + 0.5);
	return (double)b * 0.1;
}

// based on example found from https://en.cppreference.com/w/cpp/filesystem/file_size

std::string common::HumanReadable(const double& d) {

	int o = 0;
	double mantissa = d;
	for ( ; mantissa >= 1024.; mantissa /= 1024., o++ );
	unsigned long int ns = std::ceil(mantissa * 10.);
	return common::to_string((double)ns * 0.1) + "BKMGTPE"[o];
}

std::string common::join_vector(const std::vector<std::string>& vec, const std::string& delim) {

		std::string res;

		for ( auto s : vec )
			res += ( res.empty() ? "" : delim ) + s;

		return res;
	}

std::string common::join_vector(const std::vector<std::string>& vec, const common::char_type& delim) {

	return common::join_vector(vec, common::to_string(delim));
}

bool common::is_number(const std::string& s) {

	return !s.empty() && s.find_first_not_of("1234567890") == std::string::npos;
}

bool common::is_float(const std::string& s) {

	if ( s.empty() || s.find_first_not_of("1234567890.") != std::string::npos || s.find_first_of("1234567890") == std::string::npos )
		return false;

	if ( s.find_first_of('.') == std::string::npos )
		return true;

	return std::count_if(s.begin(), s.end(), [](std::string::value_type ch) { return ch == '.'; }) < 2;
}

bool common::is_hex(const std::string& s) {

	return ( common::has_prefix(s, "0x") && s.size() > 2 &&
		 s.find_first_not_of("01234567890abcdefABCDEF", 2) == std::string::npos ) ||
                ( !s.empty() && s.find_first_not_of("01234567890abcdefABCDEF") == std::string::npos );
}

bool common::is_whitespace(const common::char_type& ch) {
	return std::string(" \t\n\r\f\v").find_first_of(ch) != std::string::npos;
}

bool common::is_space(const common::char_type& ch) {
	return ch == ' ' || ch == '\t';
}

bool common::is_digit(const common::char_type& ch) {
	return std::isdigit(ch);
}

bool common::is_alpha(const common::char_type& ch) {
	return ( ch >= 'A' && ch <= 'Z' ) || ( ch >= 'a' && ch <= 'z' ) || ch == '_';
}

bool common::is_alnum(const common::char_type& ch) {
	return std::isdigit(ch) || common::is_alpha(ch);
}

bool common::starts_with_whitespace(const std::string& s) {
	return !s.empty() && common::is_whitespace(s.front());
}

bool common::starts_with_space(const std::string& s) {
	return !s.empty() && common::is_space(s.front());
}

bool common::starts_with_digit(const std::string& s) {
	return !s.empty() && common::is_digit(s.front());
}

bool common::starts_with_alpha(const std::string& s) {
	return !s.empty() && common::is_alpha(s.front());
}

bool common::starts_with_alnum(const std::string& s) {
	return !s.empty() && is_alnum(s.front());
}

std::string common::erase_prefix(std::string& s, size_t n) {

	if ( s.empty() || n == 0 )
		return "";

	std::string r;

	if ( r = s.substr(0, n > s.size() ? s.size() : n); !r.empty())
		s.erase(0, r.size());

	return r;
}

common::char_type common::erase_front(std::string &s) {

	if ( s.empty())
		return 0;

	common::char_type c = s.front();
	s.erase(0, 1);
	return c;
}

std::string common::to_string(const double& d) {

	std::stringstream ss;
	ss << std::fixed << d;
	std::string s = ss.str();
	if ( s.find_first_of('.') != std::string::npos ) {

		while ( s.back() == '0' )
			s.pop_back();

		if ( s.back() == '.' )
			s.pop_back();
	}
	return s;
}

std::string common::unquoted(const std::string& s, bool trimmed) {

	std::string r = trimmed ? trim_ws(s) : s;

	if ( r.empty())
		return r;

	if ( trimmed ) {

		if ( r.front() == '\'' && r.back() == '\'' ) {

			r.erase(0, 1);
			r.pop_back();
		} else if ( r.front() == '"' && r.back() == '"' ) {

			r.erase(0, 1);
			r.pop_back();
		}

		return r;
	}

	int i1 = -1;
	int i2 = -1;
	std::string ws = " \t\r\f\v";

	for ( size_t i = 0; i < r.size(); i++ ) {

		if ( ws.find_first_of(r.at(i)) == std::string::npos && (
			r.at(i) == '\'' || r.at(i) == '"' )) {

			i1 = i;
			break;
		}
	}

	if ( i1 == -1 )
		return r;

	for ( size_t i = r.size() - 1; i > 0; i++ ) {

		if ( ws.find_first_of(r.at(i)) == std::string::npos &&
			i != (size_t)i1 && r.at(i) == r.at(i1) &&
			( r.at(i) == '\'' || r.at(i) == '"' )) {

			i2 = i;
			break;
		}
	}

	if ( i2 > i1 ) {

		r.erase(i2, 1);
		r.erase(i1, 1);
	}

	return r;
}

std::string common::unquoted(std::string& s, bool trimmed) {

	s = unquoted(std::as_const(s));
	return s;
}

std::string common::unquoted_and_trimmed(const std::string& s, bool lowercased) {

	return lowercased ?
			common::to_lower(common::trim_ws(common::unquoted(common::trim_ws(std::as_const(s))))) :
			common::trim_ws(common::unquoted(common::trim_ws(std::as_const(s))));
}

std::string common::rtrim_ws(const std::string& s, const std::string& ws) {

	std::string _s = s;
	_s.erase(_s.find_last_not_of(ws) + 1);
	return _s;
}

std::string common::ltrim_ws(const std::string& s, const std::string& ws) {

	std::string _s = s;
	_s.erase(0, _s.find_first_not_of(ws));
	return _s;
}

std::string common::trim_ws(const std::string& s, const std::string& ws) {

	return common::ltrim_ws(common::rtrim_ws(s, ws), ws);
}

std::string common::trim_leading(const std::string& str, int count) {

	if ( count < 1 )
		return str;

	if ((size_t)count > str.size())
		count = str.size();

	std::string ret = str;
	ret.erase(0, count);
	return ret;
}

double common::round(double val) {
	return val < 0 ? std::ceil(val - 0.5) : std::floor(val + 0.5);
}

std::string common::memToStr(double amount, bool gigabytes) {

	std::ostringstream res;
	double value = amount;
	uint8_t valuetype = 0;

	if ( value >= 1024 ) {

		value = common::round(value / 1024);
		valuetype = 1;

		if ( value >= 1024 ) {

			value = common::round(value / 1024);
			valuetype = 2;

			if ( gigabytes && value >= 1024 ) {

				value = round((value / 1024) * 100.0 ) / 100.0;
				valuetype = 3;
			}
		}
	}

	res.precision(valuetype == 3 ? 2 : 0);
	res << std::fixed << value;

	switch ( valuetype ) {
		case 0: res << "b"; break;
		case 1: res << "kb"; break;
		case 2: res << "mb"; break;
		case 3: res << "gb"; break;
	}

	return res.str();
}

std::string common::time_str(const std::time_t& t) {

/*
	std::time_t _t = t;
	struct tm *timeinfo = std::localtime(&_t);
	std::string ret(std::asctime(timeinfo));
	return common::trim(ret, "\t\r\n");
*/

	std::time_t _t = t;
	char buf[80];
	strftime(buf, sizeof buf, "%F %R", std::localtime(&_t));
	return std::string(buf);
}

std::string common::uptime_str(const std::time_t& t, bool longdesc, bool seconds) {

	std::time_t _t = t;
	std::string ret;

	int d = _t > 86400 ? _t / 86400 : 0;
	if ( d > 0 )
		_t -= d * 86400;

	int h = _t > 3600 ? _t / 3600 : 0;
	if ( h > 0 )
		_t -= h * 3600;

	int m = _t > 60 ? _t / 60 : 0;
	if ( m > 0 )
		_t -= m * 60;

	if ( longdesc ) {

		if ( d > 0 )
			ret += std::to_string(d) + ( d > 1 ? " days" : " day" );

		if ( d > 0 || h > 0 )
			ret += ( ret.empty() ? "" : " " ) + std::to_string(h) +
				( h != 1 ? " hours: " : " hour" );

		if ( d > 0 || h > 0 || m > 0 )
			ret += ( ret.empty() ? "" : " " ) + std::to_string(m) +
				( m != 1 ? " minutes": " minute" );

		if ( seconds )
			ret += ( ret.empty() ? "" : " " ) + std::to_string(_t) +
				( _t != 1 ? " seconds" : " second");
	} else {

		if ( d > 0 )
			ret += std::to_string(d) + "d";

		if ( d > 0 || h > 0 )
			ret += ( ret.empty() ? "" : " " ) + std::to_string(h) + "h";

		if ( d > 0 || h > 0 || m > 0 )
			ret += ( ret.empty() ? "" : " " ) + std::to_string(m) + "m";

		if ( seconds )
			ret += ( ret.empty() ? "" : " " ) + std::to_string(_t) + "s";
	}

	return ret;
}

std::chrono::milliseconds common::get_millis() {

	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch());
}

common::lowercase_map<std::string> common::parseFile(const std::string& filename, const common::char_type& delim) {

	std::ifstream fd(filename, std::ios::in | std::ios::binary);
	std::string s;
	tsl::ordered_map<std::string, std::string> m;

	if ( !fd || !fd.good()) {

		if ( fd.is_open())
			fd.close();

		throw std::runtime_error("fatal error, could not read " + filename);
	}

	while ( std::getline(fd, s)) {

		auto pos = s.find_first_of(delim);
		if ( pos == std::string::npos )
			continue;

		pos += 1;
		std::string k = common::trim_ws(common::to_lower(s.substr(0, pos - 1)));
		std::string v = common::trim_ws(s.substr(pos));

		if ( k.empty() || v.empty())
			continue;

		m[k] = v;
	}

	fd.close();
	return m;
}

static long int get_timezone_diff() {
	::tzset();
	extern long int timezone;
	return timezone;
}

long int common::timezone_diff() {
	time_t ts = 0;
	struct tm t;
	::time(&ts);
	::localtime_r(&ts, &t);
	return -get_timezone_diff() + ( t.tm_isdst ? 60 * 60 : 0);
}

std::chrono::system_clock::time_point common::mk_time_point(double d) {

	return std::chrono::system_clock::from_time_t(d);
}

std::chrono::seconds common::mk_duration(std::chrono::system_clock::time_point tp) {

	return std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
}

std::chrono::seconds common::mk_duration(double d) {

	std::chrono::system_clock::time_point tp = common::mk_time_point(d);
	return std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
}

std::string common::put_time(const std::string& format, double d) {

	std::stringstream ss;
	std::chrono::seconds s = common::mk_duration(d);
	std::chrono::system_clock::time_point tp(s);
	time_t t = std::chrono::system_clock::to_time_t(tp);

	ss << std::put_time(std::localtime(&t), format.c_str());
	return ss.str();
}

std::string common::put_time(const std::string& format, const std::chrono::seconds &s) {

	std::stringstream ss;
	std::chrono::system_clock::time_point tp(s);
	time_t t = std::chrono::system_clock::to_time_t(tp);

	ss << std::put_time(std::localtime(&t), format.c_str());
	return ss.str();
}

std::string common::put_time(const std::string& format, const std::chrono::system_clock::time_point& tp) {

	std::stringstream ss;
	time_t t = std::chrono::system_clock::to_time_t(tp);

	ss << std::put_time(std::localtime(&t), format.c_str());
	return ss.str();
}

std::string common::put_time(const std::string& format, const time_t& t) {

	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), format.c_str());
	return ss.str();
}

struct tm common::to_tm(const std::chrono::time_point<std::chrono::system_clock>& tp) {
	time_t ts = std::chrono::system_clock::to_time_t(tp);
	struct tm t;
	::localtime_r(&ts, &t);
	return t;
}

std::vector<gid_t> common::get_groups() {

	int n = ::getgroups(0, nullptr);
	gid_t *gids = new gid_t[n];
	::getgroups(n, gids);
	std::vector<gid_t> groups(gids, gids + n);
	delete []gids;
	return groups;
}

std::vector<std::string> common::get_netdevs() {

	if ( !std::filesystem::exists("/proc/net/dev"))
		throw std::runtime_error("cannot access /proc/net/dev");

	std::fstream fd("/proc/net/dev", std::ios::in);

	if ( !fd.good()) {

		if ( fd.is_open())
			fd.close();

		throw std::runtime_error("cannot read /proc/net/dev");
	}

	std::vector<std::string> devs;
	std::string line;

	while ( std::getline(fd, line)) {

		line = common::trim_ws(line);
		if ( common::has_prefix(line, "Inter") || common::has_prefix(line, "face"))
			continue;

		if ( auto pos = line.find_first_of(' '); pos != std::string::npos ) {

			line = line.substr(0, pos);
			if ( line.back() != ':' ) continue;
			else line.pop_back();
		} else continue;

		if ( line = common::trim_ws(line); !line.empty())
			devs.push_back(line);
	}

	fd.close();
	return devs;
}

std::filesystem::path common::selfexe() {

	return std::filesystem::exists("/proc/self/exe") &&
		std::filesystem::is_symlink("/proc/self/exe") ?
			std::filesystem::read_symlink("/proc/self/exe") : "";
}

std::filesystem::path common::selfpath() {

	return std::filesystem::exists("/proc/self/exe") &&
		std::filesystem::is_symlink("/proc/self/exe") ?
			std::filesystem::read_symlink("/proc/self/exe").parent_path() : "";
}

std::filesystem::path common::selfbasename() {

	return std::filesystem::exists("/proc/self/exe") &&
		std::filesystem::is_symlink("/proc/self/exe") ?
			std::filesystem::read_symlink("/proc/self/exe").filename() : "";
}

std::ostream& operator <<(std::ostream &os, const common::padding& p) {

	for ( size_t i = 0; i < p.width; i++ )
		os << p.fill;

	return os;
}
