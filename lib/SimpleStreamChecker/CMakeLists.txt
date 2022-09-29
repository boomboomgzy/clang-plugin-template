add_library(SimpleStreamChecker MODULE
  SimpleStreamChecker.cpp
)

set_target_properties(SimpleStreamChecker PROPERTIES
  CXX_VISIBILITY_PRESET hidden
)

target_include_directories(SimpleStreamChecker
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(SimpleStreamChecker
  PRIVATE
    clang-cpp
)

install(TARGETS SimpleStreamChecker DESTINATION lib)
