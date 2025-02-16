target_sources(qcla PRIVATE
        ${CMAKE_BINARY_DIR}/qcla-config.cpp
        commandlineoption.cpp
        commandlineoption.h
        commandlineparser.cpp
        commandlineparser.h
        argumentgroup.cpp
        argumentgroup.h
        fmt.h
)

install(TARGETS qcla EXPORT qclaTargets
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qcla
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# install some header files for public usage. more are added in the sub directories
install(FILES ${CMAKE_BINARY_DIR}/qcla_config.h
        ${CMAKE_BINARY_DIR}/qcla_export.h
        commandlineoption.h
        commandlineparser.h
        argumentgroup.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qcla)
