#include "../src/dynArr.cpp"

#include <iostream>

using std::cout;

bool test_dynArr_int_operator_equals();
bool test_dynArr_int_operator_subscript();

int main()
{
    cout << "test_dynArr_int_operator_equals: " << test_dynArr_int_operator_equals() << '\n';
    cout << "test_dynArr_int_operator_subscript: " << test_dynArr_int_operator_subscript() << '\n';
    return 0;
}

bool test_dynArr_int_operator_subscript()
{
    bool res = false;
    int val = 3;

    dynArr<int> a;
    a.push_back(0);
    a.push_back(6);

    a[1] = val;

    if (a[1] == val)
    {
        res = true;
    }

    return res;
}

bool test_dynArr_int_operator_equals()
{
    dynArr<int> a;
    dynArr<int> b;

    a.push_back(1);
    a.push_back(5);
    a.push_back(7);

    b.push_back(1);
    b.push_back(5);
    b.push_back(7);

    return (a == b);
}