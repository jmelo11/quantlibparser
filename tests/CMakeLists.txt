cmake_minimum_required(VERSION 3.10)

project(
  QuantLibParserTests
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)

file(GLOB SOURCES "*.cpp")

file(GLOB INCLUDES "*.hpp")

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(QuantLibParserTests ${INCLUDES} ${SOURCES})
target_link_libraries(QuantLibParserTests PUBLIC gtest_main)

find_package(Boost REQUIRED)
find_package(QuantLib REQUIRED)
find_package(QuantLibParser REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)

# add quantext
target_link_libraries(QuantLibParserTests PUBLIC QuantLibParser::QuantLibParser)

include("../cmake/FindQuantExt.cmake")
target_link_libraries(QuantLibParserTests PUBLIC ${QLE_LIBRARY})
target_include_directories(QuantLibParserTests PUBLIC ${QLE_INCLUDE_DIR})

target_link_libraries(QuantLibParserTests PUBLIC QuantLib::QuantLib)
target_link_libraries(QuantLibParserTests PUBLIC Boost::boost)
target_link_libraries(QuantLibParserTests PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(QuantLibParserTests PUBLIC nlohmann_json_schema_validator)