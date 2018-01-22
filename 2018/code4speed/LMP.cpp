#include <algorithm>
#include <tuple>

template <typename TPL>
constexpr auto TupleSize() { return std::tuple_size<typename std::decay<TPL>::type>::value; }

template <auto N>
using IntegralConstant = std::integral_constant<decltype(N), N>;


int main()
{


}