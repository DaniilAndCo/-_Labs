#include <iostream>
#include <string>
#include "map.h"
#include "map.cpp"
using namespace std;

int main()
{
    //Demonstration of workability
    Map<int, string> ages_and_names;
    ages_and_names.Insert(make_pair(20, "Maxim"));
    ages_and_names.Insert(make_pair(25, "Kostya"));
    ages_and_names.Insert(make_pair(1, "Dan"));
    ages_and_names.Insert(make_pair(5, "Nastya"));
    ages_and_names.Insert(make_pair(7, "Nikita"));
    ages_and_names.Insert(make_pair(10, "Vadim"));
  
    Map<int, string> ages_and_names1 = ages_and_names;
    ages_and_names1.Print();
    ages_and_names.Print();
    ages_and_names.Remove(1);
    ages_and_names.Remove(8);
    ages_and_names1.Print();
    ages_and_names.Print();
    ages_and_names = move(ages_and_names1);
    ages_and_names1.Print();
    ages_and_names.Print();

    ages_and_names1.Clear();
    ages_and_names.Clear();
    return 0;
}