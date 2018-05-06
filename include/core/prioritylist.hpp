#ifndef QRW_PRIORITYLIST_HPP
#define QRW_PRIORITYLIST_HPP

#include <cassert>

#include <map>
#include <set>

namespace qrw
{

template<class T>
class PriorityList
{
public:
    class iterator
    {
    public:
        typedef std::input_iterator_tag   iterator_category;
        typedef T          value_type;
        typedef ptrdiff_t  difference_type;
        typedef T*         pointer;
        typedef const T&   reference;

        iterator(const PriorityList<T>& owner);

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        iterator& operator++();
        reference operator*() const;        

    private:
        friend class PriorityList;

        typename std::map<int,std::set<T>,std::greater<T>>::iterator mapPos_;
        typename std::set<T>::iterator setPos_;
        const PriorityList<T>& owner_;
    }; // class iterator

    void insert(int priority, T value);
    void erase(int priority, T value);
    void clear();
    bool contains(int priority, T value);

    iterator begin();
    iterator end();

private:
    std::map<int,std::set<T>> items_;
};

template<class T>
PriorityList<T>::iterator::iterator(const PriorityList<T>& owner)
    : owner_(owner)
{}

template<class T>
bool PriorityList<T>::iterator::operator==(const PriorityList<T>::iterator& rhs) const
{
    if(&owner_ != &(rhs.owner_))
        return false;
    
    if(mapPos_ != rhs.mapPos_)
        return false;

    if(mapPos_ == owner_.items_.end())
        return true;
    
    return setPos_ == rhs.setPos_;
}

template<class T>
bool PriorityList<T>::iterator::operator!=(const PriorityList<T>::iterator& rhs) const
{
    return !(*this == rhs);
}

template<class T>
typename PriorityList<T>::iterator& PriorityList<T>::iterator::operator++()
{
    ++setPos_;

    if(setPos_ == mapPos_->second.end())
    {
        ++mapPos_;

        if(mapPos_ != owner_.items_.end())
        {
            // Sets must not be empty. This is ensured by PriorityList::erase().
            assert(mapPos_->second.size()>0);
            setPos_ = mapPos_->second.begin();
        }
    }

    return *this;
}

template<class T>
typename PriorityList<T>::iterator::reference PriorityList<T>::iterator::operator*() const
{
    return *setPos_;
}

template<class T>
void PriorityList<T>::insert(int priority, T value)
{
    assert(!contains(priority, value));

    items_[priority].insert(value);
}

template<class T>
void PriorityList<T>::erase(int priority, T value)
{
    assert(contains(priority, value));

    items_[priority].erase(value);
    if(items_[priority].size() == 0)
        items_.erase(priority);
}

template<class T>
void PriorityList<T>::clear()
{
    items_.clear();
}

template<class T>
bool PriorityList<T>::contains(int priority, T value)
{
    auto mapIter = items_.find(priority);

    if(mapIter == items_.end())
        return false;
    
     return mapIter->second.find(value) != mapIter->second.end();
}

template<class T>
typename PriorityList<T>::iterator PriorityList<T>::begin()
{
    iterator it(*this);
    it.mapPos_ = items_.begin();
    if(it.mapPos_ != items_.end())
        it.setPos_ = it.mapPos_->second.begin();

    return it;
}

template<class T>
typename PriorityList<T>::iterator PriorityList<T>::end()
{
    iterator it(*this);
    it.mapPos_ = items_.end();
    return it;
}

} // namespace qrw

#endif // QRW_PRIORITYLIST_HPP