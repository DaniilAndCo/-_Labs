#pragma once

#include <initializer_list>
#include <iterator>
#include <utility>

template<class T>
class List {
private:
    class Node {
    public:
        Node *next_;
        Node *previous_;
        T data_;

        Node(const T& data = T{}, Node *previous = nullptr, Node *next = nullptr) {
            this->data_ = data;
            this->next_ = next;
            this->previous_ = previous;
        }

        ~Node() {};
    };

    unsigned int size_;
    Node *tail_;
    Node *head_;
public:
    List(const unsigned int&);

    List(const std::initializer_list<T>&);

    List(const List<T>&);

    List(List<T>&&);

    List();

    ~List();

    void PushBack(T data);

    void PushFront(T data);

    void PopBack();

    void PopFront();

    void Clear();

    bool IsEmpty() const;

    unsigned int GetSize() const;

    T& operator[](const unsigned int& index);

    T operator[](const unsigned int& index) const ;

    List<T>& operator=(const List<T>&);

    List<T>& operator=(const List<T>&&);

    class Iterator : std::iterator<std::bidirectional_iterator_tag, T> {
    private:
        Node *object_;
    public:
        Iterator() : object_(nullptr) {
        }

        Iterator(const Iterator& other) : object_(other.object_) {
        }

        Iterator(Node *value) : object_(value) {
        }

        T *operator->() {
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

        Iterator& operator--() {
            if (object_ != head_->next) {
                object_ = object_->previous_;
            } else {
                object_ = head_->previous_;
            }
            return *this;
        }

        Iterator& operator--(T) {
            if (object_ != head_->next) {
                object_ = object_->previous_;
            } else {
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

    Iterator begin();

    Iterator end();
};

template<class T>
List<T>::List(const unsigned int& size) {
    tail_ = head_ = nullptr;
    size_ = size;
    for (unsigned int i = 0; i < size; ++i) {
        PushBack(T{});
    }
    return;
}

template<class T>
List<T>::List(List<T>&& other) {
    tail_ = other.tail_;
    head_ = other.head_;
    size_ = other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
    return;

}

template<class T>
List<T>::List(const std::initializer_list<T>& listOfValues) {
    tail_ = head_ = nullptr;
    size_ = 0;
    for (const auto& element : listOfValues) {
        PushBack(element);
    }
    return;
}

template<class T>
List<T>::List(const List<T>& object) {
    tail_ = head_ = nullptr;
    size_ = 0;
    for (auto& element : object) {
        PushBack(element); 
    return;
}

template<class T>
List<T>::List() {
    tail_ = head_ = nullptr;
    size_ = 0;
    return;
}

template<class T>
List<T>::~List() {
    Clear();
    return;
}

template<class T>
void List<T>::PushBack(T data) {
    if (!head_) {
        head_ = new Node(data);
        ++size_;
    } else {
        head_->next_ = new Node(data, head_, nullptr);
        Node *temp = head_;
        head_ = head_->next_;
        if (!tail_) {
            tail_ = temp;
        }
        ++size_;
    }
    return;
}

template<class T>
void List<T>::PushFront(T data) {
    if (!head_) {
        head_ = new Node(data);
        ++size_;
    } else {
        if (!tail_) {
            tail_ = new Node(data, nullptr, head_);
            head_->previous_ = tail_;
        } else {
            tail_->previous_ = new Node(data, nullptr, tail_);
            Node *temp = tail_;
            tail_ = tail_->previous_;
            temp->previous_ = tail_;
        }
        ++size_;
    }
    return;
}

template<class T>
void List<T>::PopBack() {
    Node *temp = head_->previous_;
    delete head_;
    head_ = temp;
    if (head_) {
        Node *pseudoEnd = new Node(T{}, head_, nullptr);
        head_->next_ = pseudoEnd;
    }
    --size_;
    return;
}

template<class T>
void List<T>::PopFront() {
    Node *temp = tail_->next_;
    delete tail_;
    tail_ = temp;
    if (tail_) {
        tail_->previous_ = nullptr;
    }
    --size_;
    return;
}

template<class T>
void List<T>::Clear() {
    while (head_) {
        PopBack();
    }
    head_ = tail_ = nullptr;
    return;
}

template<class T>
unsigned int List<T>::GetSize() const {
    return size_;
}

template<class T>
bool List<T>::IsEmpty() const {
    return (size_ == 0);
}

template<class T>
T& List<T>::operator[](const unsigned int& index) {
    Node *temp = tail_;
    unsigned int counter = 0;
    while (counter != index) {
        temp = temp->next_;
        ++counter;
    }
    return temp->data_;
}

template<class T>
T List<T>::operator[](const unsigned int& index) const { 
    Node *temp = tail_;
    unsigned int counter = 0;
    while (counter != index) {
        temp = temp->next_;
        ++counter;
    }
    return temp->data_;
}

template<class T>
List<T>& List<T>::operator=(const List<T>& other) {
    Clear();
    tail_ = head_ = nullptr;
    size_ = 0;
    for (int i = 0; i < other.size(); ++i) {
        PushBack(other[i]);
    }
    return *this;
}

template<class T>
List<T>& List<T>::operator=(const List<T>&& other) {
    Clear();
    tail_ = other.tail_;
    head_ = other.head_;
    size_ = other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
    return *this;
}

template<class T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(tail_);
}

template<class T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(head_->next_);
}
