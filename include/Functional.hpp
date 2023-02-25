#pragma once
#include <cstddef>

template <typename T>
concept Iterable = requires(T a) {
                       a++;
                       a--;
                       *a;
                       a == a;
                       a != a;
                   };

template <typename T>
concept Integrable = requires(T a) {
                         a += a == a;
                         a + a == a;
                     };

template <typename T>
concept Differentiable = requires(T a) {
                             a - a == a;
                             a -= a == a;
                         };

template <typename T, typename... Args>
concept Action = requires(T f, Args... argv) { f(argv...); };

template <typename F, typename Ret, typename... Args>
concept Functor = requires(F f, Ret r, Args... argv) { f(argv...) == r; };

template <typename Collectable, typename T>
concept StdCollection = requires(Collectable e, T val, int offset) {
                            e.push_back(val);
                            e.at(offset);
                            Collectable();
                        };

template <typename T, typename Iterator>
long IndexOf(Iterator start, Iterator end, T value)
    requires Iterable<Iterator>
{
    auto s = start;
    long ret = -1;
    long i = 0;
    while (s != end)
    {
        if (*s == value)
        {
            return i;
        }
        s++;
        i++;
    }
    return -1;
}

template <typename T, typename Iterator, typename Selector>
T Sum(Iterator start, Iterator end, Selector selector)
    requires Iterable<Iterator> && Functor<Selector, T, T> && Integrable<T>
{
    T sum = *start;
    auto s = start;
    s++;
    while (s != end)
    {
        sum += selector(*s);
        s++;
    }
    return sum;
}

template <typename T, typename Collection, typename Iterator, typename Predicate>
Collection &Where(Iterator start, Iterator end, Predicate predicate)
    requires Iterable<Iterator> && Functor<Predicate, bool, T> && StdCollection<Collection, T>
{
    Collection &collection = *new Collection();
    auto s = start;
    while (s != end)
    {
        if (predicate(*s))
            collection.push_back(*s);
        s++;
    }
    return collection;
}

template <typename T, typename K, typename Collection, typename Iterator, typename Predicate>
Collection &Select(Iterator start, Iterator end, Predicate predicate)
    requires Iterable<Iterator> && Functor<Predicate, K, T> && StdCollection<Collection, K>
{
    Collection &collection = *new Collection();
    auto s = start;
    while (s != end)
    {
        collection.push_back(predicate(*s));
        s++;
    }
    return collection;
}

template <typename In, typename Out, typename Collection, typename Iterator>
Collection &ConvertAll(Iterator start, Iterator end)
    requires Iterable<Iterator> && StdCollection<Collection, Out>
{
    return Select<In, Out, Collection>(start, end, [](In val) { return static_cast<Out>(val); });
}

template <typename T, typename Collection, typename Iterator, typename Operator>
Collection &ApplyAll(Iterator start, Iterator end, Operator op)
    requires StdCollection<Collection, T> && Iterable<Iterator> && Functor<Operator, T, T>
{
    auto s = start;
    Collection &collection = *new Collection();
    while (s != end)
    {
        collection.push_back(op(*s));
        s++;
    }
    return collection;
}

template <typename T, typename Collection>
Collection &Split(Collection &array, int start, int end)
    requires StdCollection<Collection, T>
{
    Collection &collection = *new Collection();
    for (int i = start; i < end; i++)
    {
        collection.push_back(array.at(i));
    }
    return collection;
}

template <typename T, typename Collection, typename Iterator>
Collection &Reverse(Iterator start, Iterator end)
    requires Iterable<Iterator> && StdCollection<Collection, T>
{
    Collection &collection = *new Collection();
    auto s = end;
    s--;
    while (s != start)
    {
        collection.push_back(*s);
        s--;
    }
    collection.push_back(*s);
    return collection;
}
