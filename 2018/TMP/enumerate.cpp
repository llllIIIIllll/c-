#include <tuple>
#include <vector>
#include <iostream>

struct demo
{
    int a;
};

template <typename T,
          typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
auto enumerate(T && iterable)
{
    struct iterator
    {
        size_t i;
        TIter  iter;
        bool operator != (const iterator & other) const { return iter != other.iter; }
        void operator ++ () { ++i; ++iter; }
        auto operator * () const { return std::tie(i, *iter); }
    };
    struct iterable_wrapper
    {
        T iterable;
        auto begin() { return iterator{ 0, std::begin(iterable) }; }
        auto end() {return iterator{ 0, std::end(iterable)}; }
    };
    return iterable_wrapper{ std::forward<T>(iterable) };
}

int main()
{
    std::vector<demo> things;
    demo a, b;
    a.a = 1;
    b.a = 2;
    things.push_back(a);
    things.push_back(b);
    for (auto [i, thing] : enumerate(things))
    {
        std::cout << i << ": " << thing.a << std::endl;    
    }    
}