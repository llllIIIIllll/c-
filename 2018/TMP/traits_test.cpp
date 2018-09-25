#include <type_traits>
#include <vector>
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;
using std::vector;

class PointW
{
    float x;
    float y;
};

template <typename I, typename T>
void test_traits()
{
    typedef typename std::iterator_traits<I>::value_type v_t;
    v_t var;
    //cout << typeid(var).name() << endl;

    cout << std::is_array<v_t>::value << endl;

    cout << std::is_integral<decltype(var)>::value << endl;

    cout << std::is_same<decltype(var), T>::value << endl;

    cout << std::is_fundamental<decltype(var)>::value << endl;
    
}

int main()
{
    vector<int> v1;

    //test_traits<vector<vector<int>>::iterator, int>();
    //test_traits<vector<int>::iterator, int>();

    //cout << typeid(v1).name() << endl;

    typedef std::decay<PointW>::type A;
    std::cout << "A: " << std::is_same<PointW, A>::value << std::endl;
    typedef std::decay<vector<PointW>>::type B;
    std::cout << "B1: " << std::is_same<PointW, B>::value << std::endl;
    std::cout << "B2: " << std::is_same<vector<PointW>, B>::value << std::endl;

}
