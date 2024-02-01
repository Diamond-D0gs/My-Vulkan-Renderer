#include <iostream>
#include <exception>
#include <vector>

#include "GraphicsInstance.hpp"

int main(void) {
    auto graphicsInstance = GraphicsInstance::CreateGraphicsInstance();

    auto graphicsDevice = graphicsInstance->CreateGraphicsDevice(graphicsInstance->_graphicsAdapter);

    delete graphicsDevice;
    delete graphicsInstance;

    return 0;
}