#include "DoublyLinkedList.h"

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
	DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& object){
		tail_ = head_ = nullptr;
		size_ = 0;
		for (int i = 0; i < object.size(); ++i){
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
	typename DoublyLinkedList<T>::Iterator begin(){
		return Iterator(tail_);
	}
	template<class T>
	typename DoublyLinkedList<T>::Iterator end() {
		return Iterator(head_->next_);
	}
