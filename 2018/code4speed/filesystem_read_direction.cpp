#include <iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

void printDirectory(fs::path p)
{
	for (fs::directory_iterator it(p); it != fs::directory_iterator(); ++it)
	{
		if (fs::is_directory(it->path()))
		{
			std::cout << it->path().filename() << std::endl;
			printDirectory(it->path());
		}
	}
}

int main()
{
	fs::path p = L"E:/百度云同步盘";

	printDirectory(p);

	return 0;
}