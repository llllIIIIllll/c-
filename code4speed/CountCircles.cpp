#include <iostream>

int CountCircles0(int n)
{
    int r = 0;
    while (n > 0)
    {
        switch (n % 10)
        {
            case 8: r += 2; break;
            case 0: 
            case 6:
            case 9: r++; break;
        }
        n /= 10;
    }
    return n;
}

int CountCircles1(int n)
{
    int r = 0;
    // lookup tables
    const int x[] = {1, 0, 0, 0, 0, 0, 1, 0, 2, 1};
    while (n > 0)
    {
        r += x[n % 10];
        n /= 10;
    }
    return r;
}

int main()
{
    int n = 123;
    std::cout << CountCircles1(n) << std::endl;

    return 0;
}