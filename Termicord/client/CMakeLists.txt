find_package(spdlog CONFIG REQUIRED)
find_package(restclient-cpp CONFIG REQUIRED)

add_executable(client
  src/client.cpp
)

target_link_libraries(client PRIVATE spdlog::spdlog restclient-cpp)

target_include_directories(client
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
