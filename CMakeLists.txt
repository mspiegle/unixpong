CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(unixpong)

# add sources
ADD_SUBDIRECTORY(src)

# includes
INCLUDE_DIRECTORIES(include)

# apple fixes
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	INCLUDE_DIRECTORIES(/opt/local/include)
	LINK_DIRECTORIES(/opt/local/lib)
	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# CFLAGS
ADD_DEFINITIONS(-DDEBUG -O0 -Wall -g3 -Wextra -Werror -Wfatal-errors)

# add sources
INCLUDE(${unixpong_SOURCE_DIR}/src/SourceFiles.txt)

# build executables
ADD_EXECUTABLE(unixpong ${unixpong_SRC} ${unixpong_MAIN})

# link libs
TARGET_LINK_LIBRARIES(unixpong GL sdl SDLmain ${COCOA_LIBRARY})
