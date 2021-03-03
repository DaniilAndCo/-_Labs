#pragma once
#include <initializer_list>
#include <iterator>
#include <utility>
#define START_CAPACITY 5
#define CAPACITY_EXPAND_CONST 2
using namespace std;
template <class T>
class MyVector {
private:
	T* arrayOfValues_;
	unsigned int size_;
	unsigned int capacity_;
public:
	MyVector(const unsigned int&, const T&);
	MyVector();
	MyVector(MyVector<T>&&);
	MyVector(const MyVector<T>&);
	MyVector(const std::initializer_list<T>&);
	~MyVector();
	unsigned int GetSize() const;
	bool Empty() const;
	void Resize(const unsigned int&);
	void PushBack(const T&);
	bool PopPack();
	T& operator[](unsigned int index);
	MyVector<T>& operator=(const MyVector<T>&);
	MyVector<T>& operator=(MyVector<T>&&);
	class Iterator : std::iterator<std::random_access_iterator_tag, T> {
	private:
		T* object_;
	public:
		Iterator() : object_(nullptr) {
		}
		Iterator(T* value) : object_(value) {
		}
		Iterator(const Iterator& other) : object_(other.object_) {
		}
		T* operator->() {
			return object_;
		}
		Iterator& operator+(const int& n) {
			Iterator* temp = new Iterator(object_ + n);
			return *temp;
		}
		Iterator& operator+=(const int& n) {
			object_ += n;
			return *this;
		}
		Iterator& operator-=(const int& n) {
			object_ -= n;
			return *this;
		}
		Iterator& operator-(const int& n) {
			Iterator* temp = new Iterator(object_ - n);
			return *temp;
		}
		Iterator& operator++() {
			object_++;
			return *this;
		}
		Iterator& operator=(const Iterator& other) {
			object_ = other.object_;
			return *this;
		}
		Iterator& operator++(T) {
			object_++;
			return *this;
		}
		Iterator& operator-- () {
			object_--;
			return *this;
		}
		bool operator > (const Iterator& other) {
			return object_ > other.object_;
		}
		bool operator < (const Iterator& other) {
			return object_ < other.object_;
		}
		bool operator >= (const Iterator& other) {
			return object_ >= other.object_;
		}
		bool operator <= (const Iterator& other) {
			return object_ <= other.object_;
		}
		Iterator& operator--(T) {
			object_--;
			return *this;
		}
		T& operator*() {
			return *object_;
		}
		T operator*() const {
			return *object_;
		}
		bool operator==(const Iterator& other) {
			return (object_ == other.object_);
		}
		bool operator!=(Iterator& other) {
			return !(object_ == other.object_);
		}
		T& operator[](const int& index) {
			return *(object_ + index);
		}
		int operator-(const Iterator& other) {
			return distance(object_ - other.object_);
		}
		friend Iterator operator+(const int& number, const Iterator& iter) {
			return Iterator(iter.object_ + number);
		}
		friend Iterator operator+(const Iterator& iter, const int& number) {
			return Iterator(iter.object_ + number);
		}
	};
	typename Iterator begin();
	typename Iterator end();
};


