#include "Precompiled.hpp"
#include "Configuring.hpp"
#include <iostream>
#include <stdexcept>

Configuring::Configuring()
{
    std::cout << "\t\tEntering Configuring state!\n";
}

Configuring::~Configuring()
{
    std::cout << "\t\tExisting Configuring state!\n";
}

