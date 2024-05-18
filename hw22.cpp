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
#include <deque>
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
    cout << "tokenise(" << s << ") :\n";

    deque<string_view> tokens;

    while (!s.empty())
    {
        cout << "  '" << s << "' >>> ";
        while (!s.empty() && isspace(s[0])) s.remove_prefix(1);
        cout << " '" << s << "' -> ";

        if (is_number(s))
        {
            auto end = s.find_first_not_of(digits);
            tokens.push_front(s.substr(0, end));
            s.remove_prefix(end);
            cout << "dig '" << tokens.back() << "'\n";
        }
        else if (is_operator(s))
        {
            tokens.push_front(s.substr(0, 1));
            s.remove_prefix(1);
            cout << "opr '" << tokens.back() << "'\n";
        }
        else
        {
            cout << " eh? '" << s[0] << "'\n";
            return { "???" };   // we've encountered something illegal
        }
    }

    return tokens;
}

string recurse(deque<string_view> d, size_t n)
{
    string s = string(" ") + string{d[n]} + " ";
    n++;
    if (n == d.size())
        return s;
    if (is_number(d[n]))
    {
        s.append(d[n]);
    }
    else
    {
        const auto expression = recurse(d, n);
        s = expression + s;
    }
    n++;
    if (n == d.size())
        return s;
    if (is_number(d[n]))
    {
        s = string(d[n]) + s;
    }
    else
    {
        const auto expression = recurse(d, n);
        s = expression + s;
    }

    return s;
}

string infix(string_view rpn)
{
    const auto tokens = tokenise(rpn);
    {
        string s;
        for (const auto& t : tokens) s.append(string{t}), s.append(", ");
        cout << "Tokens: " << s << '\n';
    }
    return recurse(tokens, 0);
/*
    if (tokens.size() > 1)
    {
        return string(tokens[2]) + " " + string(tokens[0]) + " " + string(tokens[1]);
    }
    if (tokens.empty())
        return "@@@"; // {};

    string s;
    for (const auto& t : tokens) s.append(string{t}), s.append(", ");
    return s;
*/
}

int main()
{
    // basics, and make sure we dont care about whitespace round operator
    test(infix("3 4-"), "3 - 4");
    test(infix("78 52*"), "78 * 52");
    test(infix("7 8 +"), "7 + 8");
    test(infix("7 8/"), "7 / 8");
    test(infix("7777 8  *"), "7777 * 8");

    // next level
    test(infix("3 4 - 5 +"), "3 - 4 + 5");
    return 0;
}
