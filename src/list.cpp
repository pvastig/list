#include "list.h"

namespace pa {

 /*
template<class Type,
    class UnqualifiedType = std::remove_cv_t<Type>>
    class ForwardIterator : public std::iterator<std::forward_iterator_tag,
    UnqualifiedType,
    std::ptrdiff_t,
    Type*,
    Type&>
{
    friend class List<UnqualifiedType>;
    typename List<UnqualifiedType>::Node* m_it;

    explicit ForwardIterator(typename List<UnqualifiedType>::Node* it)
        : m_it(it)
    {
    }

public:
    ForwardIterator() : m_it(nullptr)
    {
    }

    void swap(ForwardIterator& other) noexcept
    {
        using std::swap;
        swap(m_it, other.iter);
    }

    ForwardIterator& operator++()
    {
        assert(m_it != nullptr && "Out-of-bounds iterator increment!");
        m_it = m_it->next;
        return *this;
    }

    ForwardIterator operator++(int)
    {
        assert(m_it != nullptr && "Out-of-bounds iterator increment!");
        ForwardIterator tmp(*this);
        m_it = m_it->next;
        return tmp;
    }

    // two-way comparison: v.begin() == v.cbegin() and vice versa
    template<class OtherType>
    bool operator==(ForwardIterator<OtherType> const& rhs) const
    {
        return m_it == rhs.m_it;
    }

    template<class OtherType>
    bool operator != (ForwardIterator<OtherType> const& rhs) const
    {
        return m_it != rhs.m_it;
    }

    Type& operator*() const
    {
        assert(m_it != nullptr && "Invalid iterator dereference!");
        return m_it->value;
    }

    Type& operator->() const
    {
        assert(m_it != nullptr && "Invalid iterator dereference!");
        return m_it->value;
    }

    // One way conversion: iterator -> const_iterator
    operator ForwardIterator<const Type>() const
    {
        return ForwardIterator<const Type>(m_it);
    }
};

using iterator = ForwardIterator<T>;
using const_iterator = ForwardIterator<const T>;

iterator begin();
iterator end();

const_iterator begin() const;
const_iterator end() const;

const_iterator cbegin() const;
const_iterator cend() const;

template<class T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(m_head);
}

template<class T>
typename List<T>::iterator List<T>::end()
{
    return iterator(nullptr);
}

template<class T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(m_head);
}

template<class T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(nullptr);
}

template<class T>
typename List<T>::const_iterator List<T>::cbegin() const
{
    return const_iterator(m_head);
}

template<class T>
typename List<T>::const_iterator List<T>::cend() const
{
    return const_iterator(nullptr);
}

//TODO: rewrite using iterators
template<class T>
bool List<T>::erase(iterator it)
{
    return remove(*it);
}

	*/

}//end namepace pa
