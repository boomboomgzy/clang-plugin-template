
add_library(PrintFunction MODULE
  PrintFunction.cpp
)

target_include_directories(PrintFunction
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS PrintFunction DESTINATION lib)
