#pragma once

#include <set>
#include <algorithm>
#include <initializer_list>

template <class T>
class FeatureSet {

	public:

		template <class T2>
		class iterator {

			friend class FeatureSet<T2>;

			private:
				typename std::set<T2>::iterator it;
				iterator(const typename std::set<T2>::iterator& it) : it(it) {}

			public:
				T2 operator *() noexcept { return *(this -> it); }
				iterator<T2> operator++() noexcept { ++this -> it; return *this; }
				iterator<T2> operator++(int) noexcept { iterator<T2> tmp = *this; ++this -> it; return tmp; }
				bool operator ==(const iterator& other) const noexcept { return this -> it == other.it; }
				bool operator !=(const iterator& other) const noexcept { return this -> it != other.it; }
		};

		template <class T2>
		class const_iterator {

			friend class FeatureSet<T2>;

			private:
				typename std::set<T2>::const_iterator it;
				const_iterator(const typename std::set<T2>::const_iterator& it) : it(it) {}

			public:
				T2 operator *() noexcept { return *(this -> it); }
				const_iterator<T2> operator++() noexcept { ++this -> it; return *this; }
				const_iterator<T2> operator++(int) noexcept { const_iterator<T2> tmp = *this; ++this -> it; return tmp; }
				bool operator ==(const const_iterator& other) const noexcept { return this -> it == other.it; }
				bool operator !=(const const_iterator& other) const noexcept { return this -> it != other.it; }
		};

		bool operator ==(const T& type) const;
		bool operator !=(const T& type) const;
		bool operator [](const T& type) const;
		FeatureSet<T>& operator =(const T& type);
		FeatureSet<T>& operator ^(const T& type);
		FeatureSet<T>& operator ^=(const T& type);
		FeatureSet<T>& operator +=(const T& type);
		FeatureSet<T>& operator -=(const T& type);

		FeatureSet<T>& operator =(const std::initializer_list<T>& features);
		FeatureSet<T>& operator =(const FeatureSet<T>& other);
		bool operator ==(const FeatureSet<T>& other) const;

		bool contains(const T& type) const;
		void set(const T& type, bool state = true);
		void unset(const T& type);
		void erase(const T& type);

		void clear();
		size_t size() const;
		bool empty() const;

		iterator<T> begin();
		iterator<T> end();
		const_iterator<T> cbegin();
		const_iterator<T> cend();
		const_iterator<T> begin() const;
		const_iterator<T> end() const;

		FeatureSet() {};
		FeatureSet(const std::initializer_list<T> features);

	private:
		std::set<T> store;
};

template <class T>
bool FeatureSet<T>::operator ==(const T& type) const {

	auto it = std::find_if(this -> store.begin(), this -> store.end(), [&type](const T& t) { return type == t; });
	return it != this -> store.end();
}

template <class T>
bool FeatureSet<T>::operator !=(const T& type) const {

	return !(this -> operator==(type));
}

template <class T>
bool FeatureSet<T>::operator [](const T& type) const {

	return this -> operator==(type);
}

template <class T>
FeatureSet<T>& FeatureSet<T>::operator =(const T& type) {

	if ( bool contains = this -> operator ==(type); !contains )
		this -> store.insert(type);

	return *this;
}

template <class T>
FeatureSet<T>& FeatureSet<T>::operator ^(const T& type) {

	if ( bool contains = this -> operator ==(type); contains )
		this -> store.erase(type);

	return *this;
}

template <class T>
FeatureSet<T>& FeatureSet<T>::operator ^=(const T& type) {

	if ( bool contains = this -> operator ==(type); contains )
		this -> store.erase(type);

	return *this;
}

template <class T>
FeatureSet<T>& FeatureSet<T>::operator +=(const T& type) {

	if ( bool contains = this -> operator ==(type); !contains )
		this -> store.insert(type);

	return *this;
}

template <class T>
FeatureSet<T>& FeatureSet<T>::operator -=(const T& type) {

	if ( bool contains = this -> operator ==(type); contains )
		this -> store.erase(type);

	return *this;
}

template <class T>
FeatureSet<T>& FeatureSet<T>::operator =(const std::initializer_list<T>& features) {

	this -> store.clear();

	for ( auto it = features.begin(); it != features.end(); it++ ) {

		T feature = *it;

		if ( !this -> contains(feature))
			this -> store.insert(feature);
	}

	return *this;
}

template <class T>
FeatureSet<T>& FeatureSet<T>::operator =(const FeatureSet<T>& other) {

	this -> store.clear();
	for ( auto it = other.store.begin(); it != other.store.end(); it++ ) {
		T value = *it;
		this -> store.insert(value);
	}
	return *this;
}

template <class T>
bool FeatureSet<T>::operator ==(const FeatureSet<T>& other) const {

	if ( this -> store.size() != other.store.size())
		return false;

	for ( auto it = this -> store.begin(); it != this -> store.end(); it++ ) {
		T value = *it;
		if ( other != value )
			return false;
	}

	return true;
}

template <class T>
bool FeatureSet<T>::contains(const T& type) const {

	return this -> operator==(type);
}

template <class T>
void FeatureSet<T>::set(const T& type, bool state) {

	if ( state && !this -> contains(type))
		this -> store.insert(type);
	else if ( !state && this -> contains(type))
		this -> store.erase(type);
}

template <class T>
void FeatureSet<T>::unset(const T& type) {

	this -> set(type, false);
}

template <class T>
void FeatureSet<T>::erase(const T& type) {

	this -> set(type, false);
}

template <class T>
void FeatureSet<T>::clear() {

	this -> store.clear();
}

template <class T>
size_t FeatureSet<T>::size() const {

	return this -> store.size();
}

template <class T>
bool FeatureSet<T>::empty() const {

	return this -> store.empty();
}

template <class T>
FeatureSet<T>::FeatureSet(const std::initializer_list<T> features) {

	for ( auto it = features.begin(); it != features.end(); it++ ) {

		T feature = *it;

		if ( !this -> contains(feature))
			this -> store.insert(feature);
	}
}

template <class T>
typename FeatureSet<T>::template iterator<T> FeatureSet<T>::begin() {
	return FeatureSet<T>::iterator<T>(this -> store.begin());
}

template <class T>
typename FeatureSet<T>::template iterator<T> FeatureSet<T>::end() {
	return FeatureSet<T>::iterator<T>(this -> store.end());
}

template <class T>
typename FeatureSet<T>::template const_iterator<T> FeatureSet<T>::cbegin() {
        return FeatureSet<T>::const_iterator<T>(this -> store.cbegin());
}

template <class T>
typename FeatureSet<T>::template const_iterator<T> FeatureSet<T>::cend() {
        return FeatureSet<T>::const_iterator<T>(this -> store.cend());
}

template <class T>
typename FeatureSet<T>::template const_iterator<T> FeatureSet<T>::begin() const {
        return FeatureSet<T>::const_iterator<T>(this -> store.cbegin());
}

template <class T>
typename FeatureSet<T>::template const_iterator<T> FeatureSet<T>::end() const {
        return FeatureSet<T>::const_iterator<T>(this -> store.cend());
}
