find_package(spdlog CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(ftxui CONFIG REQUIRED)

add_executable(client
  src/client.cpp
  src/utils/input.cpp
  src/utils/requests.cpp
  src/windows/auth.cpp
  src/windows/home.cpp
  src/windows/chat.cpp
)

target_link_libraries(client PRIVATE spdlog::spdlog cpr::cpr nlohmann_json::nlohmann_json magic_enum::magic_enum ftxui::dom ftxui::screen ftxui::component)

target_include_directories(client
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
