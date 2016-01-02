#include <iostream>
#include "../value.h"
#include "../colorize.h"
using namespace std;

int main()
{
    ///////////////////////////////////////
    string x    = "1254";
    char   y[]  = "1234";
    int    i    = 1234;
    long   l    = 123456;
    libwlc::ColorCode cc = libwlc::FGreen;
    ///////////////////////////////////////
    libwlc::Value v(cc);
    ///////////////////////////////////////
    cout << v.asBool() << "\t<=bool" << endl;
    cout << v.asDouble() << "\t<=double" << endl;
    cout << v.asFloat() << "\t<=float" << endl;
    cout << v.asInt() << "\t<=int" << endl;
    cout << v.asLong() << "\t<=long" << endl;
    cout << v.asShort() << "\t<=short" << endl;
    cout << v.asString() << "\t<=string" << endl;
    return 0;
}

