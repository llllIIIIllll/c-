#include <iostream>
#include <pwd.h>

struct passwd *getpwnam(const char *name);
struct passwd *getpwuid(uid_t uid);

int main(int argc, char* argv[])
{
    struct passwd *pwd;
    int errno = 0;
    const char *name = "wbll";
    pwd = getpwnam(name);
    if (pwd == NULL) {
        if (errno == 0)
            std::cout << "Not found" << std::endl;
        else 
            std::cout << "Error" << std::endl;
    }
    else {
        std::cout << "pwd not null" << std::endl;
    }
}