cmake_minimum_required(VERSION 2.8)

# project name
project(Space-Invaders)

# versions
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION "v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(IS_SFML false CACHE BOOL "Set this to true to build using SFML, or false to use Ncurses")
set(IS_DEBUG false CACHE BOOL "Whether or not to add debugging symbols to the build") # there is probably a more native way
set(IS_UTF8 false CACHE BOOL "Use fancy UTF8 symbols for ncurses 'sprites'")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

function(echo_dir)
  message("In ${CMAKE_CURRENT_SOURCE_DIR}")
endfunction(echo_dir)

set(PROJECT_INCLUDES "")
set(PROJECT_SOURCE "")

# create configuration files
configure_file(
  cmake_modules/config.cmake.in
  "../include/config.h"
)

include_directories(include)
add_subdirectory(include)
add_subdirectory(src)

# windows specific code
if(WIN32)
  message("Windows environnement detected - we shall build on windows")
  set(IS_NT 1)
elseif(UNIX)
  message("Linux environnement detected - we're building on some Ganoo/linucks")
  set(IS_UNIX 1)
endif(WIN32)

# Source files
message("Configuring using source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
if(IS_SFML)
  message("Building with SFML")
  set(PROJECT_NAME ${PROJECT_NAME}-SFML)
else()
  if(IS_UTF8)
    message("Building with Ncurses - with UTF8 support")
    set(PROJECT_NAME ${PROJECT_NAME}-UTF8)
  else(IS_UTF8)
    message("Building with Ncurses")
  endif(IS_UTF8)
endif(IS_SFML)

# Valgrind recipe on Unix
if(IS_UNIX)
  add_custom_target(
    callgrind COMMAND "valgrind" "--tool=callgrind" "--callgrind-out-file=file.out" "./${PROJECT_NAME}" 
    "&&" "callgrind_annotate" "file.out" "|" "less")
  add_custom_target(cppcheck COMMAND "cppcheck" "--enable=all" "--inconclusive" "--xml" "--xml-version=2" "../src/" "../include/" "2>" "cppcheck.xml" "|" "cppcheck-gui" "cppcheck.xml")

	add_custom_target(valgrind COMMAND "valgrind" "./${PROJECT_NAME}" "-v" "--leak-check=full")
	add_custom_target(cgdb COMMAND "cgdb" "./${PROJECT_NAME}")
	add_custom_target(cgdba COMMAND "../tools/debug.sh" )
endif(IS_UNIX)

set(FULL_PROJECT_NAME v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}) 
message("Beginning build of ${PROJECT_NAME}, ${FULL_PROJECT_NAME} ")

foreach(file ${PROJECT_INCLUDES})
  message("-- ${file}")
endforeach()

set(PROJECT_FILES  ${PROJECT_INCLUDES} ${PROJECT_SOURCE} )

add_executable(${PROJECT_NAME} ${PROJECT_FILES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin) 
if(IS_SFML)
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
  )
endif(IS_SFML)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)

set(CPACK_ARCHIVE_COMPONENT_INSTALL "ON")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Redyz doodle Redyz@doodle.com")
set(CPACK_DEBIAN_PACKAGE_NAME "bacon")
set(CPACK_DEBIAN_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_DESCRIPTION "Some space invaders game")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_GENERATOR "TGZ;STGZ;NSIS")
set(CPACK_COMPONENT_ALL applications)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)

# detect and add SFML + ncurses
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
if(IS_SFML)
    find_package(SFML 2.1 REQUIRED system window graphics network audio)
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
  else()
    if(IS_UTF8)
      set(CURSES_NEED_WIDE TRUE)
    endif(IS_UTF8)
    set(CURSES_NEED_NCURSES TRUE)
    find_package(Curses)
    target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})
endif(IS_SFML)

include(CPack)
