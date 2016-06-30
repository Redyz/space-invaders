echo_dir()

file(GLOB TEMP
  "*.cpp"
)

set(PROJECT_SOURCE ${PROJECT_SOURCE} ${TEMP} PARENT_SCOPE)