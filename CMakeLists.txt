cmake_minimum_required(VERSION 2.8)

# project name
project(Space-Invaders)

# versions
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Redyz doodle Redyz@doodle.com")
set(CPACK_PACKAGE_DESCRIPTION "Some space invaders game")
set(CPACK_DEBIAN_PACKAGE_NAME "bacon")
set(CPACK_DEBIAN_PACKAGE_VERSION ${VERSION})

include(CPack)

# WINDOW CROSS COMPILE #
#SET(CMAKE_SYSTEM_NAME Windows)
# which compilers to use for C and C++
#SET(CMAKE_C_COMPILER i586-mingw32msvc-gcc)
#SET(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
#SET(CMAKE_RC_COMPILER i586-mingw32msvc-windres)
# here is the target environment located
#SET(CMAKE_FIND_ROOT_PATH  /usr/i586-mingw32msvc /home/alex/mingw-install )
# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# END OF WINDOWS CC #

set(BUILD_SFML false CACHE BOOL "Set this to true to build using SFML, or false to use Ncurses")
# add header location
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
)
set(PS ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC ${PS}/src)
set(INC ${PS}/include)

# create configuration files
#configure_file(
#	"${
#	"${INC}/config.h"	
#)

# Source files
message("Configuring using source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
if(BUILD_SFML)
  message("Building with SFML")
  file(GLOB_RECURSE PROJECT_SRC
      "${INC}/*.h"
      "${SRC}/*.cpp"
      )
else()
  message("Building with Ncurses")
  file(GLOB_RECURSE PROJECT_SRC
      "${INC}/*.h"
      "${SRC}/*.cpp"
      )
endif(BUILD_SFML)
message("Include path: ${CMAKE_INCLUDE_PATH}")
message("Prefix path: ${CMAKE_PREFIX_PATH}")
#message("Files: ${PROJECT_SRC}")
list(LENGTH PROJECT_SRC fileCount)
message("File count: ${fileCount}")
# install target
#install(TARGETS ${NAME} DESTINATION {DEST})

# windows specific code
if(WIN32)
	message("Windows environnement detected - we shall build on windows")
endif()

if(UNIX)
	message("Linux environnement detected - we're building on some Ganoo/linucks")
endif()

#
# if(ARCH_32BITS) // if(ARCH_64BITS)
#
set(FULL_PROJECT_NAME v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}) 
message("Beginning build of ${PROJECT_NAME}, version ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

# detect and add SFML + ncurses
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.1 REQUIRED system window graphics network audio)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})
set(CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/libncurses.so")
