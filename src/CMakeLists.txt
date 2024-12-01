project(logger)

if (BUILD_STATIC_LIBS)

    # Create static library target named "logger-static" and provide list of sources
    add_library(logger-static STATIC
        logger_backend.c
        loggerPrinter.c
        numberPrinter.c)

    # Set tartget name
    # Library will be built as logger.a instead of logger-static.a
    set_target_properties(logger-static PROPERTIES
        OUTPUT_NAME logger)

    # Provide path where library will be installed
    # Export target's build information as group called "logger-targets"
    install(TARGETS logger-static EXPORT logger-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    
    target_include_directories(logger-static PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/../include>
    )
endif()
