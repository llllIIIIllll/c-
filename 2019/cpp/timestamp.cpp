#include <iostream>
#include <sstream>
#include <ctime>
#include <memory.h>
#include <stdio.h>
#include <string>

using namespace std;
 
time_t strTime2unix(const char timeStamp[])
{
    struct tm tm;
    memset(&tm, 0, sizeof(tm));
    
    sscanf(timeStamp, "%d-%d-%d %d:%d:%d", 
           &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
           &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
 
    tm.tm_year -= 1900;
    tm.tm_mon--;
 
    return mktime(&tm);
}

int IsLeapYear(int n)
{
    if (((n % 100 != 0) && (n % 4 == 0)) || (n % 400 == 0))
        return 1;
    else
        return 0;
}
 
int main()
{
    // char timeStamp[100] = "1970-1-1 08:00:00";
    for (int i = 1970; i < 2036; i++)
    {
        stringstream ss;
        ss << i << "-1-1 08:00:00";
        time_t t = strTime2unix(ss.str().c_str());
        cout << i << " " << t << " " << IsLeapYear(i) << endl;
    }
    return 0;
} 