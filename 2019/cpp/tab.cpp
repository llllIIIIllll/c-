#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
    
int startsWith(string s, string sub)
{
    return s.find(sub)==0 ? 1: 0;
}

int sameAt(string a, string b)
{
    size_t len = a.length() > b.length() ? a.length() : b.length();
    size_t i;
    for (i = 0; i < len; ++i)
    {
        if (a[i] != b[i])
        {
            break;
        }
    } 
    return ++i;
}

int main(int argc, char * argv[])
{

    string s0[] = {"reboot", "readtime", "reset", "12345", "12345677", "1234575656"};
    vector<string> s1(s0, s0+6); 
    string input = "1";

    vector<string>::iterator it = s1.begin();
    int count = 0;

    for (; it != s1.end();)
    {
        if (!startsWith(*it, input))
        {
            it = s1.erase(it);
            count++;
        }
        else
        {
            std::cout << (*it) << std::endl;
            it++;
        }
    }

    it = s1.begin();
    //！ input.length() 不加 1  并且取到12345 为所有其他匹配的字串时
    // 就有 12345 变成 1234 的问题
    input = s1.at(0); // 只有 s1.at(0) 才可能出现问题
    size_t pos = input.length(); // +1 无论input 取那个都不会有问题
    for (; it != s1.end(); ++it)
    {
        size_t same = sameAt(input, (*it));
        pos = (pos < same) ? pos : same;
    }

    std::cout << "==========" << std::endl;
    std::cout << input << std::endl;
    std::cout << input.substr(0, pos-1) << std::endl;

    return 0;
}