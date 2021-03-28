#pragma once
#include <utility>
#include <algorithm>
using std::pair;
template <typename T1, typename T2>
class Map
{
private:
    class Node;
    Node* root_;
    size_t size_;

    Node* Insert_(const pair<T1, T2>&, Node*, Node*);
    void Clear_(Node*);
    void Print_(Node*);
    Node* Next(Node*);
    Node* Previous(Node*);
    void CopyTree(Node*);
    void LeftOrRightParent(Node*, Node*);
    Node* Find_(const T1&, Node*);

public:
    void next(T1 key)
    {
        std::cout << Next(Find_(key, root_))->data_.second;
    }
    void prev(T1 key)
    {
        std::cout << Previous(Find_(key, root_))->data_.second;
    } 
    Map();
    Map(Map<T1, T2>&&);
    Map(const Map<T1, T2>&);
    ~Map();
    void Insert(const pair<T1, T2>&);
    T2& operator[](const T1&);
    T2 operator[](const T1&) const;
    Map<T1, T2>& operator=(Map<T1, T2>&&);
    Map<T1, T2>& operator=(const Map<T1, T2>&);
    bool Remove(const T1&);
    void Print();
    void Clear();
    bool IsEmpty() const;
    size_t GetSize() const;
};