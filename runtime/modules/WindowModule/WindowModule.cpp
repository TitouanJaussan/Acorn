#include "WindowModule.hpp"

static Acorn::Core::Logger logger{};

void load(Acorn::Core::Logger providedLogger)
{
    logger = providedLogger;

    logger.info("Loaded Window Module");
}

void update()
{

}

void render()
{

}

void unload()
{
    logger.info("Unloaded Window Module");
}

const char name[] = "Window";
