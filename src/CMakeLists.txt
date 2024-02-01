file(GLOB APP_SOURCES CONFIGURE_DEPENDS *.cpp *.hpp *.h)

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

target_link_libraries(
    ${EXECUTABLE_NAME}
    PUBLIC
    glfw::glfw
    volk::volk
    vk-bootstrap::vk-bootstrap
    VulkanMemoryAllocator
    glm::glm
)