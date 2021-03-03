#include <iostream>
#include "MyVector.h"
int main() {

	MyVector<int> arr = {1, 2 , 3};
	MyVector<int>::Iterator it(arr.begin());
	MyVector<int> arr1 = move(arr);
	for (auto i : arr1)
	{
		cout << i;
	}
	return 0;
}