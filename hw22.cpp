// ACCU Homework Challenge 22
//
// From https://accu.org/journals/cvu/????
//
// Write a program that will convert a Reverse Polish Notation expression for
// simple arithmetic (add, subract, multiply, divide) into an equivalent
// expression using infix notation.

//  3 4 − 5 +       ->      3 − 4 + 5
//  3 4 + 5 6 + ×   ->      (3 + 4) × (5 + 6)

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

template<typename T>
void test(string_view test_name, const T& a, const T& b)
{
    cout <<  "Test " << test_name;
    if (a == b)
        cout << " passed\n";
    else
        cerr << " FAILED!\n";
}

string infix(string_view rpn)
{
    return {};
}

int main()
{
    return 0;
}
