#pragma once
#ifndef _LIST_
#define _LIST_
#include <initializer_list>
#include <iterator>
#include <utility>
template<class T>
class DoublyLinkedList
{
private:
	template<class T>
	class Node
	{
	public:
		Node<T>* next_;
		Node<T>* previous_;
		T data_;
		Node(const T& data = T{}, Node<T>* previous = nullptr, Node<T>* next = nullptr)
		{
			this->data_ = data;
			this->next_ = next;
			this->previous_ = previous;
		}
		~Node() {};
	};
	unsigned int size_;
	Node<T>* tail_;
	Node<T>* head_;
public:
	DoublyLinkedList(const unsigned int&);
	DoublyLinkedList(const std::initializer_list<T>&);
	DoublyLinkedList(const DoublyLinkedList<T>&);
	DoublyLinkedList(DoublyLinkedList<T>&&);
	DoublyLinkedList();
	void PushBack(T data);
	void PushFront(T data);
	void PopBack();
	void PopFront();
	void Clear();
	bool Empty() const;
	unsigned int GetSize() const;
	T& operator[](const unsigned int& index);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&&);
	class Iterator : std::iterator<std::bidirectional_iterator_tag, T> {
	private:
		Node<T>* object_;
	public:
		Iterator() : object_(nullptr) {
		}
		Iterator(const Iterator& other) : object_(other.object_) {
		}
		Iterator(Node<T>* value) : object_(value) {
		}
		T* operator->() {
			return object_;
		}
		Iterator& operator++() {
			object_ = object_->next_;
			return *this;
		}
		Iterator& operator=(const Iterator& other) {
			object_ = other.object_;
			return *this;
		}
		Iterator& operator++(T) {
			object_ = object_->next_;
			return *this;
		}
		Iterator& operator-- () {
			if (object_ != head_->next) {
				object_ = object_->previous_;
			}
			else {
				object_ = head_->previous_;
			}
			return *this;
		}
		Iterator& operator--(T) {
			if (object_ != head_->next) {
				object_ = object_->previous_;
			}
			else {
				object_ = head_->previous_;
			}
			return *this;
		}
		T& operator*() {
			return object_->data_;
		}
		T operator*() const {
			return object_->data_;
		}
		bool operator==(const Iterator& other) {
			return (object_ == other.object_);
		}
		bool operator!=(Iterator& other) {
			return !(object_ == other.object_);
		}
	};
	typename Iterator begin();
	typename Iterator end();
};
#endif // !_LIST_

