#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> my_vec;
    my_vec.push_back("foo");
    my_vec.emplace_back("foo");

    set<string> my_set;
    my_set.insert("foo");
    my_set.emplace("foo");

    vector<int> vec1;
    vector<int> vec2;
    vec1.push_back(1<<20);
    vec2.emplace_back(1<<20);

    for_each(vec1.begin(), vec1.end(), [](auto x){ cout << x << " ";});
    std::cout << std::endl;
    for_each(vec2.begin(), vec2.end(), [](auto x){ cout << x << " ";});
     
}