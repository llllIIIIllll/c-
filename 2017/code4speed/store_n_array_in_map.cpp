#include <map>
#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
	int hold[2][2] = 
	{
		{1, 2},
		{3, 4}
	};


	map<int, int(*)[2][2]> t;
	t.insert(std::make_pair(1, &hold));

	int end[2][2];
	std::cout << t.find(1)->second[0][0][0];

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			end[i][j] = t.find(1)->second[0][i][j];

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			std::cout << end[i][j] << " ";

}