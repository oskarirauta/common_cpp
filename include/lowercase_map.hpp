#pragma once

#include <utility>
#include <string>

#include "tsl/ordered_map.h"
#include "common.hpp"

namespace common {

	template <class T>
	class lowercase_map {

	public:
		using mapped_type = T;
		using value_type = typename std::pair<std::string, T>;
		using map_type = typename tsl::ordered_map<std::string, T>;
		using size_type = typename map_type::size_type;
		using Self = typename common::lowercase_map<T>;

		using iterator = typename tsl::ordered_map<std::string, T>::iterator;
		using const_iterator = typename tsl::ordered_map<std::string, T>::const_iterator;


	private:
		map_type _m;

	public:

		iterator begin();
		iterator end();
		iterator find(const std::string& key);
		iterator mutable_iterator(const_iterator pos);
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
		const_iterator find(const std::string& key) const;

		T& operator [](const std::string& key);
		T& operator [](std::string& key);
                T operator [](const std::string& key) const;
                T operator [](std::string& key) const;

		bool operator ==(const lowercase_map<T>& other);
		bool operator !=(const lowercase_map<T>& other);
		bool operator <(const lowercase_map<T>&other);
		bool operator <=(const lowercase_map<T>&other);
		bool operator >(const lowercase_map<T>&other);
		bool operator >=(const lowercase_map<T>&other);
#if __cplusplus >= 202002L
		bool operator <=>(const lowercase_map<T>&other);
#endif

		Self& operator =(const std::initializer_list<value_type>& l);
		Self& operator =(const Self& other);
		Self& operator =(const map_type& map);
		Self& operator =(const value_type& pair);

		Self& operator *();
		const Self& operator*() const;
		Self* operator ->();
		const Self* operator ->() const;

		lowercase_map() {}
		lowercase_map(const std::initializer_list<value_type>& l);
		lowercase_map(const Self& other);
		lowercase_map(const map_type& map);
		lowercase_map(const value_type& pair);

		T& at(const std::string& key);
		const T at(const std::string& key) const;

		bool contains(const std::string& key) const;

		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		void insert(const std::initializer_list<value_type>& l);
		void insert(const Self& other);
		void insert(const value_type& pair);

		void append(const std::initializer_list<value_type>& l);
		void append(const Self& other);
		void append(const value_type& pair);

		const value_type& front() const;
		const value_type& back() const;
		bool insert_at_position(const_iterator pos, const value_type& value);
		bool insert_at_position(const_iterator pos, value_type& value);
		bool emplace_at_position(const_iterator pos, const value_type& value);
		bool emplace_at_position(const_iterator pos, value_type& value);
		bool rename(const std::string& old_key, const std::string& new_key);
		void pop_back();

		size_type erase(const std::string& key);
		size_type erase(iterator pos);
		size_type erase(const_iterator pos);
		void clear();

	}; // end of class common::lowercase_map<T> introduction

	template <class T>
	typename lowercase_map<T>::iterator lowercase_map<T>::begin() {
		return this -> _m.begin();
	}

	template <class T>
	typename lowercase_map<T>::iterator lowercase_map<T>::end() {
		return this -> _m.end();
	}

	template <class T>
	typename lowercase_map<T>::iterator lowercase_map<T>::find(const std::string& key) {
		auto it = this -> _m.find(key);
		return lowercase_map<T>::iterator(it);
	}

	template <class T>
	typename lowercase_map<T>::iterator lowercase_map<T>::mutable_iterator(lowercase_map<T>::const_iterator pos) {
		return lowercase_map<T>::iterator(this -> _m.mutable_iterator(pos.c_it));
	}

	template <class T>
	typename lowercase_map<T>::const_iterator lowercase_map<T>::cbegin() const {
		return lowercase_map<T>::const_iterator(this -> _m.cbegin());
	}

	template <class T>
	typename lowercase_map<T>::const_iterator lowercase_map<T>::cend() const {
		return lowercase_map<T>::const_iterator(this -> _m.cend());
	}

	template <class T>
	typename lowercase_map<T>::const_iterator lowercase_map<T>::begin() const {
		return lowercase_map<T>::const_iterator(this -> _m.cbegin());
	}

	template <class T>
	typename lowercase_map<T>::const_iterator lowercase_map<T>::end() const {
		return lowercase_map<T>::const_iterator(this -> _m.cend());
	}

	template <class T>
	typename lowercase_map<T>::const_iterator lowercase_map<T>::find(const std::string& key) const {
		auto it = this -> _m.find(key);
		return lowercase_map<T>::const_iterator(it);
	}

	template <class T>
	T& lowercase_map<T>::operator [](const std::string& key) {
		return this -> _m[common::to_lower(std::as_const(key))];
	}

	template <class T>
	T& lowercase_map<T>::operator [](std::string& key) {
		return this -> _m[common::to_lower(std::as_const(key))];
	}

	template <class T>
	T lowercase_map<T>::operator [](const std::string& key) const {
		return this -> _m[common::to_lower(std::as_const(key))];
	}

	template <class T>
	T lowercase_map<T>::operator [](std::string& key) const {
		return this -> _m[common::to_lower(std::as_const(key))];
	}

	template <class T>
	bool lowercase_map<T>::operator ==(const lowercase_map<T>& other) {
		return this -> _m == other._m;
	}

	template <class T>
	bool lowercase_map<T>::operator !=(const lowercase_map<T>& other) {
		return this -> _m != other._m;
	}

	template <class T>
	bool lowercase_map<T>::operator <(const lowercase_map<T>&other) {
		return this -> _m < other._m;
	}

	template <class T>
	bool lowercase_map<T>::operator <=(const lowercase_map<T>&other) {
		return this -> _m <= other._m;
	}

	template <class T>
	bool lowercase_map<T>::operator >(const lowercase_map<T>&other) {
		return this -> _m > other._m;
	}

	template <class T>
	bool lowercase_map<T>::operator >=(const lowercase_map<T>&other) {
		return this -> _m >= other._m;
	}

#if __cplusplus >= 202002L
	template <class T>
	bool lowercase_map<T>::operator <=>(const lowercase_map<T>&other) {
		return this -> _m <=> other._m;
	}
#endif

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator =(const std::initializer_list<std::pair<std::string, T>>& l) {

		this -> _m.clear();
		for ( auto& [key, value] : l )
			this -> _m[common::to_lower(std::as_const(key))] = value;
		return *this;
	}

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator =(const lowercase_map<T>& other) {

		this -> _m.clear();
		for ( auto& [key, value] : other )
			this -> _m[common::to_lower(std::as_const(key))] = value;
		return *this;
	}

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator =(const tsl::ordered_map<std::string, T>& map) {

		this -> _m.clear();
		for ( auto& [key, value] : map )
			this -> _m[common::to_lower(std::as_const(key))] = value;
		return *this;
	}

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator =(const std::pair<std::string, T>& pair) {

		this -> _m.clear();
		this -> _m[common::to_lower(std::as_const(pair.first))] = pair.second;
		return *this;
	}

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator *() {
		return this;
	}

	template <class T>
	const lowercase_map<T>& lowercase_map<T>::operator*() const {
		return this;
	}

	template <class T>
	lowercase_map<T>* lowercase_map<T>::operator ->() {
		return *this;
	}

	template <class T>
	const lowercase_map<T>* lowercase_map<T>::operator ->() const {
		return *this;
	}

	template <class T>
	lowercase_map<T>::lowercase_map(const std::initializer_list<std::pair<std::string, T>>& l) {

		for ( auto& [key, value] : l )
			this -> _m[common::to_lower(std::as_const(key))] = value;
	}

	template <class T>
	lowercase_map<T>::lowercase_map(const lowercase_map<T>& other) {

		for ( auto& [key, value] : other )
			this -> _m[common::to_lower(std::as_const(key))] = value;
	}

	template <class T>
	lowercase_map<T>::lowercase_map(const tsl::ordered_map<std::string, T>& map) {

		for ( auto& [key, value] : map )
			this -> _m[common::to_lower(std::as_const(key))] = value;
	}

	template <class T>
	lowercase_map<T>::lowercase_map(const std::pair<std::string, T>& pair) {
		this -> _m[common::to_lower(std::as_const(pair.first))] = pair.second;
	}

	template <class T>
	T& lowercase_map<T>::at(const std::string& key) {
		return this -> _m[common::to_lower(std::as_const(key))];
	}

	template <class T>
	const T lowercase_map<T>::at(const std::string& key) const {
		return this -> _m[common::to_lower(std::as_const(key))];
	}

	template <class T>
	bool lowercase_map<T>::contains(const std::string& key) const {
		return this -> _m.contains(common::to_lower(std::as_const(key)));
	}

	template <class T>
	bool lowercase_map<T>::empty() const {
		return this -> _m.empty();
	}

	template <class T>
	typename lowercase_map<T>::size_type lowercase_map<T>::size() const {
		return this -> _m.size();
	}

	template <class T>
	typename lowercase_map<T>::size_type lowercase_map<T>::max_size() const {
		return this -> _m.max_size();
	}

	template <class T>
	void lowercase_map<T>::insert(const std::initializer_list<std::pair<std::string, T>>& l) {

		for ( auto& [key, value] : l )
			this -> _m[common::to_lower(std::as_const(key))] = value;
	}

	template <class T>
	void lowercase_map<T>::insert(const lowercase_map<T>& other) {

		for ( auto& [key, value] : other )
			this -> _m[common::to_lower(std::as_const(key))] = value;
	}

	template <class T>
	void lowercase_map<T>::insert(const std::pair<std::string, T>& pair) {
		this -> _m[common::to_lower(std::as_const(pair.first))] = pair.second;
	}

	template <class T>
	void lowercase_map<T>::append(const std::initializer_list<std::pair<std::string, T>>& l) {
		this -> insert(l);
	}

	template <class T>
	void lowercase_map<T>::append(const lowercase_map<T>& other) {
		this -> insert(other);
	}

	template <class T>
	void lowercase_map<T>::append(const std::pair<std::string, T>& pair) {
		this -> insert(pair);
	}

	template <class T>
	const std::pair<std::string, T>& lowercase_map<T>::front() const {
		return this -> _m.front();
	}

	template <class T>
	const std::pair<std::string, T>& lowercase_map<T>::back() const {
		return this -> _m.back();
	}

	template <class T>
	bool lowercase_map<T>::insert_at_position(lowercase_map<T>::const_iterator pos, const std::pair<std::string, T>& value) {
		std::pair<std::string, T> p = { common::to_lower(value.first), value.second };
		return this -> _m.insert_at_position(pos.c_it, p).second;
	}

	template <class T>
	bool lowercase_map<T>::insert_at_position(lowercase_map<T>::const_iterator pos, std::pair<std::string, T>& value) {
		std::pair<std::string, T> p = { common::to_lower(value.first), value.second };
		return this -> _m.insert_at_position(pos.c_it, p).second;
	}

	template <class T>
	bool lowercase_map<T>::emplace_at_position(lowercase_map<T>::const_iterator pos, const std::pair<std::string, T>& value) {
		std::pair<std::string, T> p = { common::to_lower(value.first), value.second };
		return this -> _m.emplace_at_position(pos.c_it, p).second;
	}

	template <class T>
	bool lowercase_map<T>::emplace_at_position(lowercase_map<T>::const_iterator pos, std::pair<std::string, T>& value) {
		std::pair<std::string, T> p = { common::to_lower(value.first), value.second };
		return this -> _m.emplace_at_position(pos.c_it, p).second;
	}

	template <class T>
	bool lowercase_map<T>::rename(const std::string& old_key, const std::string& new_key) {
		std::string o = common::to_lower(old_key);
		std::string n = common::to_lower(new_key);

		if ( o == n || !this -> _m.contains(o) || this -> _m.contains(n))
			return false;

		if ( auto it = this -> _m.find(o); it != this -> _m.end()) {

			std::pair<std::string, T> p = { it -> first, it -> second };
			p.first = n;
			this -> _m.emplace_at_position(it, p);

			if ( this -> _m.contains(o))
				_m.erase(o);

			return true;

		} else return false;

	}

	template <class T>
	typename lowercase_map<T>::size_type lowercase_map<T>::erase(const std::string& key) {
		return this -> _m.erase(common::to_lower(std::as_const(key)));
	}

	template <class T>
	typename lowercase_map<T>::size_type lowercase_map<T>::erase(lowercase_map<T>::const_iterator pos) {
		return this -> _m.erase(pos.c_it);
	}

	template <class T>
	typename lowercase_map<T>::size_type lowercase_map<T>::erase(lowercase_map<T>::iterator pos) {
		return this -> _m.erase(pos.it);
	}

	template <class T>
	void lowercase_map<T>::clear() {
		this -> _m.clear();
	}

} // end of namespace
