cmake_minimum_required(VERSION 3.24)
project(bugWorldAscii)

set(CMAKE_CXX_STANDARD 17)

# Find Boost with the serialization component
find_package(Boost REQUIRED COMPONENTS serialization)

# Print Boost information
message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")

# Add your source files
add_executable(bugWorldAscii main.cpp Thing.cpp Thing.h Furniture.cpp Furniture.h Room.cpp Room.h Door.cpp Door.h AbstractGame.cpp AbstractGame.h gameDictionary.h textFormater.cpp textFormater.h Chest.cpp Chest.h TestGame.cpp TestGame.h LockedDoor.cpp LockedDoor.h printImage.cpp printImage.h BugDemo.cpp BugDemo.h BoardedDoor.cpp BoardedDoor.h)

# Link against Boost libraries
target_link_libraries(bugWorldAscii PRIVATE Boost::serialization)

# Set architecture flags based on the system processor
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch x86_64")
endif()
