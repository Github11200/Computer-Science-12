find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(stduuid REQUIRED)

add_executable(http
  src/http.cpp
  src/routing.cpp
)
target_link_libraries(http PRIVATE spdlog::spdlog)
target_include_directories(http
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

