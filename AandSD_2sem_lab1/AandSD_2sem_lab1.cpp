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
    m.Print();
    return 0;
}
