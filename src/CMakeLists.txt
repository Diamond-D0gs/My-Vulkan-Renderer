add_executable(${EXECUTABLE_NAME}
    main.cpp
    Graphics/Vulkan/HelpersVK.hpp
    Graphics/Vulkan/GraphicsAdapterVK.hpp
    Graphics/Vulkan/GraphicsAdapterVK.cpp
    Graphics/Vulkan/GraphicsDeviceVK.hpp
    Graphics/Vulkan/GraphicsDeviceVK.cpp
    Graphics/Vulkan/GraphicsInstanceVK.hpp
    Graphics/Vulkan/GraphicsInstanceVK.cpp
    Graphics/GraphicsAdapter.hpp
    Graphics/GraphicsDevice.hpp
    Graphics/GraphicsInstance.hpp
    Graphics/GraphicsInstance.cpp
)

target_link_libraries(
    ${EXECUTABLE_NAME}
    PUBLIC
    glfw::glfw
    volk::volk
    vk-bootstrap::vk-bootstrap
    VulkanMemoryAllocator
    glm::glm
)