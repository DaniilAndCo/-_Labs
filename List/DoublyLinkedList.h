#pragma once
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
        ~DoublyLinkedList();
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

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const unsigned int& size)
{
	tail_ = head_ = nullptr;
	size_ = size;
	for (unsigned int i = 0; i < size; ++i)
	{
		PushBack(T{});
	}
	return;
}
template<class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) {
	tail_ = other.tail_;
	head_ = other.head_;
	size_ = other.size_;
	other.head_ = other.tail_ = nullptr;
	other.size_ = 0;
	return;

}
template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const std::initializer_list<T>& listOfValues) {
	tail_ = head_ = nullptr;
	size_ = 0;
	for (const auto& element : listOfValues)
	{
		PushBack(element);
	}
	return;
}
template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& object) {
	tail_ = head_ = nullptr;
	size_ = 0;
	for (int i = 0; i < object.size(); ++i) {
		PushBack(object[i]);
	}
	return;
}
template<class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	tail_ = head_ = nullptr;
	size_ = 0;
	return;
}
template<class T>
~DoublyLinkedList::DoublyLinkedList(){
    Clear();
    return;
}
template<class T>
void DoublyLinkedList<T>::PushBack(T data)
{
	if (!head_)
	{
		head_ = new Node<T>(data);
		++size_;
	}
	else
	{
		head_->next_ = new Node<T>(data, head_, nullptr);
		Node<T>* temp = head_;
		head_ = head_->next_;
		if (!tail_)
		{
			tail_ = temp;
		}
		++size_;
	}
	return;
}
template<class T>
void DoublyLinkedList<T>::PushFront(T data)
{
	if (!head_)
	{
		head_ = new Node<T>(data);
		++size_;
	}
	else
	{
		if (!tail_)
		{
			tail_ = new Node<T>(data, nullptr, head_);
			head_->previous_ = tail_;
		}
		else
		{
			tail_->previous_ = new Node<T>(data, nullptr, tail_);
			Node<T>* temp = tail_;
			tail_ = tail_->previous_;
			temp->previous_ = tail_;
		}
		++size_;
	}
	return;
}
template<class T>
void DoublyLinkedList<T>::PopBack()
{
	Node<T>* temp = head_->previous_;
	delete head_;
	head_ = temp;
	if (head_)
	{
		Node<T>* pseudoEnd = new Node<T>(T{}, head_, nullptr);
		head_->next_ = pseudoEnd;
	}
	--size_;
	return;
}
template<class T>
void DoublyLinkedList<T>::PopFront()
{
	Node<T>* temp = tail_->next_;
	delete tail_;
	tail_ = temp;
	if (tail_)
	{
		tail_->previous_ = nullptr;
	}
	--size_;
	return;
}
template<class T>
void DoublyLinkedList<T>::Clear()
{
	while (head_)
	{
		PopBack();
	}
	head_ = tail_ = nullptr;
	return;
}
template<class T>
unsigned int DoublyLinkedList<T>::GetSize() const
{
	return size_;
}
template<class T>
bool DoublyLinkedList<T>::Empty() const
{
	return (size_ == 0);
}
template<class T>
T& DoublyLinkedList<T>::operator[](const unsigned int& index)
{
	Node<T>* temp = tail_;
	unsigned int counter = 0;
	while (counter != index)
	{
		temp = temp->next_;
		++counter;
	}
	return temp->data_;
}
template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	Clear();
	tail_ = head_ = nullptr;
	size_ = 0;
	for (int i = 0; i < other.size(); ++i) {
		PushBack(other[i]);
	}
	return *this;
}
template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>&& other)
{
	Clear();
	tail_ = other.tail_;
	head_ = other.head_;
	size_ = other.size_;
	other.head_ = other.tail_ = nullptr;
	other.size_ = 0;
	return *this;
}
template<class T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
	return Iterator(tail_);
}
template<class T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
	return Iterator(head_->next_);
}
