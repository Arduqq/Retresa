add_executable(tests main.cpp)

target_link_libraries(tests
                      ${FRAMEWORK_NAME}
                      ${LIBRARIES}
                      )

add_dependencies(tests glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

