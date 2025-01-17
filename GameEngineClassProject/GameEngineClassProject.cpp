#include <iostream>

#include "CommandDemo.h"

int main()
{
    CommandDemo* cd = new CommandDemo();
    std::cout << "\nCommands: \n";
    cd->HandleInput("W");
    cd->HandleInput("A");
    cd->HandleInput("S");
    cd->HandleInput("D");
    cd->Undo();
    cd->Undo();
    cd->Undo();
    cd->Undo();
    delete cd;
}
