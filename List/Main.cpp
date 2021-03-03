#include "DoublyLinkedList.h"
#include <iostream>

int main(){

	DoublyLinkedList<int> arr = {1, 2, 3};
	DoublyLinkedList<int>::Iterator it(arr.begin());
	DoublyLinkedList<int> arr1 = std::move(arr);
	for (auto i : arr1)
	{
		std::cout << i;
	}

	return 0;
}