add_library(StreamChecker MODULE
  StreamChecker.cpp
)

set_target_properties(StreamChecker PROPERTIES
  CXX_VISIBILITY_PRESET hidden
)

target_include_directories(StreamChecker
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(StreamChecker
  PRIVATE
    clang-cpp
)

install(TARGETS StreamChecker DESTINATION lib)
