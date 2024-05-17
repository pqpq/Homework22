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
    auto a = rpn.find_first_not_of("0123456789");
    auto b = rpn.find_first_not_of("0123456789", a + 1);
    auto c = rpn.find_first_not_of(" ", b);
    if (a == string_view::npos || b == string_view::npos || c == string_view::npos)
        return "???"; // {};

    const auto first  = rpn.substr(0, a);
    a++;
    const auto second = rpn.substr(a, b - a);
    const auto third  = rpn.substr(c);
    return string(first) + " " + string(third) + " " + string(second);
}

int main()
{
    // basics, and make sure we dont care about whitespace round operator
    test(infix("3 4-"), "3 - 4");
    test(infix("78 52*"), "78 * 52");
    test(infix("7 8 *"), "7 * 8");
    test(infix("7 8*"), "7 * 8");
    test(infix("7777 8  *"), "7777 * 8");
    return 0;
}
