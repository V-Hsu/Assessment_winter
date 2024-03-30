cmake_minimum_required(VERSION 3.0)

project(Snake)

include_directories(include)

add_executable(test main.cpp src/snake.cpp src/food.cpp) 
 
target_link_libraries(test sfml-system sfml-window sfml-graphics)
