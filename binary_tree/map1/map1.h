#pragma once
#include <utility>
#include <algorithm>
#include <iostream>
using std::pair;
using namespace std;
template <typename T1, typename T2>
class Map1
{
protected: 
class Node;
private:
    
    Node* root_;
    size_t size_;

    Node* Insert_(const pair<T1, T2>&, Node*, Node*);
    void Clear_(Node*);
    void Print_(Node*);
 	static Node* Next(Node*);
    Node* Previous(Node*);
    void CopyTree(Node*);
    void LeftOrRightParent(Node*, Node*);
    Node* Find_(const T1&, Node*);
	Node* FindMin()
	{
		Node* temp = root_;
		while (temp->left_)
		temp = temp->left_;
		return temp;
	}
	Node* FindMax()
	{
		Node* temp = root_;
		while (temp->right_)
		temp = temp->right_;
		return temp;
	}

public:
    Map1();
    Map1(Map1<T1, T2>&&);
    Map1(const Map1<T1, T2>&);
    ~Map1();
    void Insert(const pair<T1, T2>&);
    T2& operator[](const T1&);
    T2 operator[](const T1&) const;
    Map1<T1, T2>& operator=(Map1<T1, T2>&&);
    Map1<T1, T2>& operator=(const Map1<T1, T2>&);
    bool Remove(const T1&);
    void Print();
    void Clear();
    bool IsEmpty() const;
    size_t GetSize() const;

    class Iterator : std::iterator<std::bidirectional_iterator_tag, T1>
    {
    private:
		Map1<T1, T2>* tree_;
		Node* object_;
	public:
		Iterator() : object_(nullptr), tree_(nullptr) {
		}
		Iterator(const Iterator& other) : object_(other.object_), tree_(other.tree_){
		}
		Iterator(Node* value, Map1<T1, T2>* tree) : object_(value), tree_(tree) {
		}
		Node* operator->() {
			return object_;
		}
		Iterator& operator++() {
			if (object_ == tree_->FindMax())
				++object_;
			else
				object_ = tree_->Next(object_);
			return *this;
		}
		Iterator& operator=(const Iterator& other) {
			object_ = other.object_;
			tree_ = other.tree_;
			return *this;
		}
		Iterator& operator++(T1) {
			if (object_ == tree_->FindMax())
				++object_;
			else
				object_ = tree_->Next(object_);
			return *this;
		}
		Iterator& operator-- () {
			if (object_ == tree_->FindMax() + 1)
				--object_;
			else
				object_ = tree_->Previous(object_);
			return *this;
		}
		Iterator& operator--(T1) {
				if (object_ == tree_->FindMax())
				--object_;
			else
				object_ = tree_->Previous(object_);
			return *this;
		}
		T2& operator*() {
			return object_->data_.second;
		}
		T2 operator*() const {
			return object_->data_.second;
		}
		bool operator==(const Iterator& other) {
			return (object_ == other.object_);
		}
		bool operator!=(Iterator& other) {
			return !(object_ == other.object_);	
		}
	};
    Iterator begin() {
	    return Iterator(this->FindMin(), this);
    }
    Iterator end() {
	    return Iterator(this->FindMax() + 1, this);
    }

};