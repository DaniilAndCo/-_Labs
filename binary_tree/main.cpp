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
    ages_and_names.Print();
    ages_and_names.Remove(25);
    ages_and_names.Print();
    ages_and_names.Remove(20);
    ages_and_names.Print();
    ages_and_names.Remove(7);
    ages_and_names.Print();
    ages_and_names.Remove(10);
    ages_and_names.Print();
    ages_and_names.Remove(5);
    ages_and_names.Print();
    ages_and_names.Remove(1);
    ages_and_names.Print();
    

    return 0;
}