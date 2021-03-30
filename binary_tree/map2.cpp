#include "Map2.h"

    template <typename T1, typename T2>
    class Map2<T1, T2>::Node
    {
    public:
        pair<T1, T2> data_;
        Node* left_;
        Node* right_;
        Node* parent_;
        Node(const pair<T1, T2>& data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) : data_(data), left_(left), right_(right), parent_(parent) {}
    };

    template <typename T1, typename T2>
    typename Map2<T1, T2>::Node* Map2<T1, T2>::Insert_(const pair<T1, T2>& data, Node* temp, Node* parent)
    {
        auto has = Find_(data.first, root_);
        if (has)
            has->data_.second = data.second;
        else if (!temp) {
            temp = new Node(data, parent);
            if (parent)
            if (parent->data_.first > data.first) parent->left_ = temp;
                else parent->right_ = temp;
            if (!root_)
                root_ = temp;
            ++size_;
            AddToList(temp);
        }
        else {
            parent = temp;
            if (data.first <= temp->data_.first)
                temp->left_ = Insert_(data, temp->left_, parent);
            else
                temp->right_ = Insert_(data, temp->right_, parent);
        }
        return temp;
    }

    template <typename T1, typename T2>
    void Map2<T1, T2>::Clear_(Node* temp)
    {
        if (temp) {
            Clear_(temp->left_);
            Clear_(temp->right_);
            delete temp;
        }
    }

    template <typename T1, typename T2>
    void Map2<T1, T2>::Print_(Node* temp)
    {
        if (temp) {
            Print_(temp->left_);
            cout << temp->data_.second << ' ';
            Print_(temp->right_);
        }
    }

    template <typename T1, typename T2>
    typename Map2<T1, T2>::Node* Map2<T1, T2>::Next(Node* temp)
    {
        if (temp->right_) {
            temp = temp->right_;
            while (temp->left_)
                temp = temp->left_;
        }
        else if (temp->parent_)
        {
            Node* temp1 = temp->parent_;
            while (temp->data_.first >= temp1->data_.first)
            temp1 = temp1->parent_;
            temp = temp1;
        } else return nullptr;
        return temp;
    }

    template <typename T1, typename T2>
    typename Map2<T1, T2>::Node* Map2<T1, T2>::Previous(Node* temp)
    {
        if (temp->left_) {
            temp = temp->left_;
            while (temp->right_)
                temp = temp->right_;
        }
        else if (temp->parent_)
        {
            Node* temp1 = temp->parent_;
            while (temp->data_.first <= temp1->data_.first)
            temp1 = temp1->parent_;
            temp = temp1;
        } else return nullptr;
        return temp;
    }

    template <typename T1, typename T2>
    void Map2<T1, T2>::CopyTree(Node* temp)
    {
        if (!temp)
            return;
        Insert(temp->data_);
        CopyTree(temp->left_);
        CopyTree(temp->right_);
    }

    template <typename T1, typename T2>
    void Map2<T1, T2>::LeftOrRightParent(Node* temp, Node* value)
    {
        if (temp->parent_->data_.first >= temp->data_.first)
            temp->parent_->left_ = value;
        else
            temp->parent_->right_ = value;
    }

    template <typename T1, typename T2>
    typename Map2<T1, T2>::Node* Map2<T1, T2>::Find_(const T1& key, Node* temp)
    {
        if (!temp)
            return temp;
        if (key == temp->data_.first)
            return temp;
        else if (key < temp->data_.first)
            Find_(key, temp->left_);
        else if (key > temp->data_.first)
            Find_(key, temp->right_);
    }

    template <typename T1, typename T2>
    Map2<T1, T2>::Map2() : root_(nullptr), size_(0) {}

    template <typename T1, typename T2>
    Map2<T1, T2>::Map2(Map2<T1, T2>&& other)
    {
        root_ = other.root_;
        size_ = other.size_;
        other.root_ = nullptr;
        other.size_ = 0;
    }

    template <typename T1, typename T2>
    Map2<T1, T2>::Map2(const Map2<T1, T2>& other)
    {
        root_ = nullptr;
        size_ = 0;
        CopyTree(other.root_);
    }

    template <typename T1, typename T2>
    Map2<T1, T2>::~Map2()
    {
        Clear();
    }

    template <typename T1, typename T2>
    void Map2<T1, T2>::AddToList(Map2<T1, T2>::Node* temp)
    {   
        if (temp == FindMax()) list_of_nodes_.push_back(temp);
            else if (temp == FindMin()) list_of_nodes_.push_front(temp);
                else list_of_nodes_.insert(find(list_of_nodes_.begin(), list_of_nodes_.end(), Next(temp)), temp);
    }

    template <typename T1, typename T2>
    void Map2<T1, T2>::RemoveFromList(Map2<T1, T2>::Node* temp)
    {
        list_of_nodes_.erase(find(list_of_nodes_.begin(), list_of_nodes_.end(), temp));
    }

    template <typename T1, typename T2>
    void Map2<T1, T2>::Insert(const pair<T1, T2>& data)
    {
         Insert_(data, root_, nullptr);
    }

    template <typename T1, typename T2>
    T2& Map2<T1, T2>::operator[](const T1& key)
    {
        if (Node* temp = Find_(key, root_))
            return temp->data_.second;
        else {
            throw 1;
        }
    }

    template <typename T1, typename T2>
    T2 Map2<T1, T2>::operator[](const T1& key) const
    {
        if (Node* temp = Find_(key, root_))
            return temp->data_.second;
        else {
            throw 1;
        }
    }

    template <typename T1, typename T2>
    Map2<T1, T2>& Map2<T1, T2>::operator=(Map2<T1, T2>&& other)
    {
        Clear();
        root_ = other.root_;
        size_ = other.size_;
        other.root_ = nullptr;
        other.size_ = 0;
        return *this;
    }

    template <typename T1, typename T2>
    Map2<T1, T2>& Map2<T1, T2>::operator=(const Map2<T1, T2>& other)
    {
        Clear();
        CopyTree(other->root_);
        return *this;
    }

    template <typename T1, typename T2>
    bool Map2<T1, T2>::Remove(const T1& key)
    {
        auto temp = Find_(key, root_);

        if (!temp)
            return false;
        if (temp->left_ == temp->right_ && temp->right_ == nullptr && temp != root_) {
            LeftOrRightParent(temp, nullptr);
            RemoveFromList(temp);
            delete temp;
        }
        else if (temp->left_ && !temp->right_ && temp != root_) {
            LeftOrRightParent(temp, temp->left_);
            temp->left_->parent_ = temp->parent_;
            RemoveFromList(temp);
            delete temp;
        }
        else if (!temp->left_ && temp->right_ && temp != root_) {
            LeftOrRightParent(temp, temp->right_);
            temp->right_->parent_ = temp->parent_;
            RemoveFromList(temp);
            delete temp;
        }
        else if (size_ > 1)
        {
            Node* subst;
            if ((subst = Next(temp)) || (subst = Previous(temp))) {
                T1 KeyCopy = subst->data_.first;
                temp->data_.second = subst->data_.second;
                Remove(subst->data_.first);
                temp->data_.first = KeyCopy;
                ++size_;
            }
        }
        else
        {
            RemoveFromList(temp);
            delete temp;
            root_ = nullptr;
        }
        --size_;
        return true;
    }

    template <typename T1, typename T2>
    void Map2<T1, T2>::Print()
    {
        cout << size_ << " | ";
        Print_(root_);
        cout << endl;
    }
    
    template <typename T1, typename T2>
    void Map2<T1, T2>::Clear()
    {
        Clear_(this->root_);
        this->root_ = nullptr;
        this->size_ = 0;
    }

    template <typename T1, typename T2>
    bool Map2<T1, T2>::IsEmpty() const
    {
        return (size_ == 0);
    }

    template <typename T1, typename T2>
    size_t Map2<T1, T2>::GetSize() const
    {
        return size_;
    }