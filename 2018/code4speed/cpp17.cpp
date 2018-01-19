#include <algorithm>
#include <vector>
#include <iostream>

void addNumber(int& n)
{
	n++;
}

void printNumber(int n)
{
	std::cout << n << " ";
}

int main()
{
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	std::for_each_n(v.begin(), v.size(), printNumber);
	std::cout << std::endl;

	std::for_each_n(v.begin(), v.size(), addNumber);

	std::for_each_n(v.begin(), v.size(), printNumber);
	std::cout << std::endl;


}