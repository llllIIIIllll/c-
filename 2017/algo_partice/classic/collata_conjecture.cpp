#include <iostream>

using namespace std;

int collatz_conjecture(int n)
{
	int n_steps = 0;
	int n_new = n;

	while(n_new != 1)
	{
		if( n_new % 2 == 0)
		{
			n_new = n_new / 2;
		}
		else if( n_new % 2 == 1)
		{
			n_new = 3 * n_new + 1;
		}
		++n_steps;
	}
	return n_steps;
}

int main()
{
	int n;
	cin >> n;

	cout << collatz_conjecture(n);

	return 0;
}


