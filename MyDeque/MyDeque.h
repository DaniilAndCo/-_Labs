#ifndef _DEQUE_
#define _DEQUE_
#include <array>
#include <vector>
#include <iterator>
#include <cmath>
using namespace std;
template <class T>
class MyDeque
{
private:
    static const size_t kSize = 64;
    template <class T>
    class Block
    {
    public:
        array<T, kSize>* block_ptr_;
        size_t block_index_;
        Block() : block_index_(NULL)
        {
            block_ptr_ = new array<T, kSize> {};
        }
    };
    size_t start_number_of_blocks_;
    size_t amount_of_elements_;
    vector<Block<T>*>  main_block_;
    size_t block_position_end_, block_position_begin_;
    size_t index_of_end_, index_of_begin_;
    void ChangeIndex();
public:
    MyDeque();
    MyDeque(const MyDeque<T>&);
    MyDeque(MyDeque<T>&&) noexcept;
    ~MyDeque();
    void PushBack(const T&);
    void PushFront(const T&);
    bool PopBack();
    bool PopFront();
    void Clear();
    bool IsEmpty();
    size_t GetSize() const;
    T& operator[] (const size_t&);
    T operator[] (const size_t&) const;
    friend ostream& operator<<(ostream& out, MyDeque<T>& object)
    {
        for (auto& element : object)
        {
            out << element << " ";
        }
        return out;
    }
    MyDeque<T>& operator=(const MyDeque<T>&);
    MyDeque<T>& operator=(MyDeque<T>&&);
    class Iterator;
    typename Iterator begin();
    typename Iterator end();
};
template <class T>
class MyDeque<T>::Iterator : std::iterator<std::random_access_iterator_tag, T> {
private:
    MyDeque<T>* deque_ptr_;
    Block<T>* block_;
    T* element_ptr_;
public:
    Iterator() : element_ptr_(nullptr), block_(nullptr), deque_ptr_(nullptr) {}
    Iterator(MyDeque<T>* deque_ptr, Block<T>* block, T* element_ptr) : deque_ptr_(deque_ptr), block_(block), element_ptr_(element_ptr) {}
    Iterator(const Iterator& other) : deque_ptr_(other.deque_ptr_), block_(other.block_), element_ptr_(other.element_ptr_) {}
    T* operator->()
    {
        return this->element_ptr_;
    }
    T& operator*()
    {
        return *this->element_ptr_;
    }
    T operator*() const
    {
        return *this->element_ptr_;
    }
    Iterator& operator++(T)
    {
        if (this->element_ptr_ < &((*this->block_->block_ptr_)[0]) + kSize - 1)
        {
            ++this->element_ptr_;
        }
        else
        {
            this->block_ = this->deque_ptr_->main_block_[block_->block_index_ + 1];
            this->element_ptr_ = &((*this->block_->block_ptr_)[0]);
        }
        return *this;
    }
    Iterator& operator++()
    {
        if (this->element_ptr_ < &((*this->block_->block_ptr_)[0]) + kSize - 1)
        {
            ++this->element_ptr_;
        }
        else
        {
            this->block_ = this->deque_ptr_->main_block_[block_->block_index_ + 1];
            this->element_ptr_ = &((*this->block_->block_ptr_)[0]);
        }
        return *this;
    }
    Iterator& operator-- ()
    {
        if (this->element_ptr_ > &((*this->block_->block_ptr_)[0]))
        {
            --this->element_ptr_;
        }
        else
        {
            this->block_ = this->deque_ptr_->main_block_[block_->block_index_ - 1];
            this->element_ptr_ = &((*this->block_->block_ptr_)[kSize - 1]);
        }
        return *this;
    }
    Iterator& operator--(T)
    {
        if (this->element_ptr_ > &((*this->block_->block_ptr_)[0]))
        {
            --this->element_ptr_;
        }
        else
        {
            this->block_ = this->deque_ptr_->main_block_[block_->block_index_ - 1];
            this->element_ptr_ = &((*this->block_->block_ptr_)[kSize - 1]);
        }
        return *this;
    }
    Iterator& operator=(const Iterator& other)
    {
        this->deque_ptr_ = other.deque_ptr_;
        this->block_ = other.block_;
        this->element_ptr_ = other.element_ptr_;
        return *this;
    }
    Iterator operator+(const size_t& n)
    {
        size_t index = abs(distance(this->element_ptr_, &((*this->block_->block_ptr_)[0])));
        for (auto block : (*this->deque_ptr_).main_block_)
        {
            if (block->block_index_ == this->block_->block_index_ + (index + n) / kSize)
            {
                return Iterator(this->deque_ptr_, block, &((*block->block_ptr_)[0]) + (index + n) % kSize);
            }
        }
    }
    Iterator operator-(const size_t& n)
    {
        size_t index = abs(distance(this->element_ptr_, &((*this->block_->block_ptr_)[0])));
        for (auto block : (*this->deque_ptr_).main_block_)
        {
            if (block->block_index_ == this->block_->block_index_ - (index + n) / kSize)
            {
                return Iterator(this->deque_ptr_, block, &((*block->block_ptr_)[kSize - 1]) - (index + n) % kSize);
            }
        }
    }
    Iterator& operator+=(const int& n)
    {
        *this = *this + n;
        return *this;
    }
    Iterator& operator-=(const int& n)
    {
        *this = *this - n;
        return *this;
    }
    T& operator[](const int& n)
    {
        return *(*this + n);
    }
    bool operator!=(Iterator& other)
    {
        return this->element_ptr_ != other.element_ptr_;
    }
    bool operator==(const Iterator& other)
    {
        return this->element_ptr_ == other.element_ptr_;
    }
    bool operator>(const Iterator& other)
    {
        if (this->deque_ptr_ != other.deque_ptr_) return false;
        if (this->block_->block_index_ > other.block_->block_index_) return true;
        else if (this->block_->block_index_ < other.block_->block_index_)	return false;
        else if (this->element_ptr_ > other.element_ptr_) return true;
        else return false;
    }
    bool operator<(const Iterator& other)
    {
        if (this->deque_ptr_ != other.deque_ptr_) return false;
        if (this->block_->block_index_ < other.block_->block_index_) return true;
        else if (this->block_->block_index_ > other.block_->block_index_)	return false;
        else if (this->element_ptr_ < other.element_ptr_) return true;
        else return false;
    }
    bool operator>=(const Iterator& other)
    {
        if (this->deque_ptr_ != other.deque_ptr_) return false;
        if (this->block_->block_index_ > other.block_->block_index_) return true;
        else if (this->block_->block_index_ < other.block_->block_index_)	return false;
        else if (this->element_ptr_ >= other.element_ptr_) return true;
        else return false;
    }
    bool operator<=(const Iterator& other)
    {
        if (this->deque_ptr_ != other.deque_ptr_) return false;
        if (this->block_->block_index_ < other.block_->block_index_) return true;
        else if (this->block_->block_index_ > other.block_->block_index_)	return false;
        else if (this->element_ptr_ <= other.element_ptr_) return true;
        else return false;
    }
};
template<class T>
void MyDeque<T>::ChangeIndex()
{
    for (auto block = 0; block < this->main_block_.size(); ++block)
    {
        this->main_block_[block]->block_index_ = block;
    }
    return;
}
template<class T>
MyDeque<T>::MyDeque() : start_number_of_blocks_(3), amount_of_elements_(0), block_position_begin_(0), block_position_end_(0), index_of_begin_(0), index_of_end_(0)
{
    for (auto counter = 0; counter < start_number_of_blocks_; ++counter)
    {
        this->main_block_.push_back(new Block<T>());
    }
}
template<class T>
MyDeque<T>::MyDeque(const MyDeque<T>& other)
{
    this->index_of_begin_ = NULL;
    this->index_of_end_ = NULL;
    this->block_position_begin_ = NULL;
    this->block_position_end_ = NULL;
    this->start_number_of_blocks_ = other.start_number_of_blocks_;
    for (auto counter = 0; counter < other.amount_of_elements_; ++counter)
    {
        this->main_block_.push_back(new Block<T>());
    }
    for (auto counter = 0; counter < other.amount_of_elements_; ++counter)
    {
        this->PushBack(other[counter]);
    }
}
template<class T>
MyDeque<T>::MyDeque(MyDeque<T>&& other) noexcept
{
    this->main_block_.clear();
    this->index_of_begin_ = other.index_of_begin_;
    this->index_of_end_ = other.index_of_end_;
    this->block_position_begin_ = other.block_position_begin_;
    this->block_position_end_ = other.block_position_end_;
    this->start_number_of_blocks_ = other.start_number_of_blocks_;
    this->start_number_of_blocks_ = other.start_number_of_blocks_;
    this->amount_of_elements_ = other.amount_of_elements_;
    this->main_block_ = other.main_block_;
    other.Clear();
}
template<class T>
MyDeque<T>::~MyDeque()
{
    this->main_block_.clear();
}
template<class T>
void MyDeque<T>::PushBack(const T& data)
{
    if (this->amount_of_elements_ != 0)
        if (this->index_of_end_ < this->kSize - 1)++this->index_of_end_;
        else if (this->block_position_end_ == this->main_block_.size() - 1)
        {
            this->main_block_.push_back(new Block<T>());
            ++this->block_position_end_;
            this->index_of_end_ = 0;
        }
        else
        {
            ++this->block_position_end_;
            this->index_of_end_ = 0;
        }
    (*(this->main_block_[block_position_end_]->block_ptr_))[index_of_end_] = data;
    ++this->amount_of_elements_;
    this->ChangeIndex();
}
template<class T>
void MyDeque<T>::PushFront(const T& data)
{
    if (this->amount_of_elements_ != 0)
        if (this->index_of_begin_ > 0)--this->index_of_begin_;
        else
        {
            if (this->block_position_begin_ > 0)
            {
                --this->block_position_begin_;
                this->index_of_begin_ = kSize - 1;
            }
            else if (this->block_position_end_ < main_block_.size() - 1)
            {
                this->index_of_begin_ = this->kSize - 1;
                for (auto i = this->main_block_.size() - 1; i > this->block_position_begin_; --i)
                {
                    swap(this->main_block_[i], this->main_block_[i - 1]);
                }
                ++this->block_position_end_;
            }
            else
            {
                this->main_block_.insert(this->main_block_.begin(), new Block<T>());
                this->index_of_begin_ = this->kSize - 1;
                ++this->block_position_end_;
            }
        }
    (*(this->main_block_[block_position_begin_]->block_ptr_))[index_of_begin_] = data;
    ++this->amount_of_elements_;
    this->ChangeIndex();
}
template<class T>
bool MyDeque<T>::PopBack()
{
    if (this->amount_of_elements_)
    {
        (*(this->main_block_[block_position_end_]->block_ptr_))[index_of_end_] = T{};
        if (this->amount_of_elements_ != 1)
        {
            if (this->index_of_end_ == 0)
            {
                if (this->block_position_end_ > 0)
                {
                    --this->block_position_end_;
                    this->index_of_end_ = this->kSize - 1;
                }
            }
            else --this->index_of_end_;
        }
        else this->index_of_begin_ = this->index_of_end_ = this->block_position_begin_ = this->block_position_end_ = 0;
        --this->amount_of_elements_;
        this->ChangeIndex();
        return true;
    }
    else return false;
}
template<class T>
bool MyDeque<T>::PopFront()
{
    if (this->amount_of_elements_)
    {
        (*(this->main_block_[this->block_position_begin_]->block_ptr_))[this->index_of_begin_] = T{};
        if (this->amount_of_elements_ != 1)
        {
            if (this->index_of_begin_ == this->kSize - 1)
            {
                this->index_of_begin_ = 0;
                for (auto i = this->block_position_begin_; i < this->block_position_end_; ++i)
                {
                    swap(this->main_block_[i], this->main_block_[i + 1]);
                }
                --this->block_position_end_;
            }
            else ++this->index_of_begin_;
        }
        else this->index_of_begin_ = this->index_of_end_ = this->block_position_begin_ = this->block_position_end_ = 0;
        --this->amount_of_elements_;
        this->ChangeIndex();
        return true;
    }
    else return false;
}
template<class T>
void MyDeque<T>::Clear()
{
    this->main_block_.clear();
    this->amount_of_elements_ = block_position_begin_ = block_position_end_ = index_of_begin_ = index_of_end_ = 0;
    for (auto counter = 0; counter < start_number_of_blocks_; ++counter)
    {
        this->main_block_.push_back(new Block<T>());
    }
    return;
}
template<class T>
bool MyDeque<T>::IsEmpty()
{
    return amount_of_elements_ == 0;
}
template<class T>
size_t MyDeque<T>::GetSize() const
{
    return this->amount_of_elements_;
}
template<class T>
T& MyDeque<T>::operator[](const size_t& index)
{
    return (*(*this->main_block_[(kSize * block_position_begin_ + index_of_begin_ + index) / kSize]).block_ptr_)[(kSize * block_position_begin_ + index_of_begin_ + index) % kSize];
}
template<class T>
T MyDeque<T>::operator[](const size_t& index) const
{
    return (*(*this->main_block_[(kSize * block_position_begin_ + index_of_begin_ + index) / kSize]).block_ptr_)[(kSize * block_position_begin_ + index_of_begin_ + index) % kSize];
}
template<class T>
MyDeque<T>& MyDeque<T>::operator=(MyDeque<T>&& other)
{
    this->main_block_.clear();
    this->index_of_begin_ = other.index_of_begin_;
    this->index_of_end_ = other.index_of_end_;
    this->block_position_begin_ = other.block_position_begin_;
    this->block_position_end_ = other.block_position_end_;
    this->start_number_of_blocks_ = other.start_number_of_blocks_;
    this->start_number_of_blocks_ = other.start_number_of_blocks_;
    this->amount_of_elements_ = other.amount_of_elements_;
    this->main_block_ = other.main_block_;
    other.Clear();
}
template<class T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque<T>& other)
{
    this->main_block_.clear();
    this->index_of_begin_ = NULL;
    this->index_of_end_ = NULL;
    this->block_position_begin_ = NULL;
    this->block_position_end_ = NULL;
    this->start_number_of_blocks_ = other.start_number_of_blocks_;
    for (auto counter = 0; counter < other.amount_of_elements_; ++counter)
    {
        this->main_block_.push_back(new Block<T>());
    }
    for (auto counter = 0; counter < other.amount_of_elements_; ++counter)
    {
        this->PushBack(other[counter]);
    }
    return *this;
}
template<class T>
typename MyDeque<T>::Iterator MyDeque<T>::begin()
{
    return Iterator(this, this->main_block_[block_position_begin_], &((*this->main_block_[block_position_begin_]->block_ptr_)[index_of_begin_]));
}
template<class T>
typename MyDeque<T>::Iterator MyDeque<T>::end()
{
    if (this->index_of_end_ < kSize - 1)
        return Iterator(this, this->main_block_[block_position_end_], &((*this->main_block_[block_position_end_]->block_ptr_)[index_of_end_ + 1]));
    else if (block_position_end_ < main_block_.size() - 1)
        return Iterator(this, main_block_[block_position_end_ + 1], &((*this->main_block_[block_position_end_ + 1]->block_ptr_)[0]));
    else
    {
        this->PushBack(T{});
        return Iterator(this, this->main_block_[block_position_end_ + 1], &((*this->main_block_[block_position_end_ + 1]->block_ptr_)[0]));
    }
}
#endif // !_DEQUE_
