// ACCU Homework Challenge 22
//
// From https://accu.org/journals/cvu/????
//
// Write a program that will convert a Reverse Polish Notation expression for
// simple arithmetic (add, subract, multiply, divide) into an equivalent
// expression using infix notation.

#include <cassert>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>

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

bool is_number(string_view s)
{
    return contains(digits, s[0]);
}

bool is_operator(string_view s)
{
    return contains(operators, s[0]);
}

deque<string_view> tokenise(string_view s)
{
    deque<string_view> tokens;
    while (!s.empty())
    {
        while (!s.empty() && isspace(s[0]))
            s.remove_prefix(1);

        size_t chars_to_consume = 1;
        if (is_number(s))
            chars_to_consume = s.find_first_not_of(digits);
        else if (!is_operator(s))
            throw std::invalid_argument(string{s});

        tokens.push_front(s.substr(0, chars_to_consume));
        s.remove_prefix(chars_to_consume);
    }

    return tokens;
}

string expand(deque<string_view> d, size_t& n)
{
    // operator
    string s = string(" ") + string{d[n]} + " ";
    n++;

    // right hand operand or expression
    if (is_number(d[n]))
    {
        s.append(d[n]);
        n++;
    }
    else
        s.append("(" + expand(d, n) + ")");

    // left hand operand or expression
    if (is_number(d[n]))
    {
        s = string(d[n]) + s;
        n++;
    }
    else
        s = "(" + expand(d, n) + ")" + s;

    return s;
}

string infix(string_view rpn)
{
    try
    {
        size_t n{0};
        return expand(tokenise(rpn), n);
    }
    catch (std::invalid_argument const & ex)
    {
        return "???";
    }
}

int main()
{
    // basics, and make sure we dont care about whitespace round operator
    test(infix("3 4-"), "3 - 4");
    test(infix("78 52*"), "78 * 52");
    test(infix("7 8 +"), "7 + 8");
    test(infix("7 8/"), "7 / 8");
    test(infix("7777 8  *"), "7777 * 8");

    // some nesting
    test(infix("3 4 - 5 +"), "(3 - 4) + 5");

    // harder
    test(infix("4  8  +  1  3  +  /"), "(4 + 8) / (1 + 3)");
    test(infix("28  6  2  4  *  +  /"), "28 / (6 + (2 * 4))");
    test(infix("4 2 5 * + 1 3 2 * + /"), "(4 + (2 * 5)) / (1 + (3 * 2))");

    // errors
    test(infix("banana"), "???");
    test(infix("1 + a"), "???");
    test(infix("b / 5"), "???");

    return 0;
}
