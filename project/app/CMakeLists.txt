add_executable(opengl-engine
    src/main.cpp
    src/element_buffer_class.cpp
    src/shader_class.cpp
    src/vertex_array_class.cpp
    src/vertex_buffer_class.cpp
    src/vertex_buffer_layout_class.cpp
)

target_include_directories(opengl-engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(opengl-engine PRIVATE
    glad
    glfw3
    khr
)

set(APP_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

add_custom_command(TARGET opengl-engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${APP_RESOURCES_DIR}/shaders
        $<TARGET_FILE_DIR:opengl-engine>/shaders
    COMMENT "Copying application resources"
)
