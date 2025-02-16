cmake_minimum_required(VERSION 3.18)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

project(qcla VERSION 0.0.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(GetGitRevisionDescription)
git_describe(GIT_DESCRIBE "--tags")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
    add_compile_options(/Zi)
    add_link_options(/DEBUG)
endif ()

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_library(qcla SHARED
        ${CMAKE_BINARY_DIR}/qcla-config.cpp
        ${CMAKE_BINARY_DIR}/qcla-config.h
)

target_compile_features(qcla PUBLIC cxx_std_20)
target_compile_definitions(qcla PUBLIC
        QT_NO_KEYWORDS  # avoid clashes of common Qt-keywords like 'signal' with other frameworks.
)
target_include_directories(qcla PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qcla>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>
)

target_link_libraries(qcla PUBLIC fmt::fmt spdlog::spdlog Qt6::Core)

add_subdirectory(src)

configure_file(qcla_config.h.in qcla_config.h @ONLY)
configure_file(qcla_config.cpp.in qcla_config.cpp @ONLY)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FeatureSummary)
include(Install)

feature_summary(WHAT ENABLED_FEATURES DISABLED_FEATURES PACKAGES_FOUND)
