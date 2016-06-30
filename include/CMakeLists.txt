echo_dir()

file(GLOB PROJECT_INCLUDES
  "*.h"
)

if(IS_SFML)
    add_subdirectory(gui)
  else()
    add_subdirectory(guincurses)
endif(IS_SFML)

set(PROJECT_INCLUDES ${PROJECT_INCLUDES} ${TEMP} PARENT_SCOPE)