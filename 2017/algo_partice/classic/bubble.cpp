#include <iostream>

using namespace std;

template <typename T>
void swift(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T* bubble_sort(T stream[], int n)
{
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n - 1 - i; ++j)
			if(stream[i] > stream[i + 1])
				swift(stream[i], stream[i + 1]);

	return stream;
}

int main()
{
	//! swift test
	int a = 12;
	int b = 13;
	cout << a << " " << b << endl;
	swift(a, b);
	cout << a << " " << b << endl;

	//! bubblu sort test
	int stream[] = {12, 23, 456, 13, 14, 56, 24, 57, 89};
	int n = sizeof stream / sizeof(int);
	for(auto e : stream)
		cout << e << " ";
	cout << endl;

	bubble_sort(stream, n);

	for(auto e : stream)
		cout << e << " ";
	cout << endl;

	return 0;
}
