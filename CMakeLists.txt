cmake_minimum_required(VERSION 3.16)
project(java_compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(java_compiler
        .idea/.gitignore
        .idea/.name
        .idea/java-compiler.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/java_compiler.cbp
        cmake-build-debug/Makefile
        .gitignore
        CMakeLists.txt
        RegexGenerator.cpp
        RegexGenerator.h
        RegexListGenerator.cpp
        RegexListGenerator.h
        RegularDefinition.cpp
        RegularDefinition.h
        RegularExpression.cpp
        RegularExpression.h
        InputProcessor.cpp
        InputProcessor.h

        TestMain.cpp)