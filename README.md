# Homework22

## The Problem

From https://accu.org/journals/cvu/cvu36-2

Homework Challenge 22

*Write a program that will convert a Reverse Polish Notation expression for simple arithmetic (add, subract, multiply, divide) into an equivalent expression using infix notation.*


### Some links

https://en.wikipedia.org/wiki/Reverse_Polish_notation

https://en.wikipedia.org/wiki/Infix_notation

### My environment
```
mrj@ktulu:~/code/Homework22$ gcc --version
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
```

Note that gcc doesn't have <format> in C++20, which is annoying and means some string manipulation isn't ideal.

### My command line
```
mrj@ktulu:~/code/Homework22$ g++ -std=c++20 hw22.cpp && ./a.out
```

### Thoughts
The program could be a lot simpler if it assumed the input is nicely separated by white space.
Then tokenise() is simply split on spaces, trim each token, and reverse the list. That could probably be done in a one line ranges expression.
And if we ignored bad input, or just passed it through somehow, the exception handling parts could be removed further simplifying things.
