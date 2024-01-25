set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

target_link_libraries(
    ${EXECUTABLE_NAME}
    PUBLIC ${LIBRARY_NAME}
        glfw:glfw
        volk:volk
        vk-bootstrap:vk-bootstrap
        VulkanMemoryAllocator:VulkanMemoryAllocator
        glm:glm
)