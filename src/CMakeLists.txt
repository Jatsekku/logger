project(logger)

if (BUILD_STATIC_LIBS)

    # Create static library target named "logger-static" and provide list of sources
    add_library(logger-static STATIC
        logger_backend.c
        loggerPrinter.c
        numberPrinter.c)

    target_include_directories(logger-static PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )

    # Create list of public headers (API)
    set(PUBLIC_HEADERS "../include/logger/logger.h" "../include/logger/logger_common.h")
    
    # Copy headers to output
    install(FILES ${PUBLIC_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # Set tartget name
    # Library will be built as logger.a instead of logger-static.a
    set_target_properties(logger-static PROPERTIES
        OUTPUT_NAME logger)


    # Provide path where library will be installed
    # Export target's build information as group called "logger-targets"
    install(TARGETS logger-static
        EXPORT logger-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # Install target's build information to output
    install(EXPORT logger-targets
        FILE logger-targets.cmake
        NAMESPACE logger::
        DESTINATION ${CMAKE_INSTALL_CMAKEDIR})

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/logger-config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKEDIR})

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/logger-config.cmake"
        DESTINATION ${CMAKE_INSTALL_CMAKEDIR})
endif()
