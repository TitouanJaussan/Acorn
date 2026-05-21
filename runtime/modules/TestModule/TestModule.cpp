#include <iostream>

#include "TestModule.hpp"

void load()
{
    std::cout << "Initialized Test Module" << std::endl;
}

void update()
{
    
}

void render()
{

}

void unload()
{
    std::cout << "Unloaded module" << std::endl;
}

const char name[] = "Test Module";
