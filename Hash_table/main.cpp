#include "Hash.h"
#include "Hash.cpp"
#include <iostream>
#include <set>
#include <string>
int main()
{
     auto A = HashTable<int, int>(50);
     A.Insert(14, 25);
     std::cout << A.Contains(14);
    return 0;
}