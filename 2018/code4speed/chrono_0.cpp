#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std;

int main()
{
    while(true)
    {
        auto time_now_us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
        long local_us =  time_now_us.count();
        
        std::cout << local_us << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}
