#include <iostream>
#include "colorize.h"

using namespace std;

int main(int argc, char **argv)
{
    string *test = new string[4];
    test[0] = "# 测试";
    test[1] = "apt-get";
    test[2] = "# 测试-2";
    test[3] = "apt-get-2";

    Colorize a(test,4);
    a.colorizeMsg();

    cout << test[0];
    cout << test[1];
    cout << test[2];
    cout << test[3];

    return 0;
}

