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

template <class T>
MyVector<T>::MyVector(const unsigned int& size, const T& FillData) {
	this->size_ = size;
	this->capacity_ += START_CAPACITY + CAPACITY_EXPAND_CONST * size;
	if (size) {
		arrayOfValues_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			arrayOfValues_[i] = FillData;
		}
		for (int i = size_; i < capacity_; ++i) {
			arrayOfValues_[i] = T{};
		}
	}
	else {
		arrayOfValues_ = nullptr;
	}
	return;
}
template <class T>
MyVector<T>::MyVector() {
	this->size_ = NULL;
	this->capacity_ = START_CAPACITY;
	arrayOfValues_ = new T[capacity_];
	for (int i = 0; i < capacity_; ++i) {
		arrayOfValues_[i] = T{};
	}
	return;
}
template <class T>
MyVector<T>::MyVector(MyVector<T>&& other) {
	this->size_ = other.size_;
	this->capacity_ = other.capacity_;
	arrayOfValues_ = other.arrayOfValues_;
	other.capacity_ = NULL;
	other.arrayOfValues_ = nullptr;
	other.size_ = 0;
	return;
}
template <class T>
MyVector<T>::MyVector(const MyVector<T>& object) {
	this->size_ = object.size_;
	this->capacity_ = object.capacity_;
	arrayOfValues_ = new T[capacity_];
	for (int i = 0; i < size_; ++i) {
		arrayOfValues_[i] = object.arrayOfValues_[i];
	}
	for (int i = size_; i < capacity_; ++i) {
		arrayOfValues_[i] = T{};
	}
	return;
}
template<class T>
MyVector<T>::MyVector(const std::initializer_list<T>& listOfValues) {
	size_ = listOfValues.size();
	capacity_ += CAPACITY_EXPAND_CONST * size_;
	arrayOfValues_ = new T[capacity_];
	int i = 0;
	for (const auto& element : listOfValues) {
		arrayOfValues_[i] = element;
		++i;
	}
	for (; i < capacity_; ++i) {
		arrayOfValues_[i] = T{};
	}
	return;
}
template<class T>
MyVector<T>::~MyVector() {
	delete[] arrayOfValues_;
	return;
}
template<class T>
unsigned int MyVector<T>::GetSize() const {
	return size_;
}
template<class T>
bool MyVector<T>::Empty() const {
	return (size_ == 0);
}
template<class T>
void MyVector<T>::Resize(const unsigned int& newSize) {
	if (size_ >= newSize) {
		for (int i = newSize; i < size_; ++i)
		{
			arrayOfValues_[i] = T{};
		}
		size_ = newSize;
	}
	else if (newSize <= capacity_)
	{
		size_ = newSize;
	}
	else {
		capacity_ *= CAPACITY_EXPAND_CONST + newSize;
		T* tempArray = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			tempArray[i] = arrayOfValues_[i];
		}
		for (int i = size_; i < capacity_; ++i) {
			tempArray[i] = T{};
		}
		delete[] arrayOfValues_;
		arrayOfValues_ = tempArray;
		size_ = newSize;
	}
	return;
}
template<class T>
void MyVector<T>::PushBack(const T& data) {
	if (capacity_ - size_) {
		arrayOfValues_[size_] = data;
	}
	else {
		capacity_ *= CAPACITY_EXPAND_CONST;
		T* tempArray = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			tempArray[i] = arrayOfValues_[i];
		}
		tempArray[size_] = data;
		for (int i = size_ + 1; i < capacity_; ++i) {
			tempArray[i] = T{};
		}
		delete[] arrayOfValues_;
		arrayOfValues_ = tempArray;
	}
	++size_;
	return;
}
template<class T>
bool MyVector<T>::PopPack() {
	if (size_) {
		--size_;
		arrayOfValues_[size_] = T{};
	}
	else {
		return false;
	}
	return true;
}
template<class T>
T& MyVector<T>::operator[](unsigned int index) {
	if (index < size_ && index >= 0) {
		return arrayOfValues_[index];
	}
}
template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
	delete[] arrayOfValues_;
	this->size_ = other.size_;
	this->capacity_ = other.capacity_;
	arrayOfValues_ = new T[capacity_];
	for (int i = 0; i < size_; ++i) {
		arrayOfValues_[i] = other.arrayOfValues_[i];
	}
	for (int i = size_; i < capacity_; ++i) {
		arrayOfValues_[i] = T{};
	}
	return *this;
}
template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) {
	delete[] arrayOfValues_;
	this->size_ = other.size_;
	this->capacity_ = other.capacity_;
	arrayOfValues_ = other.arrayOfValues_;
	other.capacity_ = START_CAPACITY;
	other.arrayOfValues_ = new T[other.capacity_];;
	for (int i = 0; i < other.capacity_; ++i) {
		other.arrayOfValues_[i] = T{};
	}
	other.size_ = 0;
	return *this;
}
template<class T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
	return Iterator(arrayOfValues_);
}
template<class T>
typename MyVector<T>::Iterator MyVector<T>::end() {
	return Iterator(arrayOfValues_ + size_);
}

