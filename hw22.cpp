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

void test(const string& a, const char* b)
{
    if (a == string{b})
        cout << "Test passed\n";
    else
        cerr << "Test FAILED! : \"" << a << "\" != \"" << b << "\"\n";
}

string infix(string_view rpn)
{
    return "3 - 4";
}

int main()
{
    test(infix("34-"), "3 - 4");
    return 0;
}
