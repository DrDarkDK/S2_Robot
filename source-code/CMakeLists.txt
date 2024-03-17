
#sets what files will be used for the CMakeList. 
set(FILES
    main.cpp
    robotics.cpp
    robotics.h

)

add_executable(${CMAKE_PROJECT_NAME} ${FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-window sfml-system)