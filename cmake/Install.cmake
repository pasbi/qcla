include(GenerateExportHeader)
GENERATE_EXPORT_HEADER(qcla)

export(TARGETS qcla NAMESPACE qcla:: FILE qclaTargets.cmake)
export(PACKAGE qcla)

configure_file("qcla.pc.in" "qcla.pc" @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qcla.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
configure_package_config_file(cmake/qclaConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/qclaConfigToInstall.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qcla
        PATH_VARS CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(qclaConfigVersion.cmake VERSION ${PROJECT_VERSION} COMPATIBILITY SameMajorVersion)

install(EXPORT qclaTargets
        FILE qclaTargets.cmake
        NAMESPACE qcla::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qcla
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qclaConfigToInstall.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qcla
        RENAME qclaConfig.cmake
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qclaConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qcla
)
install(FILES
        ${CMAKE_SOURCE_DIR}/LICENSE.md
        DESTINATION ${CMAKE_INSTALL_DATADIR}/qcla/licenses
)
