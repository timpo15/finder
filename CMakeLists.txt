cmake_minimum_required(VERSION 2.8)

project(finder)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fsanitize=address,undefined")

find_package(Qt5Widgets REQUIRED)

add_executable(finder main.cpp mainwindow.h mainwindow.cpp Index.cpp Index.h TrigramsHolder.cpp TrigramsHolder.h Trigrammer.cpp Trigrammer.h stupid_finder.cpp stupid_finder.h pf.h)
qt5_use_modules(finder Widgets)
