#add_executable(example example.cpp)

#target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
#add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

#install(TARGETS example DESTINATION .)

add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

#aufgabe 6.5
#add_executable(aufgabe6.5 aufgabe6.5.cpp)

#target_link_libraries(aufgabe6.5 ${FRAMEWORK_NAME} ${LIBRARIES})
#add_dependencies(aufgabe6.5 glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

#install(TARGETS aufgabe6.5 DESTINATION .)
