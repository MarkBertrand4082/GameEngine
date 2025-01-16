#include <iostream>

#include "NoCommandDemo.h"

int main()
{
    NoCommandDemo* ncd = new NoCommandDemo();
    std::cout << "No Commands: \n";
    ncd->HandleInput("X");
    ncd->HandleInput("Y");
    ncd->HandleInput("A");
    ncd->HandleInput("B");
}
