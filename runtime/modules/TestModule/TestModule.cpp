#include "TestModule.hpp"

static Acorn::Core::Logger logger;

void load(Acorn::Core::Logger providedLogger)
{
    logger = providedLogger;
    logger.info("Loaded Test Module");
}

void update()
{
    
}

void render()
{

}

void unload()
{
    logger.info("Unloaded Test Module");
}

const char name[] = "Test Module";
