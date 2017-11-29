// An efficient program to randomly select k items from a stream of n items
//
#include <iostream>
using namespace std;

void coutArray(int stream[], int n)
{
	for(int i = 0; i < n; ++i)
		cout << stream[i] << " ";
	cout << endl;
}

void selectKItems(int stream[], int n, int k)
{
	int i;
	int reservoir[k];

	for(i = 0; i < k; ++i)
		reservoir[i] = stream[i];

	srand(time(NULL));

	for(; i < n; ++i)
	{
		int j = rand() % (i + 1);

		if(j < k)
			reservoir[j] = stream[i];
	}

	cout << "Following are k randomly selected items " << endl;
	coutArray(reservoir, k);
}

int main()
{
	int n;
	cin >> n;
	int stream[n];
	for(int i = 0; i < n; ++i)
		cin >> stream[i];

	int k;
	cin >> k;
	selectKItems(stream, n, k);
	return 0;
}
		
