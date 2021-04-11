#include "Hash.h"

template<typename key, typename value, typename hasher>

    void HashTable<key, value, hasher>::UpdateLoadFactor()
    {
        load_factor_ = amount_of_elements_ / main_col_.size();
    }

template<typename key, typename value, typename hasher>
    void HashTable<key, value, hasher>::Rehash()
    {
        vector<forward_list<pair<key, value>>> mainCopy;
        if (load_factor_ > REHASH_RATIO)
        {
            mainCopy.resize(main_col_.size() * REHASH_FACTOR);
            for (auto& batch : main_col_)
            {
                mainCopy[hash_(batch.front().first) % main_col_.size()] = batch;
            }
            main_col_ = mainCopy;
        }
        UpdateLoadFactor();
    }

template<typename key, typename value, typename hasher>    
    HashTable<key, value, hasher>::HashTable(HashTable<key, value, hasher>&& other)
    {
        main_col_ = std::move(other.main_col_);
        amount_of_elements_ = other.amount_of_elements_;
        load_factor_ = other.load_factor_;
        other.amount_of_elements_ = 0;
        other.load_factor_ = 0;
    } 

template<typename key, typename value, typename hasher>    
    HashTable<key, value, hasher>::HashTable(const HashTable<key, value, hasher>& other)
    {
        main_col_ = other.main_col_;
        amount_of_elements_ = other.amount_of_elements_;
        load_factor_ = other.load_factor_;
    } 

template<typename key, typename value, typename hasher>    
    HashTable<key, value, hasher>::~HashTable()
    {
        Clear();
    }     

template<typename key, typename value, typename hasher>
    HashTable<key, value, hasher>::HashTable(const size_t& sizeOfTable) : amount_of_elements_(0)
    {
        main_col_.resize(sizeOfTable);
        UpdateLoadFactor();
    }
template<typename key, typename value, typename hasher>    
    void HashTable<key, value, hasher>::Insert(const key& objectKey, const value& objectValue)
    {
        ++amount_of_elements_;
        main_col_[hash_(objectKey) % main_col_.size()].push_front(make_pair(objectKey, objectValue));
        UpdateLoadFactor();
        Rehash();
    }
template<typename key, typename value, typename hasher>
    bool HashTable<key, value, hasher>::Contains(const key& objectKey) const
    {
        return !main_col_[hash_(objectKey) % main_col_.size()].empty();
    }
template<typename key, typename value, typename hasher>    
    void HashTable<key, value, hasher>::Erase(const key& objectKey, const value& objectValue)
    {   
        --amount_of_elements_;
        main_col_[hash_(objectKey) % main_col_.size()].remove_if([&objectValue](value const& value_)
        {
            return value_ == objectValue;
        });
        UpdateLoadFactor();
        Rehash();
    }
template<typename key, typename value, typename hasher>    
    void HashTable<key, value, hasher>::Clear()
    {
        for (auto& batch : main_col_)
        {   
            batch.clear();
        }
        UpdateLoadFactor();
    }
template<typename key, typename value, typename hasher>   
    HashTable<key, value, hasher>& HashTable<key, value, hasher>::operator=(HashTable<key, value, hasher>&& other)
    {
        Clear();
        main_col_ = std::move(other.main_col_);
        amount_of_elements_ = other.amount_of_elements_;
        load_factor_ = other.load_factor_;
        other.amount_of_elements_ = 0;
        other.load_factor_ = 0;
        hash_ = other.hash_;
        return *this;
    }

template<typename key, typename value, typename hasher>   
    HashTable<key, value, hasher>& HashTable<key, value, hasher>::operator=(const HashTable<key, value, hasher>& other)
    {
        Clear();
        main_col_ = other.main_col_;
        amount_of_elements_ = other.amount_of_elements_;
        load_factor_ = other.load_factor_;
        return *this;
    }

template<typename key, typename value, typename hasher>
    value HashTable<key, value, hasher>::operator[](const key& objectKey) const
    {
        if (!Contains(objectKey))
        {   
            Insert(objectKey, value{});
        }
        else
        {
            for (auto element : main_col_[hash_(objectKey) % main_col_.size()])
            {
                if (element.first == objectKey)
                    return element.second;
            }
        }   
        return  (*main_col_[hash_(objectKey) % main_col_.size()].begin()).second;
    }
template<typename key, typename value, typename hasher>    
    value& HashTable<key, value, hasher>::operator[](const key& objectKey)
    {
        if (!Contains(objectKey))
        {   
            Insert(objectKey, value{});
        }
        else
        {
            for (auto& element : main_col_[hash_(objectKey) % main_col_.size()])
            {
                if (element.first == objectKey)
                    return element.second;
            }
        }
        UpdateLoadFactor();
        Rehash();
        return  (*main_col_[hash_(objectKey) % main_col_.size()].begin()).second;
    }

