cmake_minimum_required(VERSION 3.22)

set(NAME_PROJECT SearchEngine)
project(${NAME_PROJECT} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------
# Подключаем FetchContent
# ----------------------------
#include(FetchContent)

# ----------------------------
# nlohmann/json
# ----------------------------
add_subdirectory(include/nlohmann)
#FetchContent_Declare(
#        nlohmann_json
#        GIT_REPOSITORY https://github.com/nlohmann/json.git
#        GIT_TAG v3.11.3
#)

#FetchContent_MakeAvailable(nlohmann_json)

# ----------------------------
# GoogleTest
# ----------------------------
add_subdirectory(include/googletest)
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG v1.14.0
#)
#
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

enable_testing()

# ----------------------------
# Основное приложение
# ----------------------------
add_executable(${NAME_PROJECT}
        src/main.cpp
        src/SearchEngine.cpp
        src/SearchEngine.h
        src/dto/ConfigDTO.cpp
        src/dto/ConfigDTO.h
        src/dto/RequestDTO.cpp
        src/dto/RequestDTO.h
        src/dto/AnswersDTO.cpp
        src/dto/AnswersDTO.h
        src/coopFunc.cpp
        src/coopFunc.h
        src/dto/Document.cpp
        src/dto/Document.h
        src/dto/Indexer.cpp
        src/dto/Indexer.h
        src/ConverterJSON.cpp
        src/ConverterJSON.h
)

target_include_directories(${NAME_PROJECT} PRIVATE include)

target_link_libraries(${NAME_PROJECT}
        PRIVATE
        nlohmann_json::nlohmann_json
)

# ----------------------------
# Тесты
# ----------------------------
add_subdirectory(tests)