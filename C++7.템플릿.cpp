#include <iostream>
using namespace std;
#pragma once // 중복 헤더가 있을경우 배제한다
//#define ON_MAIN
#ifdef ON_MAIN
template <typename T , typename C> T mymax(T a, C b)
{
	return a > b ? a : b;
}

template <typename T> T myswap(T& a, T& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
	return a, b;
}

int main() {
	//함수 탬플릿2
	{
		int i = 50;
		int& a = i;
		int j = 40;
		int& b = j;
		cout << "Before i = " << i << " j = " << j << endl;
		swap(a, b);
		cout << "After i = " << i << " j = " << j << endl;
	
		char c1 = 'A';
		char& a2 = c1;
		char c2 = 'Z';
		char& b2 = c2;
		cout << "Before i = " << c1 << " j = " << c2 << endl;
		swap(a2, b2);
		cout << "After i = " << c1 << " j = " << c2 << endl;
		return 0;
	}

	//함수 탬플릿1
	{
	cout << mymax(30, 20) << endl;
	cout << mymax(3.9, 4) << endl;
	cout << mymax('a', 4) << endl;
	cout << mymax<int>(10, 'a') << endl;
	return 0;
	}
}
#endif