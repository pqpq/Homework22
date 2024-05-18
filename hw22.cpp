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
#include <cctype>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

constexpr const char* digits = "0123456789";
constexpr const char* operators = "+-*/";

void test(const string& a, const char* b)
{
    if (a == string{b})
        cout << "Test passed\n";
    else
        cerr << "Test FAILED! : \"" << a << "\" != \"" << b << "\"\n";
}

bool contains(const char* s, char c)
{
    return string_view(s).find(c) != string_view::npos;
}

pair<string_view, string_view> token(string_view s)
{
    cout << "token(" << s << ") : ";

    while (!s.empty() && isspace(s[0])) s.remove_prefix(1);

    if (contains(digits, s[0]))
    {
        auto end = s.find_first_not_of(digits);
        cout << "digits " << end << " '" << s.substr(0, end) << "', '" << s.substr(end) << "'\n";
        return { s.substr(0, end), s.substr(end) };
    }
    else if (contains(operators, s[0]))
    {
        cout << "op '" << s.substr(0, 1) << "', '" << s.substr(1) << "'\n";
        return { s.substr(0, 1), s.substr(1) };
    }

    cout << "nowt\n";
    return { {}, s };
}

string infix(string_view rpn)
{
    const auto a = token(rpn);
    const auto b = token(a.second);
    const auto c = token(b.second);
    if (a.first.empty() || b.first.empty() || c.first.empty())
        return "???"; // {};

    return string(a.first) + " " + string(c.first) + " " + string(b.first);
}

int main()
{
    // basics, and make sure we dont care about whitespace round operator
    test(infix("3 4-"), "3 - 4");
    test(infix("78 52*"), "78 * 52");
    test(infix("7 8 *"), "7 * 8");
    test(infix("7 8*"), "7 * 8");
    test(infix("7777 8  *"), "7777 * 8");

    // next level
    test(infix("3 4 − 5 +"), "3 - 4 + 5");
    return 0;
}
