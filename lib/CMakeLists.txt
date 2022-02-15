add_library(astexp MODULE
  AstExporter.cpp
)

target_include_directories(astexp
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS astexp DESTINATION lib)
