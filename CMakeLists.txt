cmake_minimum_required(VERSION 3.0)

project(QuantLibParser VERSION 1.0.0)

find_package(Boost REQUIRED)
find_package(QuantLib REQUIRED)

add_library(QuantLibParser INTERFACE)

include(GNUInstallDirs)
#https://dominikberner.ch/cmake-interface-lib/
target_include_directories(QuantLibParser INTERFACE 
                                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
                                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#create configs files to be used with find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file("${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
                              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION
                              ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake)



#install paths
set(CONFIG_INSTALL_DIR        "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(INCLUDE_INSTALL_DIR       "${CMAKE_INSTALL_INCLUDEDIR}")

#export targets to be used with find_package
install(TARGETS QuantLibParser
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

#exports headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${PROJECT_NAME})
