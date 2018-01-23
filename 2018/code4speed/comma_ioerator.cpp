#include <stdio.h>

int main()
{
	char* c{ (char*)-1 };
	if (c = 0, delete c++, c--)
	{
   		long a[] = { 0b1100, 0x1, 0b10, 0b110, 0x10 }, b = (long)c;
    	char(*p)(char) = [](char x) { return printf("%c", 0x43 + x), x; };
    	for (int i = (c++, p(b)); ++c, i < 5 || p(b); p(b | a[i]), ++i, c++);
	}
	return 0;

}
