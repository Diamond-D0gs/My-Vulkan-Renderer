set(APP_SOURCES main.cpp)

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

target_link_libraries(
    ${EXECUTABLE_NAME}
    PUBLIC ${LIBRARY_NAME}
        glfw
        volk
        vk-bootstrap
        VulkanMemoryAllocator
        glm
)