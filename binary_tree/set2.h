#pragma once
#include "Map2.cpp"
#include "Map2.h"
using namespace std;
template<typename T>
class Set2
{
private:
	Map2<T, T> set_;

public:
	Set2()
	{

	}
	~Set2()
	{
		set_.Clear();
	}
	void Insert(T data)
	{
		set_.Insert(make_pair(data, data));
	}
	auto Remove(T data)
	{
		return set_.Remove(data);
	}
	auto GetSize()
	{
		return set_.GetSize();
	}
	auto IsEmpty()
	{
		return set_.IsEmpty();
	}
	void Clear()
	{
		set_.Clear();
	}
	void Print()
	{
		set_.Print();
	}
	class Iterator : std::iterator<std::bidirectional_iterator_tag, T>
	{
	private:
		typename Map2<T, T> :: Iterator it;
	public:
		Iterator() {

		}
		Iterator(const typename Map2<T, T>::Iterator& other)
		{
			this->it = other;
		}
		Iterator(const Set2<T>::Iterator& other){
			this->it = other.it;
		}
		// auto operator->() {
		// 	return ->it;
		// }
		Iterator& operator++() {
			++it;
			return *this;
		}
		Iterator& operator=(const Iterator& other) {
			this->it = other.it;
			return *this;
		}
		Iterator& operator++(T) {
			++it;
			return *this;
		}
		Iterator& operator-- () {
			--it;
			return *this;
		}
		Iterator& operator--(T) {
			--it;
			return *this;
		}
		T& operator*() {
			return *it;
		}
		T operator*() const {
			return *it;
		}
		bool operator==(const Iterator& other) {
			return (it == other.it);
		}
		bool operator!=(Iterator& other) {
			return !(it == other.it);	
		}

	};

	Iterator begin() {
	    return set_.begin();
    }
    Iterator end() {
	    return set_.end();
	}

};