#include "MyDeque.h"
#include <iostream>
#include <utility>
using namespace std;

int main()
{
	//Demonstration of workability of main functions
	MyDeque<int> A;
	A.PushFront(7);
	A.PushFront(-7);
	A.PopBack();
	A.PushBack(25);
	MyDeque<int>::Iterator it1(A.begin());
	for (int i = 0; i < 512; ++i)
		A.PushBack(i);
	for (int i = 0; i < 512; ++i)
		A.PushFront(i);
	MyDeque<int> A1 = move(A);
	for (auto i : A1)
	{
		cout << i << endl;
	}
	MyDeque<int>::Iterator it(A1.end());
	cout << *(--it) << endl;
	cout << *it1 << endl;
	cout << *(it - 251);
	cout << A1;
	A.Clear();
  	return 0;
}

