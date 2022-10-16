cmake_minimum_required(VERSION 3.10)

project(QuantLibParser VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

file(GLOB SOURCES "src/*.cpp" "src/schemas/*.cpp" "src/schemas/ratehelpers/*.cpp")
file(GLOB INCLUDES "include/*.hpp" "include/schemas/*.hpp" "include/schemas/ratehelpers/*.hpp")

add_library(QuantLibParser STATIC ${INCLUDES} ${SOURCES})

target_include_directories(QuantLibParser PRIVATE "src" "include" )

set(Boost_INCLUDE_DIR "C:/Users/bloomberg/Desktop/Desarrollo/builds/boost")
find_package(Boost REQUIRED)
find_package(QuantLib REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)

# add quantext

target_include_directories(QuantLibParser PRIVATE "$ENV{QLE_PATH}/include")
target_link_libraries(QuantLibParser PRIVATE "$ENV{QLE_PATH}/lib/QuantExt-x64-mt.lib")
target_link_libraries(QuantLibParser PRIVATE QuantLib::QuantLib)
target_link_libraries(QuantLibParser PRIVATE Boost::boost)
target_link_libraries(QuantLibParser PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(QuantLibParser PRIVATE nlohmann_json_schema_validator)


#https://dominikberner.ch/cmake-interface-lib/
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file("${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
                              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION
                              ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake)


set(CONFIG_INSTALL_DIR        "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(INCLUDE_INSTALL_DIR       "${CMAKE_INSTALL_INCLUDEDIR}")




#export targets to be used with find_package
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

#exports target config file to be used with find_package
install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CONFIG_INSTALL_DIR})
                            
#exports config file to be used with find_package
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CONFIG_INSTALL_DIR})

#exports headers to install dir
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX})

