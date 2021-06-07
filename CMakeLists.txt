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
        LexicalAnalyzer/RegexGenerator.cpp
        LexicalAnalyzer/RegexGenerator.h
        LexicalAnalyzer/RegexListGenerator.cpp
        LexicalAnalyzer/RegexListGenerator.h
        LexicalAnalyzer/RegularDefinition.cpp
        LexicalAnalyzer/RegularDefinition.h
        LexicalAnalyzer/RegularExpression.cpp
        LexicalAnalyzer/RegularExpression.h
        LexicalAnalyzer/InputProcessor.cpp
        LexicalAnalyzer/InputProcessor.h
        LexicalAnalyzer/TestMain.cpp
        LexicalAnalyzer/DFA_minimization.h
        LexicalAnalyzer/DFA.h
        LexicalAnalyzer/NFA.h
        LexicalAnalyzer/testCode.h
        main.cpp
        Parser/Facade.cpp
        Parser/predictiveParsingTableForTheGrammar.cpp
        Parser/Facade.h
        Parser/FatherOfAllThingsTerminal.cpp
        Parser/FatherOfAllThingsTerminal.h
        Parser/InputReader.cpp
        Parser/InputReader.h)
