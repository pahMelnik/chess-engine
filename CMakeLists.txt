cmake_minimum_required(VERSION 3.10)
project(chess_engine LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SOURCES src/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Добавляем исполняемый файл
add_executable(chess_engine ${SOURCES})

# Указываем путь к заголовкам
target_include_directories(chess_engine PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Указываем выходной путь для бинарника
set_target_properties(chess_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build
)
