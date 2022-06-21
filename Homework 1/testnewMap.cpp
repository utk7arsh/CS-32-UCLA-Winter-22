#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

// To test a Map from string to double, leave the following #define line
// commented out; to test a Map from int to string, remove the "//".

// #define INT_TO_STRING

#ifdef INT_TO_STRING

const KeyType DUMMY_KEY = 9876543;
const ValueType DUMMY_VALUE = "Ouch";
const KeyType NO_SUCH_KEY = 42;
const KeyType KEY1 = 123456789;
const ValueType VALUE1 = "Wow!";

#else // assume string to double

const KeyType DUMMY_KEY = "hello";
const ValueType DUMMY_VALUE = -1234.5;
const KeyType NO_SUCH_KEY = "abc";
const KeyType KEY1 = "xyz";
const ValueType VALUE1 = 9876.5;

#endif

void test()
{
    Map m;
    assert(m.empty());
    ValueType v = DUMMY_VALUE;
    assert(!m.get(NO_SUCH_KEY, v) && v == DUMMY_VALUE); // v unchanged by get failure
    m.insert(KEY1, VALUE1);
    assert(m.size() == 1);
    KeyType k = DUMMY_KEY;
    assert(m.get(0, k, v) && k == KEY1 && v == VALUE1);
}

int main()
{
    test();
    cerr << "Passed all tests" << endl;
}