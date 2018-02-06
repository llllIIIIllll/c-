// this is from https://github.com/Poordeveloper/ini-parser.git
#include "ini.hpp"

#include <sstream>

void test1();
void test2();

int main()
{
	test1();
	test2();

	return 0;
}

void test1()
{
	std::ifstream ss("test.ini");
	INI::Parser p(ss);
	std::string a = p.top().values["a"];
	a = "abs\n";
	p.top().values["a"] = a;
	
	std::string eb = p.top().sections["e"].values["eb"];
	std::cout << eb;
	eb = "remember to add \n";
	p.top().sections["e"].values["eb"] = eb ;

	std::ofstream out("test.ini");
	p.dump(out);
}

void test2()
{
	std::stringstream ss;

	ss <<
		"a=1\n"
		"b=1\n\n"
		"[e]\n"
		"ea=1\n"
		"eb=1\n\n"
		"[c]\n"
		"ca=2\n"
		"cb=2\n\n"
		"[[d]]\n"
		"da=3\n"
		"db=3\n\n"
		"[A]\n"
		"Aa=4\n"
		"Ab=4\n";

	INI::Parser p(ss);
	std::ofstream out("test.ini");
	p.dump(out);
}