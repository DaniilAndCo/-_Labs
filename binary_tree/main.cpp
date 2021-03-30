#include <iostream>
#include <string>
#include "set2.h"
#include "set1.h"
using namespace std;

int main()
{   //Demonstration of workability
    Set2<int> A;
    A.Insert(1);
    A.Insert(-5);
    A.Insert(8);
    A.Insert(-6);
    A.Print();
    for (auto i : A)
    cout << i << ' '; 
    /////////////////////////
    cout << endl;
    Set1<int> B;
    B.Insert(1);
    B.Insert(-5);
    B.Insert(8);
    B.Insert(-6);
    B.Print();
    for (auto i : B)
    cout << i << ' '; 
    /////////////////////////
    cout << endl;
    Map1<int, int> C;
    C.Insert(make_pair(1, 1));
    C.Insert(make_pair(2, 2));
    C.Insert(make_pair(3, 3));
    C.Insert(make_pair(4, 4));
    C.Print();
    for (auto i : C)
    cout << i << ' '; 
    /////////////////////////
    cout << endl;
    Map2<int, int> D;
    D.Insert(make_pair(1, 1));
    D.Insert(make_pair(2, 2));
    D.Insert(make_pair(3, 3));
    D.Insert(make_pair(4, 4));
    D.Print();
    for (auto i : D)
    cout << i << ' '; 
    return 0;
}