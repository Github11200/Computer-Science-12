find_package(spdlog CONFIG REQUIRED)

add_executable(server
  src/server.cpp
)
target_link_libraries(server PRIVATE spdlog::spdlog)
target_include_directories(server
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

