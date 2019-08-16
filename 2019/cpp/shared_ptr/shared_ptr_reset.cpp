#include <iostream>
#include <thread>
#include <string>

using namespace std;

int main()
{
    cout << "1"; 
    std::shared_ptr<string> p = std::make_shared<string>();
    cout << "2"; 
    p.reset();
    cout << "3"; 
    p = NULL;
    cout << "4"; 
    return 0;
}