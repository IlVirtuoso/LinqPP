#pragma once
#pragma once
#include <vector>
#include "Functional.hpp"



template <typename T> class Enumerable : public std::vector<double>
{
  public:
    
    template <typename Predicate>
    Enumerable<T>& Where(Predicate predicate)
        requires Functor<Predicate, bool, T>
    {
        return Where<T, Enumerable<T>>(begin(), end(), predicate);
    }

    template <typename K, typename Predicate>
    Enumerable<T>& Select(Predicate predicate)
        requires Functor<Predicate, T, K>
    {
        return Select<T, K, Enumerable<T>>(begin(), end(), predicate);
    }

    Enumerable<T>& Split(int start, int end)
    {
        return Split<T>(this, start, end);
    }

    Enumerable<T>& Reverse()
    {
        return Reverse<T, Enumerable<T>>(begin(), end());
    }

    template <typename K> Enumerable<K> &ConvertAll()
    {
        return ConvertAll<T, K, Enumerable<K>>(begin(), end());
    }
};


