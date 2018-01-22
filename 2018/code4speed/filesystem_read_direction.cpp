#include <iostream>
#include <sstream>
#include <experimental/filesystem>
#include <vector>
#include <string>
namespace fs = std::experimental::filesystem;

void getDirectory(fs::path p, std::vector<std::string> &s)
{
	for (fs::directory_iterator it(p); it != fs::directory_iterator(); ++it)
	{
		if (fs::is_directory(it->path()))
		{
			std::ostringstream os;
			os << it->path().filename();
			s.push_back(os.str());
		}
	}
}

int main()
{
	fs::path p = L"E:/百度云同步盘";
	std::vector<std::string> s;

	getDirectory(p, s);

	for (auto e : s)
	{
		std::cout << e << std::endl;
	}

	return 0;
}