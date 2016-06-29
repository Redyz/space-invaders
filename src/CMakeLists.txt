echo_dir()
add_subdirectory(game)
if(IS_SFML)
    add_subdirectory(gui)
  else()
    add_subdirectory(guincurses)
endif(IS_SFML)

file(GLOB TEMP
  "*.cpp"
)

set(PROJECT_SOURCE ${PROJECT_SOURCE} ${TEMP} PARENT_SCOPE)