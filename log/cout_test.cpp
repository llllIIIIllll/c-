#include <iostream>
#include <fstream>

class ScopedRedirect
{
public:
    ScopedRedirect(std::ostream & inOriginal, std::ostream & inRedirect) :
        mOriginal(inOriginal),
        mOldBuffer(inOriginal.rdbuf(inRedirect.rdbuf()))
    { }

    ~ScopedRedirect()
    {
        mOriginal.rdbuf(mOldBuffer);
    }    

private:
    ScopedRedirect(const ScopedRedirect&);
    ScopedRedirect& operator=(const ScopedRedirect&);

    std::ostream & mOriginal;
    std::streambuf * mOldBuffer;
};


int main()
{
    std::cout << "Before redirect." << std::endl;
    std::ofstream filestream("redirected.txt");
    {
        ScopedRedirect redirect(std::cout, filestream);
        std::cout << "During redirect." << std::endl;

        // yay:
        filestream << "also to the file, right?...yes" << std::endl;
        filestream << "i am not on the screen" << std::endl;
    }
    std::cout << "After redirect." << std::endl;

    return 0;
}