#include <iostream>
#include <conio.h>
#include "Map.h"
using namespace std;

int main()
{
    Map m;
    m.Insert(5, "dac");
    m.Insert(3, "dsac");
    m.Insert(7, "dsac");
    m.Insert(12, "sdsac");
    m.Insert(4, "ssdddsac");
    m.Insert(11, "ssdddsac");
    m.Print();

    return 0;
}
