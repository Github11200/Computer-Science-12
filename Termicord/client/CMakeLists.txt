find_package(spdlog CONFIG REQUIRED)

add_executable(client
  src/client.cpp
)

target_link_libraries(client PRIVATE spdlog::spdlog)

target_include_directories(client
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIRECTORY}/include
)
