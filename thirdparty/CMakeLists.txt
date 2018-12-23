cmake_minimum_required(VERSION 3.12)
include(ExternalProject)

# SFML
externalproject_add(
    SFML
    URL https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip
    PREFIX ${CMAKE_SOURCE_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/src/SFML/bin/ ${CMAKE_SOURCE_DIR}/..
)

# TinyXml2
set(TINYXML2_DLL
    $<$<CONFIG:Debug>:Debug/tinyxml2d.dll>
    $<$<CONFIG:Release>:Release/tinyxml2.dll>
)
externalproject_add(
    tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
    GIT_TAG de6d164822076f9b1e26a7222808a25ac03867d8
    GIT_SHALLOW true
    PREFIX ${CMAKE_SOURCE_DIR}
    INSTALL_COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/src/tinyxml2-build/${TINYXML2_DLL} ${CMAKE_SOURCE_DIR}/..
)

# Yaml-Cpp
externalproject_add(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG abf941b20d21342cd207df0f8ffe09f41a4d3042
    GIT_SHALLOW true
    PREFIX ${CMAKE_SOURCE_DIR}
    CMAKE_ARGS -DYAML_CPP_BUILD_TESTS=OFF -DYAML_CPP_BUILD_TOOLS=OFF -D YAML_CPP_INSTALL=OFF
    INSTALL_COMMAND ""
)