#pragma once

#include <algorithm>
#include <forward_list>
#include <vector>
#include <utility>
#define REHASH_FACTOR 2
#define REHASH_RATIO 0.75

using std::vector;
using std::pair;
using std::forward_list;
using std::make_pair;

template<typename key, typename value, typename hasher = std::hash<key>>
class HashTable
{
private:
    vector<forward_list<pair<key, value>>> main_col_;
    hasher hash_;
    size_t amount_of_elements_;
    double load_factor_;

    void UpdateLoadFactor();
    void Rehash();

public:
    HashTable(HashTable<key, value, hasher>&&);
    HashTable(const HashTable<key, value, hasher>&);
    HashTable(const size_t&);
    ~HashTable();
    bool Contains(const key&) const;
    void Insert(const key&, const value&);
    void Erase(const key&, const value&);
    void Clear();
    HashTable<key, value, hasher>& operator=(HashTable<key, value, hasher>&&);
    HashTable<key, value, hasher>& operator=(const HashTable<key, value, hasher>&);
    value operator[](const key&) const;
    value& operator[](const key&); 
};
