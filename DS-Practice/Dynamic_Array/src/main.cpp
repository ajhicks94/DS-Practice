#include "dynArr.cpp"
#include <string>

using std::string;

int main()
{
    dynArr<int> arr;
    arr.push_back(3);
    arr.push_back(10);

    dynArr<float> farr;
    farr.push_back(3.14);

    dynArr<char> charr;
    charr.push_back('a');
    charr.push_back('b');
    charr.push_back('c');

    dynArr<std::string> strarr;
    strarr.push_back("String");

    arr.print();
    farr.print();
    charr.print();
    strarr.print();

    return 0;
}