cmake_minimum_required(VERSION 3.0)
project(par2deep2)

set(CMAKE_CXX_STANDARD 17)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

set(par2deep2_SRC
  src/main.cpp
  src/gui.cpp
  src/par2deep2.cpp
)

# Tell CMake to create the executable
add_executable(par2deep2 ${par2deep2_SRC})

# Add submodules to header search path
target_include_directories(par2deep2 PUBLIC ext/popl/include)

# Use the Widgets module from Qt 5.
target_link_libraries(par2deep2 Qt5::Widgets)

# Install the executable
install(TARGETS par2deep2 DESTINATION bin)
