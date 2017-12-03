cmake_minimum_required(VERSION 2.8)
project(sGLGUI)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")


add_library(sglgui SHARED src/Event.cpp
					      src/Gui.cpp
						  src/Panel.cpp
						  src/Window.cpp)

install(TARGETS sglgui DESTINATION /usr/lib)