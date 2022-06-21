#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

// Evaluates an integer arithmetic expression
          //   If infix is a syntactically valid infix integer expression whose
          //   only operands are single lower case letters (whether or not they
          //   appear in the values map), then postfix is set to the postfix
          //   form of the expression; otherwise postfix may or may not be
          //   changed, result is unchanged, and the function returns 1.  If
          //   infix is syntactically valid but contains at least one lower
          //   case letter operand that does not appear in the values map, then
          //   result is unchanged and the function returns 2.  If infix is
          //   syntactically valid and all its lower case operand letters
          //   appear in the values map, then if evaluating the expression
          //   (using for each letter in the expression the value in the map
          //   that corresponds to it) attempts to divide by zero, then result
          //   is unchanged and the function returns 3; otherwise, result is
          //   set to the value of the expression and the function returns 0.


int precedence(char c) {        //checked for the precedence of the operations
    switch (c) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 3;
    }
}

bool isValid(string infix) {
    string temp = "";

    for (int i = 0; i < infix.size(); i++) {
        if (isspace(infix[i]) == 0) {
            temp += infix[i];               //making a temp function without spaces
        }
    }

    if (temp.size() == 0)               //size zero check
        return false;

    if (temp[0] == '+' || (temp[0]) == '-' || (temp[0]) == '*' || (temp[0]) == '/' || temp[0] == ')') { //if starts with an illegal char
        return false;
    }
    if (temp[temp.size() - 1] == '+' || temp[temp.size() - 1] == '-' || temp[temp.size() - 1] == '*' || temp[temp.size() - 1] == '/' || temp[temp.size() - 1] == '(') {
        return false;           //if ends with an illigal char
    }

    for (int i = 0; i < temp.size(); i++) {
        if (isupper(temp[i])) {           //upper cases are not allowed
            return false;                   
        }
        else if (!isalpha(temp[i])) {
            if (temp[i] != '+' && temp[i] != '-' && temp[i] != '*' && temp[i] != '/' && temp[i] != '(' && temp[i] != ')') {
                return false;           //if special characters other than operations and parathesis appear, return false
            }
        }
    }

    int par_count = 0; int defult = 0;      //paranthesis rule
    for (int k = 0; k < temp.size(); k++) {
        if (temp[k] == '(') {
            par_count++;
        }
        else if (temp[k] == ')') {
            if (par_count == 0) {
                return false;
            }
            par_count--;
        }
    }
    if (par_count != 0)
        return false;


    for (int i = 0; i < temp.size(); i++) {
        if (isalpha(temp[i])) {                 //alphabets rules - an alphabet/open paranthesis cannot follow an alphabet
            if (i + 1 < temp.size()) {
                if (isalpha(temp[i + 1]) || temp[i + 1] == '(') {
                    return false;
                }
            }
        }

        else if (temp[i] == '(') {                   //open bracket rules - there must be an alphabet after open
            if (i + 1 < temp.size()) {
                if ((temp[i + 1]) == '+' || (temp[i + 1]) == '-' || (temp[i + 1]) == '*' || (temp[i + 1]) == '/' || temp[i + 1] == ')') {
                    return false;
                }
            }
        }

        else if (temp[i] == ')') {                   //close bracket rules - there must be an operation after closing
            if (i + 1 < temp.size()) {
                if (isalpha(temp[i + 1]) || temp[i + 1] == '(') {
                    return false;
                }
            }
        }

        if ((temp[i]) == '+' || (temp[i]) == '-' || (temp[i]) == '*' || (temp[i]) == '/') {         //operation rules - there must be alphabets or open parathesis after operations
            if (i + 1 < temp.size()) {
                if ((temp[i + 1]) == '+' || (temp[i + 1]) == '-' || (temp[i + 1]) == '*' || (temp[i + 1]) == '/' || temp[i + 1] == ')') {
                    return false;
                }
            }
        }
    }
    return true;        //if all cases satisfied, return true
}

bool isThere(string infix, Map val) {   //checking for retuerning 2 case
    for (int i = 0; i < infix.size(); i++) {
        if (isalpha(infix[i])) {
            if (val.contains(infix[i]) == 0) {
                return false;           //if any of the char is not present in the value of map then return false
            }
        }
    }
    return true;
}


int evaluate(string infix, const Map& values, string& postfix, int& result) {
    if (isValid(infix) == 0) {      //if not valid return 1
        return 1;
    }

    //postfix conversion
    stack <char> cstack;
    string temp = "";
    postfix = "";

    for (int i = 0; i < infix.size(); i++) {
        if (isspace(infix[i]) == 0) {
            temp += infix[i];               //making a temp function without spaces
        }
    }

    for (int i = 0; i < temp.size(); i++) {
        if (islower(temp[i])) {
            postfix += temp[i];
        }
        else if (temp[i] == '(') {
            cstack.push(temp[i]);
        }
        else if (temp[i] == ')') {
            while (cstack.top() != '(') {
                postfix += cstack.top();
                cstack.pop();
            }
            cstack.pop();
        }
        if ((temp[i]) == '+' || (temp[i]) == '-' || (temp[i]) == '*' || (temp[i]) == '/') {
            while (!cstack.empty() && cstack.top() != '(' && precedence(temp[i]) <= precedence(cstack.top())) {
                postfix += cstack.top();
                cstack.pop();
            }
            cstack.push(temp[i]);
        }
    }
    while (!cstack.empty()) {
        postfix += cstack.top();
        cstack.pop();
    }

    if (isThere(infix, values) == 0) {      //we check the map after changing to postfix
        return 2;
    }

    //evaluating the result
    stack <int> eva;
    for (int i = 0; i < postfix.size(); i++) {
        if (islower(postfix[i])) {
            int val;
            values.get(postfix[i], val);
            eva.push(val);
        }
        else if (postfix[i] == '+') {
            int v1 = eva.top();
            eva.pop();
            int v2 = eva.top();
            eva.pop();
            eva.push(v2 + v1);
        }
        else if (postfix[i] == '-') {
            int v1 = eva.top();
            eva.pop();
            int v2 = eva.top();
            eva.pop();
            eva.push(v2 - v1);
        }
        else if (postfix[i] == '*') {
            int v1 = eva.top();
            eva.pop();
            int v2 = eva.top();
            eva.pop();
            eva.push(v2 * v1);
        }
        else if (postfix[i] == '/') {
            int v1 = eva.top();
            if (v1 == 0)
                return 3;
            eva.pop();
            int v2 = eva.top();
            eva.pop();
            eva.push(v2 / v1);
        }
    }
    result = eva.top();
    return 0;
}

//int main()
//{
//    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
//    int  vals[] = { 3,  -9,   6,   2,   4,   1 };
//    Map m;
//    for (int k = 0; vars[k] != '#'; k++)
//        m.insert(vars[k], vals[k]);
//    string pf;
//    int answer;
//    assert(evaluate("a+ e", m, pf, answer) == 0 &&
//        pf == "ae+" && answer == -6);
//    answer = 999;
//    assert(evaluate("", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
//    // unary operators not allowed:
//    assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
//    assert(evaluate("a*b", m, pf, answer) == 2 &&
//        pf == "ab*" && answer == 999);
//    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
//        pf == "yoau-*+" && answer == -1);
//    answer = 999;
//    assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
//        pf == "oyy-/" && answer == 999);
//    assert(evaluate(" a  ", m, pf, answer) == 0 &&
//        pf == "a" && answer == 3);
//    assert(evaluate("((a))", m, pf, answer) == 0 &&
//        pf == "a" && answer == 3);
//    cout << evaluate("(a+o )* i)*((a / i)", m, pf, answer) << endl;
//    assert(evaluate("((i +    c))", m, pf, answer) == 2 && pf == "ic+");
//    assert(evaluate("a / i * (o / o)", m, pf, answer) == 0 && answer == 0);
//    assert(evaluate("((a)))", m, pf, answer) == 1);
//    assert(evaluate("(a - a)* i", m, pf, answer) == 0 && answer == 0);
//    assert(evaluate("((a-a)/i)", m, pf, answer) == 0 && answer == 0);
//    assert(evaluate("(o / (a-a)) ", m, pf, answer) == 3 && pf == "oaa-/");
//    answer = 3;
//    assert(evaluate("+((a+y))", m, pf, answer) == 1 && answer == 3);
//    assert(evaluate("a))+a+((", m, pf, answer) == 1 && answer == 3);
//    assert(evaluate("a+b--c", m, pf, answer) == 1 && answer == 3);
//    assert(evaluate("a+b-1", m, pf, answer) == 1 && answer == 3);
//    assert(evaluate("a*(a+(i-o))", m, pf, answer) == 0 && answer == 21);
//    assert(evaluate("(a+o )* i)((a / i)", m, pf, answer) == 1);
//    cout << "Passed all tests" << endl;
//}