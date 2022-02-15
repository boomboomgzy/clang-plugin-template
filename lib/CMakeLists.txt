add_library(printfunc MODULE
  PrintFunction.cpp
)

target_include_directories(printfunc
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS printfunc DESTINATION lib)
