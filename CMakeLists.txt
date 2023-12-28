cmake_minimum_required(VERSION 3.27)
project(dnf_minimizer)


include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(dnf_minimizer main.cpp
        Singleton.h
        Table.h
        Table.cpp
        Screen.h
        TextBox.h
        TextBox.cpp
        Button.h
        TextLabel.h)

target_link_libraries(dnf_minimizer PRIVATE sfml-graphics)