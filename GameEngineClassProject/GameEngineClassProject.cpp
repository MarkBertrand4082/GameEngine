#include <iostream>

#include "CommandDemo.h"

int main()
{
    CommandDemo* cd = new CommandDemo();
    std::cout << "\nCommands: \n";
    cd->HandleInput("X");
    cd->HandleInput("Y");
    cd->HandleInput("A");
    cd->HandleInput("B");
    delete cd;
}
