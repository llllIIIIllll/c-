#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int i , j;
        char tmp;
        for(i = 0, j = s.size()-1; i<=j; i++, j--)
        {
            tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
        }
    }
};

int main()
{
    Solution test;
    vector<char> s;
    s.push_back('h');
    s.push_back('e');
    s.push_back('l');
    s.push_back('l');
    s.push_back('o');
    test.reverseString(s);
    
    for (auto c : s)

        std::cout << c;
}