cmake_minimum_required(VERSION 3.15)		#проверка версии CMake.

set(PROJECT_NAME test)		#имя проекта
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)		#устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(test  
 main.cpp
 UI.cpp
 ListOfObjects.cpp
 Object.cpp
 Point.cpp
 UI.h
 ListOfObjects.h
 Object.h
 Point.h
)

file(COPY "input.txt" DESTINATION "/")