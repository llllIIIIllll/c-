#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <auto value> constexpr auto TConstant = value; 
// ^^^^
constexpr auto const MySuperConst = TConstant <100>;



void test_fold_expression_1()
{
}

int main()
{
	test_fold_expression_1();
	system("pause");
}
