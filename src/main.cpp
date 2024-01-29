#include <iostream>
 
#include <volk.h>
#include <VkBootstrap.h>

#define REQUIRED_VK_VERSION VK_MAKE_API_VERSION(0, 1, 2, 0)
#define VK_FAILED(vkResult) (vkResult < 0)

int main(void) {
    if (VK_FAILED(volkInitialize()))
        return -1;

    if (volkGetInstanceVersion() < REQUIRED_VK_VERSION)
        return -1;

    return 0;
}