#include <iostream>

using namespace std;

unsigned leading_zero_naive(int x)
{
    unsigned n = 0;
    const unsigned bits = sizeof(x) * 8;
    for (int i = i; i < bits; i++)
    {
        if (x < 0) break;
        n++;
        x <<= 1;
    }
    return n;
}   

unsigned leading_zero_naive2(int x)
{
    unsigned n = 0;
    const unsigned bits = sizeof(x) * 8;
    for (int i = bits; --i; )
    {
        if (x < 0) break;
        n++;
        x <<= 1;
    }
    return n;
}

unsigned leading_zero_naive3(int x)
{
    unsigned n = 0;
    if (x == 0) return sizeof(x) * 8;
    while (1) 
    {
        if (x < 0) break;
        n ++;
        x <<= 1;
    }
    return n;
}

unsigned leading_zero(unsigned x)
{
    unsigned n = 0;
    if (x <= 0x0000ffff) n += 16, x <<= 16;
    if (x <= 0x00ffffff) n +=  8, x <<=  8;
    if (x <= 0x0fffffff) n +=  4, x <<=  4;
    if (x <= 0x3fffffff) n +=  2, x <<=  2;
    if (x <= 0x7fffffff) n +=  1;
    return n;
}

int main()
{
    unsigned n = 0;
    for (int i = 1; i < 999999999; i++)
    {
        n += leading_zero_naive(n);
    }
    cout << n << endl;
    return 0;
}