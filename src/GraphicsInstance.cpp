#include "GraphicsInstance.hpp"
#include "VkHelpers.hpp"

#include <exception>

const GraphicsInstance* GraphicsInstance::CreateGraphicsInstance() {
    if (VK_FAILED(volkInitialize()))
        throw std::runtime_error("Failed to initialize volk.");

    if (volkGetInstanceVersion() < REQUIRED_VK_VERSION)
        throw std::runtime_error("Failed to get Vulkan instance version.");

    vkb::Result<vkb::Instance> instanceResult = vkb::InstanceBuilder(vkGetInstanceProcAddr)
        .require_api_version(REQUIRED_VK_VERSION)
        .enable_validation_layers(true)
        .use_default_debug_messenger()
        .build();

    if (!instanceResult)
        throw std::runtime_error("Failed to build Vulkan instance.");

    vkb::Instance& vkInstance = instanceResult.value();

    volkLoadInstance(vkInstance);

    return new GraphicsInstance(vkInstance, GraphicsAdapter::Create(vkInstance));
}