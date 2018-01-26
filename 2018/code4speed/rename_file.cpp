#include <iostream>
#include <experimental/filesystem>
#include <sstream>
#include <string>

namespace fs = std::experimental::filesystem;

int main()
{
	fs::path p = "C:/Users/ASUS/Documents/WeChat Files/wbl___l/Files/test/0304img"; // portable format
	int i = 0;
	for (fs::directory_iterator it(p); it != fs::directory_iterator(); ++it)
	{
		std::ostringstream os;
		os << "image_" << i++ << ".jpg";
		fs::rename(p / it->path().filename(), p / "../new" / os.str());
		std::cout << i << std::endl;
	}
	system("pause");

}
